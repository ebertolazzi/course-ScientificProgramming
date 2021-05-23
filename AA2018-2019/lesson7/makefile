
# compilation rule
# use make file.s

#
# result: dependencies
#         compilation rule

OPT  = -O3 -g0
CC   = gcc-8
CXX  = g++-8
FOR  = gfortran
WARN = -Wall
INC  = -I/usr/local/include/eigen3

2: 2_link_with_fortran.o 2_link_with_fortran_b.o
	$(CXX) 2_link_with_fortran.o 2_link_with_fortran_b.o -o run2 -L/usr/local/lib/gcc/8 -lgfortran

3: 3_ordina_c.o
	$(CXX) 3_ordina_c.o -o run3

4: 4_ordina_c.o
	$(CXX) 4_ordina_c.o -o run4

5: 5_bubble_sort_template.o
	$(CXX) 5_bubble_sort_template.o -o run5

6: 6_test_vector.o
	$(CXX) 6_test_vector.o -o run6

7: 7_test_vector2.o TimeMeter.o
	$(CXX) 7_test_vector2.o TimeMeter.o -o run7

8: 8_string.o
	$(CXX) 8_string.o -o run8

9: 9_exception.o
	$(CXX) 9_exception.o -o run9

10: 10_classes.o
	$(CXX) 10_classes.o -o run10

11: 11_Eigen.o
	$(CXX) 11_Eigen.o -o run11

12: 12_Eigen.o
	$(CXX) 12_Eigen.o -o run12

13: 13_Eigen.o
	$(CXX) 13_Eigen.o -o run13

14: 14_Eigen.o
	$(CXX) 14_Eigen.o -o run14

# generic rule for compile C-code
%.o: %.c
	$(CC) $(OPT) $(OPT) $(WARN) -c $<

# generic rule for compile C++-code
%.o: %.cc
	$(CXX) $(INC) $(OPT) $(WARN) -c $<

%.o: %.cpp
	$(CXX) $(INC) $(OPT) $(WARN) -c $<

# generic rule for compile FORTRAN-code
%.o: %.f
	$(FOR) $(OPT) $(WARN) -c $<

%.o: %.f90
	$(FOR) $(OPT) $(WARN) -c $<

clean:
	rm -f *.o *.s
	# $< = %.c
	# $@ = %.s
