##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my first make file
##

CC = gcc

MAIN	=

SRC     =	src/main.c	\
		src/drop_menu.c	\
		src/init.c	\
		src/color.c	\
		src/edit.c	\
		src/display.c	\
		src/event.c	\
		src/draw.c	\
		src/toolbar.c	\
		src/help.c	\
		src/topbar.c	\
		src/color_picker.c	\
		src/shape.c	\
		src/clean.c	\

CRFLAGS	=	--coverage -lcriterion

CSFML	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

OBJ	=	$(SRC:.c=.o)

NAME	=	my_paint

LDFLAGS =	-L./lib/my

LDLIBS	=	-lmy $(CSFML) -lm

CPPFLAGS	=	-I./include/

CFLAGS	=	-Wall -Wextra

LIBNAME	=	libmy.a

TEST_SRC	=	tests/unit_tests.c

TNAME	=	unit_tests

all:	lib $(NAME)

lib:
	$(MAKE) -C lib/my

$(NAME):	$(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(MAIN) $(OBJ) $(LDLIBS)

tests_run: lib
	$(CC) $(LDFLAGS) -o $(TNAME) $(TEST_SRC) $(OBJ) $(CRFLAGS) $(LDLIBS)
	./$(TNAME)

clean:
	$(MAKE) clean -C lib/my
	rm -f $(OBJ) *~  *.gcda *.gcno src/*.gc*

fclean:	clean
	rm -f $(NAME) $(TNAME) lib/my/$(LIBNAME)

debug:	CPPFLAGS += -g3
debug:	re

re:     fclean all

.PHONY: all lib tests_run clean fclean re debug
