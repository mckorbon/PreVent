bin_PROGRAMS = preventtools

CXX = h5c++

preventtools_SOURCES = AttributeUtils.cpp  ClippingSignalSet.cpp  H5Cat.cpp  main.cpp  OutputSignalData.cpp  TimeParser.cpp

AM_CXXFLAGS = -I../libtdms/include -I../Formats @zlib_CFLAGS@ @expat_CFLAGS@ @WFDB_CFLAGS@

ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS=-L../libtdms/.libs -ltdms -L../Formats/.libs -lFormats @zlib_LIBS@ @matio_LIBS@ @expat_LIBS@ @WFDB_LIBS@ -lstdc++fs /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so 

