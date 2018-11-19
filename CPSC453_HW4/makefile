#makefile modified from: https://github.com/psettle/particles/blob/master/makefile
#(My own hobby project)
#config
DEBUG=0

#setup
SOURCES=
LIBS=
INCLUDE=

#header includes
INCLUDE += include
INCLUDE += include/GL
INCLUDE += include/GLFW

INCLUDE += Apps
INCLUDE += Core
INCLUDE += Polygon

#source includes
SOURCES += Core/AppManager.cpp
SOURCES += Core/Shader.cpp
SOURCES += Core/System.cpp
SOURCES += Core/Texture.cpp

SOURCES += Apps/RayTraceApp.cpp
SOURCES += Apps/RayTraceScene.cpp
SOURCES += Apps/SceneParser.cpp

SOURCES += Polygon/Polygon.cpp

#lib includes
LIBS += -lglfw
LIBS += -lGL
LIBS += linux-lib/libGLEW.a
LIBS += -lX11
LIBS += -ldl
LIBS += -lpthread

#more setup
EXECUTABLE=out/cpsc453_hw4.exe
EXECUTABLE_MAIN=Core/main.cpp
EXECUTABLE_MAIN_O=$(EXECUTABLE_MAIN:%.cpp=out/%.o)

ifeq ($(DEBUG), 1)
	FLAG_BUILD_MODE=-O0 -g
else
	FLAG_BUILD_MODE=-O3
endif

LDFLAGS=-Wall $(FLAG_BUILD_MODE)
CC=g++
CFLAGS=-c -Wall $(FLAG_BUILD_MODE)
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS_FINAL=$(OBJECTS:%.o=out/%.o)
OBJECTS_FINAL_PLUS_MAIN=$(OBJECTS_FINAL)
OBJECTS_FINAL_PLUS_MAIN+=$(EXECUTABLE_MAIN_O)
DEPENDENCIES=$(OBJECTS_FINAL:.o=.d)

INCLUDE_FORMATTED=$(addprefix -I, $(INCLUDE))

#targets
.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_FINAL) $(EXECUTABLE_MAIN_O)
	@$(CC) $(LDFLAGS) $(OBJECTS_FINAL) $(EXECUTABLE_MAIN_O) $(LIBS) -o $@
	@echo $@

$(OBJECTS_FINAL_PLUS_MAIN): out/%.o : %.cpp
	@mkdir -p out/$(dir $<)
	@$(CC) $(CFLAGS) $(INCLUDE_FORMATTED) $< -o $@
	@echo $<


.PHONY: clean
clean:
	@rm -rf out/*

-include $(DEPENDENCIES)
