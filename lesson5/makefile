
# compilation rule
# use make file.s

#
# result: dependencies
#         compilation rule

all: test.o polynom.o
	gcc test.o polynom.o -o runme

%.o: %.c
	gcc -Wall -c $<

clean:
	rm -f *.o *.s
	# $< = %.c
	# $@ = %.s
