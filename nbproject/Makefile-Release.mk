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
CCC=arm-linux-gnueabi-g++
CXX=arm-linux-gnueabi-g++
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
	${OBJECTDIR}/Action.o \
	${OBJECTDIR}/Behaviour.o \
	${OBJECTDIR}/ButtonTest.o \
	${OBJECTDIR}/ColorUtils.o \
	${OBJECTDIR}/Command.o \
	${OBJECTDIR}/CommandMotor.o \
	${OBJECTDIR}/Communication.o \
	${OBJECTDIR}/DriveTest.o \
	${OBJECTDIR}/EV3Buttons.o \
	${OBJECTDIR}/EV3Config.o \
	${OBJECTDIR}/EV3Motor.o \
	${OBJECTDIR}/EV3Status.o \
	${OBJECTDIR}/Ev3Main.o \
	${OBJECTDIR}/LedControl.o \
	${OBJECTDIR}/Message.o \
	${OBJECTDIR}/MessageQueue.o \
	${OBJECTDIR}/Program.o \
	${OBJECTDIR}/Robot.o \
	${OBJECTDIR}/RobotModelA.o \
	${OBJECTDIR}/SignalHandler.o \
	${OBJECTDIR}/ev3dev.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-D_GLIBCXX_USE_NANOSLEEP -pthread
CXXFLAGS=-D_GLIBCXX_USE_NANOSLEEP -pthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ev3dev

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ev3dev: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ev3dev ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Action.o: Action.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Action.o Action.cpp

${OBJECTDIR}/Behaviour.o: Behaviour.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Behaviour.o Behaviour.cpp

${OBJECTDIR}/ButtonTest.o: ButtonTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ButtonTest.o ButtonTest.cpp

${OBJECTDIR}/ColorUtils.o: ColorUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ColorUtils.o ColorUtils.cpp

${OBJECTDIR}/Command.o: Command.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Command.o Command.cpp

${OBJECTDIR}/CommandMotor.o: CommandMotor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandMotor.o CommandMotor.cpp

${OBJECTDIR}/Communication.o: Communication.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Communication.o Communication.cpp

${OBJECTDIR}/DriveTest.o: DriveTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DriveTest.o DriveTest.cpp

${OBJECTDIR}/EV3Buttons.o: EV3Buttons.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EV3Buttons.o EV3Buttons.cpp

${OBJECTDIR}/EV3Config.o: EV3Config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EV3Config.o EV3Config.cpp

${OBJECTDIR}/EV3Motor.o: EV3Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EV3Motor.o EV3Motor.cpp

${OBJECTDIR}/EV3Status.o: EV3Status.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EV3Status.o EV3Status.cpp

${OBJECTDIR}/Ev3Main.o: Ev3Main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ev3Main.o Ev3Main.cpp

${OBJECTDIR}/LedControl.o: LedControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LedControl.o LedControl.cpp

${OBJECTDIR}/Message.o: Message.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Message.o Message.cpp

${OBJECTDIR}/MessageQueue.o: MessageQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MessageQueue.o MessageQueue.cpp

${OBJECTDIR}/Program.o: Program.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Program.o Program.cpp

${OBJECTDIR}/Robot.o: Robot.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robot.o Robot.cpp

${OBJECTDIR}/RobotModelA.o: RobotModelA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RobotModelA.o RobotModelA.cpp

${OBJECTDIR}/SignalHandler.o: SignalHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SignalHandler.o SignalHandler.cpp

${OBJECTDIR}/ev3dev.o: ev3dev.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ev3dev.o ev3dev.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ev3dev

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
