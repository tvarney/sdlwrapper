
# Tools
CXX  := g++
AR   := ar

# Target Names
TARGET := libSDLWrapper.a
TOOL := sdlwrap-config

# Source variables
SRC  := ./source
INC  := ./include
BIN  := ./build

# Flag marking install type
USER_INSTALL := no

# Subdirectories of $PREFIX used by install and user-install
BINDIR := bin
LIBDIR := lib
INCDIR := include
ROOT_PREFIX := /usr/local
USER_PREFIX := ${HOME}

# Flag controlling which standard of C++ we compile with
STD := -std=c++11

# Get platform specific flags
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
PLATFORM := -DPLATFORM_DARWIN
LIBS := -framework OpenGL -lpthread -lpng
else
PLATFORM := -DPLATFORM_LINUX
LIBS := -lGLU -lGL -lpthread -lm -lpng
endif

# Compilation and packing flags
CPPFLAGS := -Wall -Werror ${STD} -I${INC} $(shell sdl2-config --cflags) ${PLATFORM} -ggdb
ARFLAGS := rcs

# Auto creation of 
OBJECTS = $(patsubst ${SRC}/%.cpp, ${BIN}/%.o, $(wildcard ${SRC}/*.cpp))
TARGET := ${BIN}/${TARGET}

.PHONEY: all fresh clean builddir

all: ${TARGET}

fresh: clean all

clean:
	rm ${BIN}/*.o ${TARGET}

builddir: ${BIN}/.flag

install: PREFIX=${ROOT_PREFIX}
install: doinstall

user-install: PREFIX=${USER_PREFIX}
user-install: doinstall

doinstall: ${TARGET} ${PREFIX}/${BINDIR}/${TOOL}
	cp ${TARGET} ${PREFIX}/${LIBDIR}/
	cp -R ${INC}/SDLWrap ${PREFIX}/${INCDIR}

${BIN}/.flag:
	mkdir -p ${BIN}
	touch ${BIN}/.flag

${TARGET}: builddir ${OBJECTS}
	${AR} ${ARFLAGS} ${TARGET} ${OBJECTS}

${BIN}/%.o: ${SRC}/%.cpp
	${CXX} -c ${CPPFLAGS} -o $@ $<

${PREFIX}/${BINDIR}/${TOOL}:
	echo "#!/bin/sh" > ${PREFIX}/${BINDIR}/${TOOL}
	echo >> ${PREFIX}/${BINDIR}/${TOOL}
	echo "prefix=${PREFIX}" >> ${PREFIX}/${BINDIR}/${TOOL}
	echo "libext=${LIBDIR}" >> ${PREFIX}/${BINDIR}/${TOOL}
	cat ${TOOL}.in >> ${PREFIX}/${BINDIR}/${TOOL}
	chmod +x ${PREFIX}/${BINDIR}/${TOOL}
