
# compilation rule
# use make file.s

#
# result: dependencies
#         compilation rule

all: bitvec.o Eratosthenes5.o
	gcc bitvec.o Eratosthenes5.o -o runme

bitvec.o: bitvec.h bitvec.c
	gcc -Wall bitvec.c -c

Eratosthenes5.o: Eratosthenes5.c bitvec.h
	gcc -Wall Eratosthenes5.c -c

%.s: %.c
	gcc -S -fverbose-asm -g0 -O3 $< -o $@

clean:
	rm -f *.o *.s
	# $< = %.c
	# $@ = %.s
