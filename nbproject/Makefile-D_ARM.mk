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
CND_CONF=D_ARM
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Program.o \
	${OBJECTDIR}/src/action/Action.o \
	${OBJECTDIR}/src/action/Behaviour.o \
	${OBJECTDIR}/src/action/BehaviourState.o \
	${OBJECTDIR}/src/action/Command.o \
	${OBJECTDIR}/src/action/CommandMotor.o \
	${OBJECTDIR}/src/action/CommandSensor.o \
	${OBJECTDIR}/src/communication/CommUtils.o \
	${OBJECTDIR}/src/communication/Communication.o \
	${OBJECTDIR}/src/communication/Event.o \
	${OBJECTDIR}/src/communication/Message.o \
	${OBJECTDIR}/src/control/LedControl.o \
	${OBJECTDIR}/src/ev3dev/ev3dev.o \
	${OBJECTDIR}/src/master/Agent.o \
	${OBJECTDIR}/src/master/Master.o \
	${OBJECTDIR}/src/robot/Devices.o \
	${OBJECTDIR}/src/robot/Motor.o \
	${OBJECTDIR}/src/robot/Robot.o \
	${OBJECTDIR}/src/robot/RobotModelA.o \
	${OBJECTDIR}/src/robot/RobotState.o \
	${OBJECTDIR}/src/robot/Sensor.o \
	${OBJECTDIR}/src/utils/CircularBuffer.o \
	${OBJECTDIR}/src/utils/ColorUtils.o \
	${OBJECTDIR}/src/utils/EventQueue.o \
	${OBJECTDIR}/src/utils/Logger.o \
	${OBJECTDIR}/src/utils/Queue.o \
	${OBJECTDIR}/src/utils/SignalHandler.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-D_GLIBCXX_USE_NANOSLEEP -pthread -static-libstdc++ -std=c++11 -D__AGENT
CXXFLAGS=-D_GLIBCXX_USE_NANOSLEEP -pthread -static-libstdc++ -std=c++11 -D__AGENT

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

${OBJECTDIR}/src/Program.o: src/Program.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Program.o src/Program.cpp

${OBJECTDIR}/src/action/Action.o: src/action/Action.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/Action.o src/action/Action.cpp

${OBJECTDIR}/src/action/Behaviour.o: src/action/Behaviour.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/Behaviour.o src/action/Behaviour.cpp

${OBJECTDIR}/src/action/BehaviourState.o: src/action/BehaviourState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/BehaviourState.o src/action/BehaviourState.cpp

${OBJECTDIR}/src/action/Command.o: src/action/Command.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/Command.o src/action/Command.cpp

${OBJECTDIR}/src/action/CommandMotor.o: src/action/CommandMotor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/CommandMotor.o src/action/CommandMotor.cpp

${OBJECTDIR}/src/action/CommandSensor.o: src/action/CommandSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/action
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/action/CommandSensor.o src/action/CommandSensor.cpp

${OBJECTDIR}/src/communication/CommUtils.o: src/communication/CommUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/communication
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/communication/CommUtils.o src/communication/CommUtils.cpp

${OBJECTDIR}/src/communication/Communication.o: src/communication/Communication.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/communication
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/communication/Communication.o src/communication/Communication.cpp

${OBJECTDIR}/src/communication/Event.o: src/communication/Event.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/communication
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/communication/Event.o src/communication/Event.cpp

${OBJECTDIR}/src/communication/Message.o: src/communication/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/communication
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/communication/Message.o src/communication/Message.cpp

${OBJECTDIR}/src/control/LedControl.o: src/control/LedControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/control/LedControl.o src/control/LedControl.cpp

${OBJECTDIR}/src/ev3dev/ev3dev.o: src/ev3dev/ev3dev.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ev3dev
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ev3dev/ev3dev.o src/ev3dev/ev3dev.cpp

${OBJECTDIR}/src/master/Agent.o: src/master/Agent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/master
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/master/Agent.o src/master/Agent.cpp

${OBJECTDIR}/src/master/Master.o: src/master/Master.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/master
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/master/Master.o src/master/Master.cpp

${OBJECTDIR}/src/robot/Devices.o: src/robot/Devices.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/Devices.o src/robot/Devices.cpp

${OBJECTDIR}/src/robot/Motor.o: src/robot/Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/Motor.o src/robot/Motor.cpp

${OBJECTDIR}/src/robot/Robot.o: src/robot/Robot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/Robot.o src/robot/Robot.cpp

${OBJECTDIR}/src/robot/RobotModelA.o: src/robot/RobotModelA.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/RobotModelA.o src/robot/RobotModelA.cpp

${OBJECTDIR}/src/robot/RobotState.o: src/robot/RobotState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/RobotState.o src/robot/RobotState.cpp

${OBJECTDIR}/src/robot/Sensor.o: src/robot/Sensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/robot/Sensor.o src/robot/Sensor.cpp

${OBJECTDIR}/src/utils/CircularBuffer.o: src/utils/CircularBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/CircularBuffer.o src/utils/CircularBuffer.cpp

${OBJECTDIR}/src/utils/ColorUtils.o: src/utils/ColorUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/ColorUtils.o src/utils/ColorUtils.cpp

${OBJECTDIR}/src/utils/EventQueue.o: src/utils/EventQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/EventQueue.o src/utils/EventQueue.cpp

${OBJECTDIR}/src/utils/Logger.o: src/utils/Logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/Logger.o src/utils/Logger.cpp

${OBJECTDIR}/src/utils/Queue.o: src/utils/Queue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/Queue.o src/utils/Queue.cpp

${OBJECTDIR}/src/utils/SignalHandler.o: src/utils/SignalHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude/communication -Iinclude/control -Iinclude/ev3dev -Iinclude/master -Iinclude/robot -Iinclude/utils -Iinclude/action -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/SignalHandler.o src/utils/SignalHandler.cpp

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
