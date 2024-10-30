##
## EPITECH PROJECT, 2021
## B-CCP-400-PAR-4-1-theplazza-francois.zhao [WSL]
## File description:
## Makefile
##

SRC		= 	src/thread/Mutex.cpp		\
			src/thread/ScopedLock.cpp	\
			src/thread/Process.cpp		\
			src/thread/Thread.cpp		\
			src/thread/ThreadPool.cpp	\
			src/thread/NamedPipe.cpp	\
			src/shell/Shell.cpp			\
			src/plazza/Cook.cpp			\
			src/plazza/Reception.cpp	\
			src/plazza/Pizza.cpp		\
			src/plazza/Kitchen.cpp

MAIN = src/main.cpp

CXX = g++

CXXFLAGS = -W -Wextra -Werror -I./include

LDFLAGS = -lpthread

NAME = plazza

OBJ = $(SRC:.cpp=.o)

.PHONY: all clean fclean re
all: $(OBJ) compile

%.o:	%.c
	echo -e "\e[0;94mCompiled\t\e[0;95m$<\e[39m -> \e[38;5;208m$@\e[39m"
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(LDFLAGS)

compile: $(OBJ)
	$(CXX) -o $(NAME) $(MAIN) $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

debug: CXXFLAGS += -ggdb
debug: all

test: MAIN = bootstrap.cpp
test: debug