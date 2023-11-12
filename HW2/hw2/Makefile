CC = gcc
CFLAGS = -Wall -g

all: guest_main host_main hw2-sheep hw2-test

guest_main: guest_main.c
	$(CC) $(CFLAGS) -o guest_main guest_main.c

host_main: host_main.c
	$(CC) $(CFLAGS) -o host_main host_main.c

hw2-sheep: guest_hw2_sheep.c
	$(CC) $(CFLAGS) -o guest_hw2_sheep guest_hw2_sheep.c

hw2-test: host_hw2_test.c
	$(CC) $(CFLAGS) -o host_hw2_test host_hw2_test.c

clean:
	rm -f guest_main host_main guest_hw2_sheep host_hw2_test
