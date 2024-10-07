# Program Executable
EXE			:=	ftop

# Files
VPATH		:=	src

SRC			:=	main.c \
				handle_input.c \
				cpu_info.c \
				cpu_menu.c \

SOURCES		:=	${SRC}
OBJ_DIR		:=	obj
OBJECTS		:=	${SOURCES:%.c=${OBJ_DIR}/%.o}

# Variables
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -fsanitize=address,leak -Iincludes
LDFLAGS		:=	-lncurses

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS}

${OBJ_DIR}/%.o:	%.c | ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
			@mkdir -p $@

clean:
			@rm -rf obj

fclean:		clean
			@rm -rf ${EXE}

re:			fclean all

.PHONY:		all clean fclean re
