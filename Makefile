CC = gcc
SRCS = prank.c
TARGET = prank
all:
	$(CC) $(SRCS) -o $(TARGET) -lmpg123 -lao
clean:
	rm -f $(TARGET)
	rm -f dude.mp3
