
CC= gcc
CFLAGS= -std=c99 -Wall -Werror -g
OUTFILE= tar10
SRC=$(wildcard *.c)

all: $(OUTFILE)
$(OUTFILE): $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -o $(OUTFILE) 

.PHONY: clean mrproper
clean:
	rm -f $(OUTFILE)

mrproper: clean
	rm -f *~
	rm -f *.tar		
