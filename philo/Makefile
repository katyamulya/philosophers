NAME = philo

SRC_1 = philo.c
SRC_2 = utils/check_err.c utils/ft_strcmp.c utils/ft_usleep.c
SRC_3 = threads/functions_threads.c threads/init.c threads/routine.c \
		threads/status_died.c threads/status_eaten.c threads/threads_philo.c

OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}
OBJ_3 = ${SRC_3:.c=.o}

CC = cc

CFlAGS = -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	${CC} -c $< -o ${<:.c=.o}


${NAME}:	${OBJ_1} ${OBJ_2} ${OBJ_3}
	${CC} ${CFlAGS} ${OBJ_1} ${OBJ_2} ${OBJ_3} -o ${NAME}

clean:
	rm -f ${OBJ_1} ${OBJ_2} ${OBJ_3}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re