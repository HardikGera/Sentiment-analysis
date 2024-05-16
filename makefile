CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
SRCS=sentiment_analysis.c
EXEC=mySA


$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

clean:
	rm -f $(EXEC)

