make: clean build run

build: src/render.c
	gcc -g \
	-Iinclude \
	-lSDL2 -lglfw \
	-o triangle \
	src/glad.c src/render.c

run: build
	./triangle

clean:
	rm -f triangle
