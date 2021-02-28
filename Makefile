CC = gcc
CFLAGS = -g -Wall
TARGET = smpbashshell

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Clean the directory
clean: 
	$(RM) $(TARGET)
