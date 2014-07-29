PLATFORM    = $(shell uname)
UV_PATH     = ./libuv
UV_LIB      = $(UV_PATH)/.libs/libuv.a
CFLAGS      = -g -Wall -I$(UV_PATH)/include

ifeq ($(PLATFORM),Linux)
	LDFLAGS=-lpthread -lrt
endif

repro: main.c
	$(CC) $(CFLAGS) -o $@ main.c $(UV_LIB) $(LDFLAGS)

clean:
	$(RM) repro