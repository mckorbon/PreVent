/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReadInfo.h
 * Author: ryan
 *
 * Created on July 10, 2017, 8:02 AM
 */

#ifndef SIGNALSET_H
#define SIGNALSET_H

#include "DataRow.h"
#include "SignalDataIterator.h"
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

class SignalData;
class PartionedSignalData;

enum TimeCounter {
  VITAL, WAVE, EITHER
};

class SignalSet {
public:
  SignalSet();
  virtual ~SignalSet( );
  virtual std::vector<std::unique_ptr<SignalData>>&vitals( ) =0;
  virtual std::vector<std::unique_ptr<SignalData>>&waves( ) =0;

  virtual const std::vector<std::unique_ptr<SignalData>>&vitals( ) const =0;
  virtual const std::vector<std::unique_ptr<SignalData>>&waves( ) const =0;

  std::vector<std::reference_wrapper<const std::unique_ptr<SignalData>>>allsignals( ) const;

  virtual const std::map<std::string, std::string>& metadata( ) const;

  /**
   * Adds a new vital sign if it has not already been added. If it already
   * exists, the old dataset is returned
   * @param name
   * @param if not NULL, will be set to true if this is the first time this function
   *  has been called for this vital
   * @return
   */
  virtual std::unique_ptr<SignalData>& addVital( const std::string& name, bool * added = nullptr ) = 0;
  /**
   * Adds a new waveform if it has not already been added. If it already
   * exists, the old dataset is returned
   * @param name
   * @param if not NULL, will be set to true if this is the first time this function
   *  has been called for this vital
   * @return
   */
  virtual std::unique_ptr<SignalData>& addWave( const std::string& name, bool * added = nullptr ) = 0;
  virtual void setMeta( const std::string& key, const std::string& val );
  virtual void reset( bool signalDataOnly = true );
  virtual void clearMetas();
  void setFileSupport( bool );
  virtual dr_time earliest( const TimeCounter& tc = EITHER ) const = 0;
  virtual dr_time latest( const TimeCounter& tc = EITHER ) const = 0;
  virtual void setMetadataFrom( const SignalSet& target );
  const std::map<long, dr_time>& offsets( ) const;
  void addOffset( long seg, dr_time time );
  void clearOffsets( );
  //void moveTo( SignalSet& dest );

private:
  std::map<std::string, std::string> metamap;
  std::map<long, dr_time> segs; // segment index->time

  //friend class SignalSetWrapper;
};

#endif /* SIGNALSET_H */

