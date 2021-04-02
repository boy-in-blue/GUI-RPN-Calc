all: sdl

rpn: rpn.o stack.o mylib.o
	clang -g -Wall -o rpn rpn.o stack.o mylib.o

rpn.o: rpn.c
	clang -c -g -Wall rpn.c

stack.o: stack.c
	clang -c -g -Wall stack.c

mylib.o: mylib.c
	clang -c -g -Wall mylib.c

clean:
	rm *.o

run:
	.\rpn.exe

COMPILER_FLAGS = -w -Wl, -subsystem,windows
INCLUDE_PATHS = -IC:/Users/Sohma/scoop/apps/sdl2/2.0.10/include/SDL2 -I./SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2
LIBRARY_PATHS = -LC:/Users/Sohma/scoop/apps/sdl2/2.0.10/lib -L./SDL2_image-2.0.5/x86_64-w64-mingw32/lib
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_Image

sdl:
	clang $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) rpn.c -o sdl stack.o mylib.o

