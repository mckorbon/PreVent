/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hdf5Writer.h
 * Author: ryan
 *
 * Created on August 26, 2016, 12:58 PM
 */

#ifndef HDF5WRITER_H
#define HDF5WRITER_H

#include <H5Cpp.h>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include "Writer.h"


class SignalData;

class Hdf5Writer : public Writer {
public:
	Hdf5Writer( );
	virtual ~Hdf5Writer( );

protected:
	int initDataSet( const std::string& outdir, const std::string& namestart,
			int compression );
	std::vector<std::string> closeDataSet( );
	int drain( SignalSet& );

private:

	Hdf5Writer( const Hdf5Writer& orig );

	static void writeFileAttributes( H5::H5File file, std::map<std::string, std::string> datasetattrs,
			const time_t& firsttime, const time_t& lasttime );
	static void writeAttribute( H5::H5Location& loc,
			const std::string& attr, const std::string& val );
	static void writeAttribute( H5::H5Location& loc,
			const std::string& attr, int val );
	static void writeAttribute( H5::H5Location& loc,
			const std::string& attr, double val );
	static void writeTimesAndDurationAttributes( H5::H5Location& loc,
			const time_t& start, const time_t& end );
	static void writeAttributes( H5::DataSet& ds, const SignalData& data );
	static void writeVital( H5::DataSet& ds, H5::DataSpace& space, SignalData& data );
	static void writeWave( H5::DataSet& ds, H5::DataSpace& space, SignalData& data );
	static void autochunk( hsize_t* dims, int rank, hsize_t* rslts );
	void createEvents( H5::H5File, const SignalSet& data );

	std::string tempfileloc;
	int compression;
	SignalSet * dataptr;
};

#endif /* HDF5WRITER_H */
