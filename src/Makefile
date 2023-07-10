CC = gcc
GCOVFLAGS = -lcheck -lgcov -coverage
GCOVFLAGSLIN = --coverage
GTKFLAG = -lm `pkg-config --cflags --libs gtk+-3.0`
ERRFLAGS = -Wall -Werror -Wextra
#ASAN = -fsanitize=address
FLAGC = -c
FLAGO = -o
TEST_C = Tests/tests.c
TEST_O = Tests/obj/tests.o
TEST_A = Tests/tests.a
calc_C = brains/*.c
calc_H = brains/*.h
calc_O = brains/obj/*.o
calc_A = brains/calc.a
calc_GCDA = covers/*.gcda
gui_C = gui/*.c
gui_H = gui/*.h
gui_O = gui/obj/*.o
gui_A = gui/gui.a

all: install

install: uninstall calc.a gui.a
	mkdir ready_to_go
	$(CC) $(ASAN) $(FLAGO) ready_to_go/smart_calc $(calc_A) $(gui_A) $(GTKFLAG)

uninstall: clean
	rm -rf ready_to_go

dist:
	tar -czvf smart_calc.tar.gz ready_to_go

dvi:
	open ref_doc.pdf	

run:
	./ready_to_go/smart_calc

clean:
	rm -rf calc_test a.out
	rm -rf Tests/obj brains/obj gui/obj
	rm -rf $(TEST_A) $(calc_A) $(gui_A)
	rm -rf covers html
	rm -rf smart_calc.tar.gz

calc.a:
	$(CC) $(ASAN) $(ERRFLAGS) $(FLAGC) $(calc_C)
	mkdir brains/obj
	mv *.o brains/obj
	ar rc $(calc_A) $(calc_O)
	ranlib $(calc_A)

gui.a:
	$(CC) $(ASAN) $(FLAGC) $(gui_C) $(GTKFLAG)
	mkdir gui/obj
	mv *.o gui/obj
	ar rc $(gui_A) $(gui_O)
	ranlib $(gui_A)

tests.a:
	$(CC) $(ASAN) $(ERRFLAGS) $(FLAGC) $(TEST_C)
	mkdir Tests/obj
	mv tests.o Tests/obj
	ar rc $(TEST_A) $(TEST_O)
	ranlib $(TEST_A)

tests: clean calc.a tests.a
	$(CC) $(ASAN) $(ERRFLAGS) $(GCOVFLAGS) $(FLAGO) calc_test $(calc_A) $(TEST_A) $(calc_C) -lcheck
	./calc_test
	mkdir covers
	mv *.gcda covers
	mv *.gcno covers

gcov_report: tests
	mkdir html
	gcov $(calc_GCDA)
	gcovr
	gcovr --html-details html/coverage.html
	open html/coverage.html
	mv *.gcov covers

check:
	cp ../materials/linters/.clang-format ../src
	clang-format -n $(calc_C) $(calc_H) $(gui_C) $(gui_H) $(TEST_C)
	cppcheck $(calc_C) $(calc_H) $(gui_C) $(gui_H) $(TEST_C)
	rm .clang-format
	$(CC) $(ERRFLAGS) $(calc_C) $(TEST_C) -lcheck -lm
	valgrind --leak-check=full ./a.out
	CK_FORK=no leaks --atExit -- ./a.out
