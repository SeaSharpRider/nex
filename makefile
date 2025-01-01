CC = gcc
CFLAGS = -Wall -Wextra -IC:/Users/Administrator/Downloads/glew/glew/include -IC:/Users/Administrator/Downloads/GLFW/glfw/include
LDFLAGS = -LC:/Users/Administrator/Downloads/glew/glew/lib/Release/x64 -lglew32 -lopengl32 -LC:\Users\Administrator\Downloads\GLFW\glfw\lib-mingw-w64 -lglfw3 -lgdi32
TARGET = nex
SOURCES = main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
