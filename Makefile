
PROJECT = NetConnection
TARGET  = lib$(PROJECT).so
PREFIX  = $(HOME)/.local


SRCDIR=./src


INC_DIR= $(.INCLUDE_DIRS) \
         $(HOME)/.local/include

INC_DIRS=$(INC_DIR:%=-I%)

CXXFLAGS= -Wall -fPIC -g $(INC_DIRS)

LDFLAGS= -lcurl

SOURCES=\
	$(SRCDIR)/NetConnection.cpp

OBJECTS=\
	$(SOURCES:.cpp=.o)

.PHONY: all clean install uninstall

all: $(TARGET)


clean:
						rm -rf ./src/*.o

$(TARGET): $(OBJECTS)
						$(CXX) -shared $(LDFLAGS) $(CXXFLAGS)  $(SOURCES) -o $@

# .cpp.o:
# 						$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $(SOURCES)

install:
						install $(TARGET) $(PREFIX)/lib/; \
						mkdir -p $(PREFIX)/include/$(PROJECT); \
						install $(SRCDIR)/*.h $(PREFIX)/include/$(PROJECT)/

uninstall:
						rm -rf $(PREFIX)/lib/$(TARGET);
						rm -rf $(PREFIX)/include/$(PROJECT)
