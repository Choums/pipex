SRCS		=	srcs/pipex.c srcs/pipex_utils.c

SRCS_BONUS	=	srcs_bonus/pipex_bonus.c srcs_bonus/pipex_utils_bonus.c srcs_bonus/heredoc_bonus.c \
				srcs_bonus/get_next_line/get_next_line.c srcs_bonus/get_next_line/get_next_line_utils.c

OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME		=	pipex

BONUS		=	${NAME}

LIB			=	./libft/libft.a

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

${NAME}:		${OBJS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

all:			${NAME}

bonus:			${BONUS}

${BONUS}:		${OBJS_BONUS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS_BONUS} ${LIB} -o ${BONUS}

clean:
				${RM} ${OBJS} ${OBJS_BONUS}
				${MAKE} clean -C ./libft

fclean:			clean
				${RM} ${NAME}
				${MAKE} fclean -C ./libft

re:				fclean all

.PHONY:			all bonus clean fclean re
