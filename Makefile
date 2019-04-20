CC = g++

all:
	@-$(CC) ./src/*.cpp ./src/obj_loader/*.cpp -lopengl32 -lglut32 -I. -o ./build/cgprog -std=c++11

clean:
	rm cgprog

