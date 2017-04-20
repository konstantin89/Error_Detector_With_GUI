#Push changes to github.
#git push -u origin master



CXX = g++

CXX_FLAGS = -std=c++11 -Wall -Wextra -lwiringPi -lpthread -lsfml-graphics -lsfml-window -lsfml-system
DEBUG_FLAG = -DDEBUG=1

#Derectory for object and executable files.
OBJDIR = ./ObjsAndExecs/
AD7992_DIR = ./AD9772_Comm_Module/
ERR_DET_DIR = ./Error_Detector/
GRAPH_DIR = ./Graphics/

JOYSTICK_CALIB_DIR = ../error_gui/JoystickCalibrationFiles/


AD9772_MAIN = $(OBJDIR)AD9772_Comm_Main
ERROR_DETECTOR_MAIN = $(OBJDIR)errorDetector
JOYSTICK_CALIBRATION_PROC = $(OBJDIR)joysticCalibration

all: $(AD9772_MAIN) $(ERROR_DETECTOR_MAIN)   $(JOYSTICK_CALIBRATION_PROC)


$(ERROR_DETECTOR_MAIN): $(OBJDIR)A2D_Comm_I2C.o $(OBJDIR)AD9772_Comm.o \
                $(OBJDIR)errorDetector.o $(OBJDIR)Graphics.o $(OBJDIR)pointerLocation.o\
		        $(ERR_DET_DIR)Sample.h $(ERR_DET_DIR)errordetectorParameters.h \
		        $(OBJDIR)LogModule.o $(ERR_DET_DIR)Sample.h \
	$(CXX) $(CXX_FLAGS) $^ -o $@

$(AD9772_MAIN): $(OBJDIR)A2D_Comm_I2C.o $(OBJDIR)AD9772_Comm.o  $(AD7992_DIR)AD9772_Comm_Main.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

$(OBJDIR)errorDetector.o: $(ERR_DET_DIR)errorDetector.cpp $(ERR_DET_DIR)errorDetector.h\
	$(JOYSTICK_CALIB_DIR)JoystickCalib.h $(JOYSTICK_CALIB_DIR)JoystickCalib.cpp

	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(OBJDIR)AD9772_Comm.o: $(AD7992_DIR)AD9772_Comm.cpp $(AD7992_DIR)AD9772_Comm.h 
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(OBJDIR)Graphics.o: $(GRAPH_DIR)GameLogic.cpp $(GRAPH_DIR)GameLogic.h 
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(OBJDIR)pointerLocation.o: $(ERR_DET_DIR)pointerLocation.cpp $(ERR_DET_DIR)pointerLocation.h 
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(OBJDIR)A2D_Comm_I2C.o: $(AD7992_DIR)A2D_Comm_I2C.cpp $(AD7992_DIR)A2D_Comm_I2C.hpp \
	                     $(AD7992_DIR)A2D_Communication.hpp
	$(CXX) $(CXX_FLAGS)  -c $< -o $@
	
	 
$(OBJDIR)LogModule.o: $(ERR_DET_DIR)LogModule.cpp $(ERR_DET_DIR)LogModule.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@


$(JOYSTICK_CALIBRATION_PROC): $(ERR_DET_DIR)joysticCalibration.cpp\
	                     $(OBJDIR)AD9772_Comm.o \
	                     $(OBJDIR)A2D_Comm_I2C.o
	$(CXX) $(CXX_FLAGS)  $^ -o $@
	
# specify commands that are not files.
.PHONY: clean

#make clean
clean:
	rm -rf $(OBJDIR)*


