CC = g++
Project = main
SRC = main.cpp
LIBS = `pkg-config --cflags --libs opencv4`
$(Project) : $(SRC)
	$(CC) -std=c++17 -g $(SRC) -o $(Project) $(LIBS)


clean:
	rm -fR $(Project) *.o 

