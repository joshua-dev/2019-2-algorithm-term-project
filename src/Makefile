CC = g++
CFLAGS = -std=c++11
SOURCES = main.cpp
TARGET = pushbox

$(TARGET):
	$(CC) $(CFLAGS) -o $@ $(SOURCES) -lncurses

all:
		$(TARGET)

clean:
		rm -f $(TARGET)
