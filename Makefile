
CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g
OUTFILE = tar10
SRC = src
INCLUDE = include

all: $(OUTFILE)
$(OUTFILE): $(SRC) 
	$(CC) $(CFLAGS) -I $(INCLUDE) $(SRC) -o $(OUTFILE) 

.PHONY: clean mrproper
clean:
	$(RM) $(OUTFILE)
	$(RM) *~
