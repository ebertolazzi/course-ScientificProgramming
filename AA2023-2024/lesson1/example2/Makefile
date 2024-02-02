# rule to produce example2_1.o
# production: dependencies
# [tab] commands to generate `production`

all: example2_1

# from source file --> binary file
example2_1.o: example2_1.cc
	g++ example2_1.cc -c

# from binary file --> executable
example2_1: example2_1.o
	g++ example2_1.o -o example2_1

clean:
	rm example2_1.o example2_1