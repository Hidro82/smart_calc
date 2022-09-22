CC = gcc
GCOVFLAGS = -lcheck -lgcov -coverage
GCOVFLAGSLIN = --coverage
#ERRFLAGS = -Wall -Werror -Wextra
#ASAN = -fsanitize=address
FLAGC = -c
FLAGO = -o
TEST_C = Tests/tests.c
TEST_O = Tests/obj/tests.o
calc_C = *.c
calc_O = obj/*.o
calc_GCDA = covers/*.gcda

all: clean create

create:
	$(CC) $(ASAN) $(ERRFLAGS) *.c gui/*.c -lm `pkg-config --cflags --libs gtk+-3.0`
	./a.out

clean:
	rm -rf calc_test a.out $(TEST_O) $(calc_O) Tests/*.a covers/* html/* Tests/*.a *.a

calc.a:
	$(CC) $(ASAN) $(ERRFLAGS) $(FLAGC) $(calc_C)
	mv *.o obj
	ar rc calc.a $(calc_O)
	ranlib calc.a

test: calc.a
	$(CC) $(ASAN) $(ERRFLAGS) $(FLAGC) $(TEST_C) $(MAIN_C)
	mv tests.o Tests/obj
	ar rc Tests/tests.a $(TEST_O)
	ranlib Tests/tests.a
	$(CC) $(ASAN) $(ERRFLAGS) $(GCOVFLAGS) $(FLAGO) calc_test calc.a Tests/tests.a $(calc_C) $(MAIN_O) -lcheck
	./calc_test
	mv *.gcda covers
	mv *.gcno covers

gcov_report: test
	gcov $(calc_GCDA)
	gcovr
	gcovr --html-details html/coverage.html
	open html/coverage.html
	mv *.gcov covers

check:
	cp ../materials/linters/.clang-format ../src
	clang-format -n *.c *.h
	cppcheck *.h *.c
	rm .clang-format
