
CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g
OUTFILE = tar10
SRC = $(wildcard *.c)

all: $(OUTFILE)
$(OUTFILE): $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -o $(OUTFILE) 

.PHONY: clean mrproper
clean:
	$(RM) $(OUTFILE)
	$(RM) *~
