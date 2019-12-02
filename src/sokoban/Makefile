CC = g++
CFLAGS = -std=c++17
SOURCES = main.cpp GameController.cpp
TARGET = pushbox

$(TARGET):
	$(CC) $(CFLAGS) -o $@ $(SOURCES) -lncurses

all:
		$(TARGET)

clean:
		rm -f $(TARGET)
