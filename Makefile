SRCS		=	srcs/pipex.c srcs/pipex_utils.c

SRCS_BONUS	=	pipex_bonus.c\
				pipex_utils_bonus.c\
				heredoc_bonus.c \
				get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c

OBJ_DIR	=	obj
SRCS_DIR	=	srcs_bonus

OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${addprefix ${OBJ_DIR}/,${SRCS_BONUS:.c=.o}}
DPD			=	${addprefix ${OBJ_DIR}/,${SRCS_BONUS:.c=.d}}

NAME		=	pipex

LIB			=	./libft/libft.a

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -MMD

RM			=	rm -f

${NAME}:		${OBJS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

all:			${NAME}

bonus:			${OBJS_BONUS}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${LIB} -o ${NAME} ${OBJS_BONUS}

#si le .c est plus recent que son .o, on entre dans la règle
${OBJ_DIR}/%.o:	${SRCS_DIR}/%.c
				@mkdir -p ${OBJ_DIR}
				${CC} ${CFLAGS} -c $< -o $@

clean:
				${RM} ${OBJS} ${OBJS_BONUS}
				${MAKE} clean -C ./libft

fclean:			clean
				${RM} ${NAME}
				${MAKE} fclean -C ./libft

re:				fclean all

.PHONY:			all bonus clean fclean re

-include ${DPD}
