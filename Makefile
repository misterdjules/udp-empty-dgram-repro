UV_PATH=./libuv
UV_LIB=$(UV_PATH)/.libs/libuv.a
CFLAGS=-g -Wall -I$(UV_PATH)/include

repro: main.c
	$(CC) $(CFLAGS) -o $@ main.c $(UV_LIB)