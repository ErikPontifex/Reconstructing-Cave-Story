SDLFLAGS = $(shell sdl2-config --libs --cflags)

game:
mkdir -p build

g++ \

src/main.cpp \

-o build/main \

$(SDLFLAGS) \

-framework OpenGL \

-std=c++14 \

-g
