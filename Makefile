NAME		=	pipex

SRCS		=	pipex.c\
				pipex_utils.c\

#SRCS_BONUS	=	pipex_bonus.c\
				pipex_utils_bonus.c\
				heredoc_bonus.c \
				get_next_line.c\
				get_next_line_utils.c

OBJ_DIR		=	obj
#SRCS_DIR	=	srcs_bonus
INC			=	./includes
SRCS_DIR	=	./srcs
OBJ			=	${addprefix ${OBJ_DIR}/,${SRCS:.c=.o}}

#OBJS_BONUS	=	${addprefix ${OBJ_DIR}/,${SRCS_BONUS:.c=.o}}
#DPD			=	${addprefix ${OBJ_DIR}/,${SRCS_BONUS:.c=.d}}


FT			=	./libft/
FT_LIB		=	$(addprefix $(FT),libft.a)
FT_INC		=	-I ./libft

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

RM			=	rm -rf


all:			obj ${FT_LIB} ${NAME}

${FT_LIB}:
				${MAKE} -C ${FT}

obj:
				mkdir -p ${OBJ_DIR}

${NAME}:		${OBJ}
				${CC} ${CFLAGS} ${OBJ} ${FT_LIB} -o ${NAME}


#bonus:			${OBJS_BONUS}
#				${MAKE} -C ./libft
#				${CC} ${CFLAGS} -I ${INC} ${LIB} -o ${NAME} ${OBJS_BONUS}

#si le .c est plus recent que son .o, on entre dans la règle
${OBJ_DIR}/%.o:	${SRCS_DIR}/%.c includes/pipex.h
				${CC} ${CFLAGS} ${FT_INC} -I ${INC} -o $@ -c $<

clean:
				${RM} ${OBJ_DIR}
				${MAKE} -C ${FT} clean

fclean:			clean
				${RM} ${NAME}
				make -C $(FT) fclean

re:				fclean all