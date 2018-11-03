#
# **************************************************************
# *                Simple C++ Makefile Template                *
# *                                                            *
# * Original Author: Arash Partow (2003)  	(Thanks dude!) 		 *
# * Modified by : Francesco Feltrin (2018)      							 *
# * URL: http://www.partow.net/programming/makefile/index.html *
# *                                                            *
# * Copyright notice:                                          *
# * Free use of this C++ Makefile template is permitted under  *
# * the guidelines and in accordance with the the MIT License  *
# * http://www.opensource.org/licenses/MIT                     *
# *                                                            *
# **************************************************************
#

CXX      := -c++
#Add "-pedantic" if you wish
CXXFLAGS := -errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
#This is just the name of the executable which is published
TARGET   := testStat
INCLUDE  := -Iinclude/
#This is where to look for cpp and the MAIN,
#  	 $(wildcard src/test/*.cpp)
SRC      :=                      \
   $(wildcard src/actuators/*.cpp) \
   $(wildcard src/statistic/*.cpp) \
	 $(wildcard src/sensors/*.cpp) \
	 $(wildcard src/test/*.cpp)


OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
