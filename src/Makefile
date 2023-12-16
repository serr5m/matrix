SFILENAME = my_matrix_oop.cc
OFILENAME = my_matrix_oop.o
LIBNAME = my_matrix_oop.a

TESTNAME = test_matrix
TFILENAME = test_matrix.cc

ifeq ($(shell uname), Linux)
	OPEN= xdg-open 
	LIBS= -lgtest -lpthread -pthread -lrt -lsubunit 
	LEAKS= CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TESTNAME)
	CC = g++ -std=c++17 -lstdc++
else
	CC = g++ -std=c++17 -lstdc++
	OPEN= open
	LIBS= -lcheck -pthread -lgtest 
	LEAKS= leaks --atExit -- ./$(TESTNAME) 
endif

all: clean $(LIBNAME) test linter
$(OFILENAME): $(SFILENAME)
	g++ -Wall -Werror -Wextra -o $(OFILENAME) $(SFILENAME) -c
$(LIBNAME): $(OFILENAME)	
	ar rc $(LIBNAME) $(OFILENAME)	
test:
	$(CC) $(TFILENAME) $(LIBNAME) -o $(TESTNAME) $(LIBS)
	./$(TESTNAME)

leaks:
	$(LEAKS)
linter:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cc
	clang-format -n *.h
	rm .clang-format
clean:
	rm -f $(TESTNAME)
	rm -f *.out
	rm -f *.o
	rm -f *.a
