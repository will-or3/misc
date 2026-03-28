CC = gcc

# gnu standard flags
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = add

SRC = add.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)


clean:
	rm -f $(TARGET) *.o

#just learned about this
.PHONY: all clean
