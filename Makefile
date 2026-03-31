CC = gcc
LDFLAGS = -lraylib -lm -ldl -lpthread -lX11

TARGET = latmab
SRC = main.c mcore.c menvi.c mlang.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c latmab.h
	$(CC) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
