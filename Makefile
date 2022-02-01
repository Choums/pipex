SRCS		=	srcs/pipex.c srcs/pipex_utils.c

SRCS_BONUS	=	srcs_bonus/pipex_bonus.c srcs_bonus/pipex_utils_bonus.c srcs_bonus/link_management_bonus.c \
				srcs_bonus/get_next_line/get_next_line.c srcs_bonus/get_next_line/get_next_line_utils.c

OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME		=	pipex

LIB			=	./libft/libft.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

.c.o:			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

all:			${NAME}

bonus:			${OBJS_BONUS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS_BONUS} ${LIB} -o ${NAME}
clean:
				${RM} ${OBJS} ${OBJS_BONUS}
				${MAKE} clean -C ./libft

fclean:			clean
				${RM} ${NAME}
				${MAKE} fclean -C ./libft

re:				fclean all

.PHONY:			all bonus clean fclean re