SHELL=/bin/sh
CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread

NAME=philo

all: ${NAME}

SRCS=\
announce.c \
data.c \
error.c \
main.c \
monitor.c \
parse.c \
routines.c \
sleep.c \
start.c \
time.c

BINARY_FOLDER=bin
OBJS=${addprefix ${BINARY_FOLDER}/,${SRCS:.c=.o}}

${OBJS}: ${BINARY_FOLDER}/%.o: %.c philo.h
	mkdir -p $(@D)
	${CC} ${CFLAGS} $< -o $@ -c

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@

.PHONY: all clean fclean re

clean:
	rm -rf ${BINARY_FOLDER}

fclean: clean
	rm -f ${NAME}

re: fclean all
