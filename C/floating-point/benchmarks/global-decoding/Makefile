CC=gcc
CFLAGS=-Wall

all: airborne check

airborne:
	$(CC) -o decode decode.c -L../.. -lairborne $(FLAGS)

check:
	$(CC) -o check-decoding check-decoding.c $(FLAGS)

clean:
	$(RM) decode check-decoding