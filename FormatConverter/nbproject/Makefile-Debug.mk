#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=h5c++
CXX=h5c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CacheFileReader.o \
	${OBJECTDIR}/DataRow.o \
	${OBJECTDIR}/DataSetDataCache.o \
	${OBJECTDIR}/Formats.o \
	${OBJECTDIR}/FromReader.o \
	${OBJECTDIR}/Hdf5Writer.o \
	${OBJECTDIR}/HdfWriter.o \
	${OBJECTDIR}/ToWriter.o \
	${OBJECTDIR}/WfdbReader.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wno-deprecated -O0 -pg -g `wfdb-config --cflags` 
CXXFLAGS=-Wno-deprecated -O0 -pg -g `wfdb-config --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs zlib` /usr/lib/x86_64-linux-gnu/libsz.so /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter: /usr/lib/x86_64-linux-gnu/libsz.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter ${OBJECTFILES} ${LDLIBSOPTIONS} `wfdb-config --libs`

${OBJECTDIR}/CacheFileReader.o: CacheFileReader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CacheFileReader.o CacheFileReader.cpp

${OBJECTDIR}/DataRow.o: DataRow.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataRow.o DataRow.cpp

${OBJECTDIR}/DataSetDataCache.o: DataSetDataCache.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataSetDataCache.o DataSetDataCache.cpp

${OBJECTDIR}/Formats.o: Formats.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Formats.o Formats.cpp

${OBJECTDIR}/FromReader.o: FromReader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FromReader.o FromReader.cpp

${OBJECTDIR}/Hdf5Writer.o: Hdf5Writer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Hdf5Writer.o Hdf5Writer.cpp

${OBJECTDIR}/HdfWriter.o: HdfWriter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HdfWriter.o HdfWriter.cpp

${OBJECTDIR}/ToWriter.o: ToWriter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ToWriter.o ToWriter.cpp

${OBJECTDIR}/WfdbReader.o: WfdbReader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WfdbReader.o WfdbReader.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags zlib` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsz.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhdf5.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhdf5_cpp.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/formatconverter

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
