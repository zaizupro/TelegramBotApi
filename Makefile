##[==================================]##
PROJECT = NetConnection
TARGET  = lib$(PROJECT).so
PREFIX  = $(HOME)/.local
##[==================================]##

INC_DIR= $(.INCLUDE_DIRS) \
		 $(HOME)/.local/include

INC_DIRS=$(INC_DIR:%=-I%)

BUILD_DIR=./build
BIN_DIR=$(BUILD_DIR)/bin
LIB_DIR=$(BUILD_DIR)/lib
OBJ_DIR=$(BUILD_DIR)/obj

CXXFLAGS= -shared -Wall -fPIC $(INC_DIRS)

LDFLAGS= -lcurl

SRCDIR=./src

##[==================================]##
SOURCES=\
		$(SRCDIR)/NetConnection.cpp

OBJECTS := $(patsubst $(SRCDIR)/%.cpp, %.o, $(SOURCES))
##[==================================]##
.SUFFIXES: .c .cpp .h .o
.PHONY: all clear clean install uninstall directories

##[==================================]##
all: $(TARGET)

directories:
		@mkdir -p $(LIB_DIR)
		@mkdir -p $(OBJ_DIR)

debug: clean
		@CXXFLAGS+=-g make

$(TARGET): $(OBJECTS)
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(LIB_DIR)/$@ $(OBJ_DIR)/*.o

$(OBJECTS) : directories $(SOURCES)
		$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)/$@ $(SRCDIR)/$(patsubst %.o,%.cpp, $@)

install:
		mkdir -p $(PREFIX)/lib/
		install $(LIB_DIR)/$(TARGET) $(PREFIX)/lib/

uninstall:
		rm -rf $(PREFIX)/lib/$(TARGET)

clean:
		rm -rf $(OBJ_DIR)/*.o

clear: clean
		rm -fr $(BUILD_DIR)
