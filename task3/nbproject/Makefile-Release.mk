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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/camera.o \
	${OBJECTDIR}/src/figures/geom.o \
	${OBJECTDIR}/src/figures/textures.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/objloader.o \
	${OBJECTDIR}/src/shader.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs glew` `pkg-config --libs libglfw`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task3

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task3: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task3 ${OBJECTFILES} ${LDLIBSOPTIONS} -lGLEW -lGL -lglfw

${OBJECTDIR}/src/camera.o: src/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/camera.o src/camera.cpp

${OBJECTDIR}/src/figures/geom.o: src/figures/geom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/figures
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/figures/geom.o src/figures/geom.cpp

${OBJECTDIR}/src/figures/textures.o: src/figures/textures.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/figures
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/figures/textures.o src/figures/textures.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/objloader.o: src/objloader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/objloader.o src/objloader.cpp

${OBJECTDIR}/src/shader.o: src/shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I/usr/include/ImageMagick `pkg-config --cflags glew` `pkg-config --cflags libglfw` -std=c++11  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/shader.o src/shader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task3

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
