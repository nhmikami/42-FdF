NAME			=	fdf
RM				=	rm -f
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

SRC_PATH		=	./src
INC_PATH		=	./inc
LIB_PATH		=	./lib

SRC				=	fdf.c
OBJ				=	$(addprefix $(SRC_PATH)/, $(SRC:.c=.o))

INC				=	-I$(INC_PATH)

LIBFT			=	$(LIB_PATH)/libft.a

all:				$(NAME)

$(LIBFT):
					make -C $(LIB_PATH) -s

$(NAME):			$(LIBFT) $(OBJ)
						$(CC) $(CFLAGS) $(OBJ) -L$(LIB_PATH) -lft -o $(NAME)

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH)/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
					$(RM) $(OBJ)
					make clean -C $(LIB_PATH) -s

fclean:				clean
					$(RM) $(NAME)
					make fclean -C $(LIB_PATH) -s

re:					fclean all

.PHONY:		all clean fclean re