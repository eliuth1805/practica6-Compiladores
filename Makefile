CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = parser
TEST_TARGET = test_parser

SRC = src/main.c \
      src/parser.c \
      src/tablas.c \
      src/ast.c

OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test_parser.c \
           src/parser.c \
           src/tablas.c \
           src/ast.c

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean
