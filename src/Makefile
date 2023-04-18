CC 						= g++ -std=c++17
OS 						= $(shell uname)

# flags #
CFLAG 					= -Wall -Wextra -Werror
GCOV 					= --coverage
LIBS 					= $(shell pkg-config --libs --cflags gtest) -lpthread -lgtest_main
# libraries #
ifeq ($(OS), Linux)
	OPEN 				= xdg-open
else
	OPEN 				= open
endif
S_NAME 					= matrix_oop
# path and files #
LIB_NAME 				= $(S_NAME).a

T_NAME					= tests
T_SOURCE 				= $(T_NAME).cc
T_HEADER 				= $(T_NAME).h
T_OBJECT 				= $(T_SOURCE:%.cc=%.o)

SOURCES 				= $(S_NAME).cc
HEADERS 				= $(S_NAME).h
.PHONY: object test matrix_oop.a clean rebuild code_style memcheck
# targets #
all: test

object:
	@$(CC) -c $(CFLAG) $(SOURCES) -o $(S_NAME).o

$(LIB_NAME): object
	@ar -rcs $(LIB_NAME) $(S_NAME).o
	@ranlib $@
	@rm -rf *.o
	@echo "Successfully. The library was created."

# targets for tests #
test: $(LIB_NAME)
	@echo " "
	@$(CC) $(T_SOURCE) -o $(T_NAME) $(LIBS) $(LIB_NAME)
	@./$(T_NAME)

# assembly #
clean:
	@rm -rf *.o *.a *.gcno *.gcda *.info *.out coverage report $(T_NAME) valgrind-out.txt
	@echo "Successfully. Everything was deleted."

rebuild: clean all

# for debug #
check: code_style cppcheck

code_style:
	@echo "------------  Code style  ---------------"
	@clang-format -n *.cc *.h
	@echo "Successfully. Code style was checked."

cppcheck:
	@echo "------------  CPPCheck  -------------"
	@cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ *.cc *.h
	@echo "Successfully. CPPCheck was checked."

memcheck: test
ifeq ($(OS), Linux)
	@echo "------------  Valgrind  -------------"
	@CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  --log-file=valgrind-out.txt --verbose ./$(T_NAME)
else
	@echo "-------------  Leaks  ---------------"
	@CK_FORK=no leaks --atExit -- ./$(T_NAME)
endif
