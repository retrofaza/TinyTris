TARGET ?= TinytrisAROS

CC        := x86_64-aros-gcc
OBJS       = Widjet.o tinytrisPC.o

SYSROOT     := $(shell $(CC) --print-sysroot)
SDL_CONFIG  := $(SYSROOT)/bin/sdl-config
SDL_CFLAGS  := $(shell $(SDL_CONFIG) --cflags)
SDL_LIBS    := $(shell $(SDL_CONFIG) --libs) -lm -lSDL_image -lSDL_mixer -ljpeg -lpng -lmikmod -lvorbisfile -lvorbis -logg

HEADERS     += Widjet.h

CFLAGS       = $(SDL_CFLAGS) -Wall -Wno-unused-variable \
               -O2 -fomit-frame-pointer $(DEFS) $(INCLUDE)
LDFLAGS     := $(SDL_LIBS) -s

include Makefile.rules

.PHONY: all

all: $(TARGET)

$(TARGET): $(OBJS)