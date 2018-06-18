/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DurationSignalData.h"
#include "DataRow.h"
#include "DurationSpecification.h"

DurationSignalData::DurationSignalData( SignalData * data, const DurationSpecification& dur )
: SignalDataWrapper( data ), spec( dur ) {
}

DurationSignalData::~DurationSignalData( ) {
}

void DurationSignalData::add( const DataRow& row ) {
  if ( spec.accepts( row.time ) ) {
    SignalDataWrapper::add( row );
  }
}
