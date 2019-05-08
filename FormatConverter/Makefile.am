bin_PROGRAMS = formatconverter

CXX = h5c++

formatconverter_SOURCES = Db.cpp main.cpp

AM_CXXFLAGS = -shlib -I../libtdms/include -I../Formats @zlib_CFLAGS@ @expat_CFLAGS@ @WFDB_CFLAGS@ @sqlite3_CFLAGS@

ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS=-L../libtdms/.libs -ltdms -L../Formats/.libs -lFormats @zlib_LIBS@ @matio_LIBS@ @expat_LIBS@ @WFDB_LIBS@ @sqlite3_LIBS@ -lstdc++fs -dynamic -lhdf5 -lhdf5_cpp
#/usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so 

