


CXX = g++

CXX_FLAGS = -std=c++11 -Wall -Wextra

JOYSTICK_CALIB_TEST = JoystickCalibTest

all: $(JOYSTICK_CALIB_TEST)

$(JOYSTICK_CALIB_TEST): JoystickCalib.h JoystickCalib.cpp JoystickCalibTest.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@

