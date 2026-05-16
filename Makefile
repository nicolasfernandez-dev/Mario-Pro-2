CXX = g++
CXXFLAGS = -std=c++17 -Iinclude 

ifeq "$(MODE)" "release"
    CXXFLAGS += -O3
else
    CXXFLAGS += -g3
endif

ifeq ($(OS),Windows_NT)
    LDFLAGS += -lgdi32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS += -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS += -framework Cocoa
    endif
endif

CCFILES := $(wildcard src/*.cc)
HHFILES := $(wildcard include/*.hh)
OBJS := $(patsubst src/%.cc,build/%.o,$(CCFILES))
TAR_FILE = mario-pro-2-$(USER)-$(shell date +%s).tgz

mario_pro_2: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mario_pro_2 $(OBJS) $(LDFLAGS)

build/%.o: src/%.cc $(HHFILES)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/window.o: src/window.cc include/geometry.hh include/fenster.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

tgz: clean
	tar -czf $(TAR_FILE) Makefile src/ include/ .vscode .clang-format

clean:
	rm -rf mario_pro_2 build/*.o

.PHONY: clean tgz