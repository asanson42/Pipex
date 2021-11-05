SRCS		= $(wildcard ./srcs/*.c)

OBJS		= ${SRCS:.c=.o}

NAME		= pipex

INC		= ./inc/

CC		= gcc -Wall -Wextra -Werror
RM		= rm -f

all:	 ${NAME}

.c.o:
	 ${CC} -I${INC} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	 ${CC} ${OBJS} -I${INC} -o${NAME}

clean:
	 ${RM} ${OBJS}

fclean:	 clean
	 ${RM} ${NAME}

re:	 fclean all

.PHONY:		all clean fclean re
