lib_LTLIBRARIES = libFormats.la

CXX = h5c++

libFormats_la_SOURCES = 	AnonymizingSignalSet.cpp \
	Base64.cpp \
	BasicSignalData.cpp \
	BasicSignalSet.cpp \
	CpcXmlReader.cpp \
	CsvWriter.cpp \
	DataRow.cpp \
	FileNamer.cpp \
	Formats.cpp \
	Hdf5Reader.cpp \
	Hdf5Writer.cpp \
	MatWriter.cpp \
	NullReader.cpp \
	OffsetTimeSignalSet.cpp \
	Options.cpp \
	Reader.cpp \
	SignalData.cpp \
	SignalDataWrapper.cpp \
	SignalSet.cpp \
	SignalSetWrapper.cpp \
	SignalUtils.cpp \
	StpJsonReader.cpp \
	StpXmlReader.cpp \
	StreamChunkReader.cpp \
	TdmsReader.cpp \
	TimezoneOffsetTimeSignalSet.cpp \
	WfdbReader.cpp \
	WfdbWriter.cpp \
	Writer.cpp \
	XmlReaderBase.cpp \
	ZlReader2.cpp \
	ZlReader.cpp

include_HEADERS =	AnonymizingSignalSet.h \
	Base64.h \
	BasicSignalData.h \
	BasicSignalSet.h \
	build.h \
	config.h \
	ConversionListener.h \
	CpcXmlReader.h \
	CsvWriter.h \
	DataRow.h \
	dr_time.h \
	FileNamer.h \
	Formats.h \
	Hdf5Reader.h \
	Hdf5Writer.h \
	json.hpp \
	MatWriter.h \
	NullReader.h \
	OffsetTimeSignalSet.h \
	Options.h \
	Reader.h \
	SignalData.h \
	SignalDataIterator.h \
	SignalDataWrapper.h \
	SignalSet.h \
	SignalSetWrapper.h \
	SignalUtils.h \
	StpJsonReader.h \
	StpXmlReader.h \
	StreamChunkReader.h \
	TdmsReader.h \
	TimezoneOffsetTimeSignalSet.h \
	WfdbReader.h \
	WfdbWriter.h \
	Writer.h \
	XmlReaderBase.h \
	ZlReader2.h \
	ZlReader.h

AM_CXXFLAGS = -std=c++17 -I../libtdms/include @WFDB_CFLAGS@

ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS=-L../libtdms/.libs -ltdms @zlib_LIBS@ @matio_LIBS@ @expat_LIBS@ @WFDB_LIBS@ -lstdc++fs #/usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so 
