
#include "ToWriter.h"

#include "Hdf5Writer.h"
#include "FromReader.h"
#include <sys/stat.h>
#include "config.h"

ToWriter::ToWriter( ) {
}

ToWriter::ToWriter( const ToWriter& ) {

}

ToWriter::~ToWriter( ) {
}

std::unique_ptr<ToWriter> ToWriter::get( const Format& fmt ) {
  switch ( fmt ) {
    case HDF5:
      return std::unique_ptr<ToWriter>( new Hdf5Writer( ) );
  }
}

void ToWriter::setOutputPrefix( const std::string& pre ) {
  prefix = pre;
}

void ToWriter::setCompression( int lev ) {
  compression = lev;
}

void ToWriter::setOutputDir( const std::string& _outdir ) {
  outdir = _outdir;

  struct stat info;
  if ( stat( outdir.c_str( ), &info ) != 0 ) {
    mkdir( outdir.c_str( ), S_IRWXU | S_IRWXG );
  }

  size_t extpos = outdir.find_last_of( dirsep, outdir.length( ) );
  if ( outdir.length( ) - 1 != extpos || extpos < 0 ) {
    // doesn't end with a dirsep, so add it
    outdir += dirsep;
  }
}

std::vector<std::string> ToWriter::write( std::unique_ptr<FromReader>& from,
    ReadInfo& data ) {
  int retcode = from->next( data );
  std::vector<std::string> list;

  initDataSet( outdir + prefix + "-p" + std::to_string( list.size( ) + 1 ),
      compression );

  while ( retcode >= -1 ) {
    writeChunk( data );

    if ( 0 == retcode ) {
      // end of old patient
      list.push_back( closeDataSet( ) );
      initDataSet( outdir + prefix + "-p" + std::to_string( list.size( ) + 1 ),
          compression );
    }
    else if ( -1 == retcode ) {
      // end of file, so break out of our write
      list.push_back( closeDataSet( ) );
      break;
    }

    // carry on with next data chunk
    retcode = from->next( data );
  }

  return list;
}

