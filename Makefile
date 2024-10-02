# Program Executable
EXE			:=	ftop

# Files
SRC			:=	./src/main.c \
				./src/cpu.c \

SOURCES		:=	${SRC}
OBJECTS		:=	${SOURCES:%.c=obj/%.o}

# Variables
CC			:=	cc
WARNFLAGS	:=	-Wall -Wextra
LDFLAGS		:=	-lncurses

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			@${CC} ${WARNFLAGS} ${OBJECTS} -o ${EXE} ${LDFLAGS}

obj/%.o:	%.c
			@mkdir -p obj/$(dir $<)
			@${CC} ${WARNFLAGS} -c $< -o $@

clean:
			@rm -rf obj

fclean:		clean
			@rm -rf ${EXE}

re:			fclean all

.PHONY:		all clean fclean re
