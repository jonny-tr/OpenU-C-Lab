# Compiler
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -std=c89 -lm
SRCS = ${shell ls *.c}
OBJS = $(SRCS:.c=.o)
LIB = ${shell ls *.h} 
# Executable
TARGET = my_add

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c $(LIB)
	$(CC) $(CFLAGS) $ -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Remove up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)