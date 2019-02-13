/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataSetDataCache.cpp
 * Author: ryan
 * 
 * Created on August 3, 2016, 7:47 AM
 */

#include "BasicSignalData.h"
#include "DataRow.h"

#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <limits>
#include <queue>
#include <cstdlib>
#include "config.h"

const int BasicSignalData::CACHE_LIMIT = 30000;

BasicSignalData::BasicSignalData( const std::string& name, bool wavedata )
: label( name ), firstdata( std::numeric_limits<dr_time>::max( ) ), lastdata( 0 ),
datacount( 0 ), livecount( 0 ), popping( false ), iswave( wavedata ),
highval( -std::numeric_limits<double>::max( ) ),
lowval( std::numeric_limits<double>::max( ) ) {
  scale( 0 );
  setChunkIntervalAndSampleRate( 2000, 1 );
  setUom( "Uncalib" );

  setMeta( SignalData::MSM, SignalData::MISSING_VALUE );
  setMeta( SignalData::TIMEZONE, "UTC" );
  setMeta( "Note on Scale", "To get from a scaled value back to the real value, divide by 10^<scale>" );
}

BasicSignalData::~BasicSignalData( ) {
  data.clear( );
  if ( file.is_open( ) ) {
    file.close( );
  }
}

std::unique_ptr<SignalData> BasicSignalData::shallowcopy( bool includedates ) {
  std::unique_ptr<BasicSignalData> copy( new BasicSignalData( label ) );

  if ( includedates ) {
    copy->firstdata = this->firstdata;
    copy->lastdata = this->lastdata;
  }

  for ( auto x : metad( ) ) {
    copy->setMeta( x.first, x.second );
  }
  for ( auto x : metai( ) ) {
    copy->setMeta( x.first, x.second );
  }
  for ( auto x : metas( ) ) {
    copy->setMeta( x.first, x.second );
  }
  copy->popping = this->popping;
  for ( std::string& s : extras( ) ) {
    copy->extras( ).push_back( s );
  }
  return std::move( copy );
}

dr_time BasicSignalData::startTime( ) const {
  return firstdata;
}

dr_time BasicSignalData::endTime( ) const {
  return lastdata;
}

std::unique_ptr<DataRow> BasicSignalData::pop( ) {
  if ( !popping ) {
    startPopping( );
  }

  if ( file.is_open( ) && data.empty( ) ) {
    int lines = uncache( );
    livecount += lines;
    if ( 0 == lines ) {
      file.close( );
    }
  }

  datacount--;
  livecount--;
  std::unique_ptr<DataRow> row = std::move( data.front( ) );
  data.pop_front( );
  dates.pop_front( );
  return row;
}

size_t BasicSignalData::size( ) const {
  return datacount;
}

const std::string& BasicSignalData::name( ) const {
  return label;
}

void BasicSignalData::startPopping( ) {
  popping = true;
  if ( file.is_open( ) ) {
    cache( ); // copy any extra rows to disk
    file.seekg( 0, std::ios::beg );
  }
}

double BasicSignalData::highwater( ) const {
  return highval;
}

double BasicSignalData::lowwater( ) const {
  return lowval;
}

void BasicSignalData::cache( ) {
  std::cout << "caching signal data" << std::endl;

  if ( file.is_open() ) {
#ifdef __CYGWIN__
    std::string fname( "c:\\temp\\" + std::to_string( rand( ) ) );
    fname += ( iswave ? "-wave.tmp" : "-vital.tmp" );
    std::cout << "\t0 cache file: " << fname << std::endl;
    //    char * tmpdir = getenv( "TMP" );
    //    std::cout << "\t1 cache file: " << fname << std::endl;
    //    if ( nullptr == tmpdir ) {
    //      tmpdir = getenv( "TEMP" );
    //    }
    //    if ( nullptr != tmpdir ) {
    //      fname = tmpdir + dirsep + fname;
    //    }

    file.open( fname.c_str( ) );
    if ( file.is_open( ) ) {
      std::cout << "opened" << std::endl;
      file << "this is a test" << std::endl;
    }
#else
    std::cout << "skipping cygwin ifdef" << std::endl;
    file.open( tmpnam( nullptr ) );
#endif
  }

  std::cout << "here 0" << std::endl;
  while ( !data.empty( ) ) {
    std::unique_ptr<DataRow> a = std::move( data.front( ) );
    data.pop_front( );
    std::cout << "popped; size: " << data.size( ) << std::endl;
    file << a->time << " " << a->data << " " << a->high << " " << a->low << " ";
    if ( !a->extras.empty( ) ) {
      for ( const auto& x : a->extras ) {
        file << "|" << x.first << "=" << x.second;
      }
    }
    file << std::endl;
  }

  std::cout << "here 2" << std::endl;
  livecount = 0;
}

void BasicSignalData::add( const DataRow& row ) {

  if ( livecount >= CACHE_LIMIT ) {
    // copy current data list to disk
    cache( );
  }

  datacount++;
  livecount++;

  int rowscale = DataRow::scale( row.data, iswave );
  DataRow::hilo( row.data, highval, lowval );
  int myscale = scale( );
  if ( rowscale > myscale ) {
    scale( rowscale );
  }

  if ( !row.extras.empty( ) ) {
    for ( const auto& x : row.extras ) {
      extras( x.first );
    }
  }

  DataRow * lastins = new DataRow( row );
  data.push_back( std::unique_ptr<DataRow>( lastins ) );

  if ( row.time > lastdata ) {
    lastdata = row.time;
  }
  if ( row.time < firstdata ) {
    firstdata = row.time;
  }
  dates.push_front( row.time );
}

void BasicSignalData::setWave( bool wave ) {
  iswave = wave;
}

bool BasicSignalData::wave( ) const {
  return iswave;
}

int BasicSignalData::uncache( int max ) {
  int loop = 0;

  std::string read;
  while ( loop < max && std::getline(read, file)) {
    // first things first: if we have attributes, cut them out 
    const size_t barpos = read.find( "|" );
    std::string extras;
    if ( std::string::npos != barpos ) {
      // we have attributes!
      extras = read.substr( barpos + 1 );
      read = read.substr( 0, barpos );
    }

    std::stringstream ss( read );
    dr_time t;
    std::string val;
    std::string high;
    std::string low;

    ss >> t;
    ss >> val;
    ss >> high;
    ss >> low;

    std::map<std::string, std::string> attrs;
    if ( !extras.empty( ) ) {
      // split on |, then split again on "="
      std::string token;
      std::stringstream extrastream( extras );
      while ( std::getline( extrastream, token, '|' ) ) {
        // now split on =
        int eqpos = token.find( "=" );
        std::string key = token.substr( 0, eqpos );
        std::string val = token.substr( eqpos + 1 );

        // strip the \n if it's there
        const size_t newlinepos = val.rfind( "\n" );
        if ( std::string::npos != newlinepos ) {
          val = val.substr( 0, newlinepos );
        }
        attrs[key] = val;
      }
    }


    data.push_back( std::unique_ptr<DataRow>( new DataRow( t, val, high, low, attrs ) ) );
    loop++;
  }

  return loop;
}

const std::deque<dr_time> BasicSignalData::times( ) const {
  return std::deque<dr_time>( dates.begin( ), dates.end( ) );
}

void BasicSignalData::setMetadataFrom( const SignalData& model ) {
  metadatai.clear( );
  metadatai.insert( model.metai( ).begin( ), model.metai( ).end( ) );

  metadatas.clear( );
  metadatas.insert( model.metas( ).begin( ), model.metas( ).end( ) );

  metadatad.clear( );
  metadatad.insert( model.metad( ).begin( ), model.metad( ).end( ) );

  extrafields.clear( );
  std::vector<std::string> vec = model.extras( );
  extrafields.insert( vec.begin( ), vec.end( ) );
}

std::vector<std::string> BasicSignalData::extras( ) const {
  return std::vector<std::string>( extrafields.begin( ), extrafields.end( ) );
}

void BasicSignalData::extras( const std::string& ext ) {
  extrafields.insert( ext );
}

void BasicSignalData::setMeta( const std::string& key, const std::string& val ) {
  metadatas[key] = val;
}

void BasicSignalData::setMeta( const std::string& key, int val ) {
  metadatai[key] = val;
}

void BasicSignalData::setMeta( const std::string& key, double val ) {
  metadatad[key] = val;
}

void BasicSignalData::erases( const std::string& key ) {
  if ( "" == key ) {
    metadatas.clear( );
  }
  else {
    metadatas.erase( key );
  }
}

void BasicSignalData::erasei( const std::string& key ) {
  if ( "" == key ) {
    metadatai.clear( );
  }
  else {
    metadatai.erase( key );
  }
}

void BasicSignalData::erased( const std::string& key ) {
  if ( "" == key ) {
    metadatad.clear( );
  }
  else {
    metadatad.erase( key );
  }
}

const std::map<std::string, std::string>& BasicSignalData::metas( ) const {
  return metadatas;
}

const std::map<std::string, int>& BasicSignalData::metai( ) const {
  return metadatai;
}

const std::map<std::string, double>& BasicSignalData::metad( ) const {
  return metadatad;
}

void BasicSignalData::recordEvent( const std::string& eventtype, const dr_time& time ) {
  if ( 0 == namedevents.count( eventtype ) ) {
    namedevents[eventtype] = std::vector<dr_time>( );
    namedevents[eventtype].push_back( time );
  }
  else {
    auto& list = namedevents[eventtype];
    if ( list[list.size( ) - 1] != time ) {
      list.push_back( time );
    }
  }
}

std::vector<std::string> BasicSignalData::eventtypes( ) {
  std::vector<std::string> keys;
  for ( auto& x : namedevents ) {
    keys.push_back( x.first );
  }
  return keys;
}

std::vector<dr_time> BasicSignalData::events( const std::string& type ) {
  return ( 0 == namedevents.count( type )
          ? std::vector<dr_time>( )
          : namedevents.at( type ) );
}

