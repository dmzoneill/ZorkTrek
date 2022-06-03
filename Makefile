.PHONY: run build run-debug build-debug valgrind clean deps push

CC = g++
CFLAGS = -pthread -O2 -Wall -w -g
LDFLAGS = `sdl-config --cflags --libs` -lpthread -lSDL -lGL -lGLU -lfreetype -lSDL_ttf -lSDL_image -lSDL_mixer 

INCLUDES = -I ./source/header
SRCS = ./source/source/*.cpp
MAIN = zorktrek

run: build
	./source/bin/zorktrek

build: deps clean
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o ./source/bin/$(MAIN) $(LDFLAGS) 

run-debug: build-debug
	./source/debug/zorktrek

build-debug: deps clean
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o ./source/debug/$(MAIN) $(LDFLAGS)

valgrind: build-debug
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v --track-origins=yes ./source/debug/zorktrek	

clean: 
	find . -iname "*~" -exec rm {} \;
	- rm -f ./source/bin/$(MAIN)
	- rm -f ./source/debug/$(MAIN)

deps:
	sudo apt install libsdl-console \
		libsdl-console-dev \
		libsdl-gfx1.2-5 \
		libsdl-gfx1.2-dev \
		libsdl-gfx1.2-doc \
		libsdl-image1.2 \
		libsdl-image1.2-dev \
		libsdl-kitchensink-dev \
		libsdl-kitchensink1 \
		libsdl-mixer1.2 \
		libsdl-mixer1.2-dev \
		libsdl-net1.2 \
		libsdl-net1.2-dev \
		libsdl-ocaml \
		libsdl-ocaml-dev \
		libsdl-pango-dev \
		libsdl-pango1 \
		libsdl-perl \
		libsdl-sge \
		libsdl-sge-dev \
		libsdl-sound1.2 \
		libsdl-sound1.2-dev \
		libsdl-ttf2.0-0 \
		libsdl-ttf2.0-dev \
		libsdl1.2-compat \
		libsdl1.2-compat-dev \
		libsdl1.2-compat-shim \
		libsdl1.2-compat-tests \
		libsdl2-2.0-0 \
		libsdl2-dev \
		libsdl2-doc \
		libsdl2-gfx-1.0-0 \
		libsdl2-gfx-dev \
		libsdl2-gfx-doc \
		libsdl2-image-2.0-0 \
		libsdl2-image-dev \
		libsdl2-mixer-2.0-0 \
		libsdl2-mixer-dev \
		libsdl2-net-2.0-0 \
		libsdl2-net-dev \
		libsdl2-tests \
		libsdl2-ttf-2.0-0 \
		libsdl2-ttf-dev

push: clean
	git add -A
	git commit -a -m "latest"
	git push -f

