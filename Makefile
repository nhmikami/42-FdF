NAME			=	fdf
RM				=	rm -f
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

SRC_PATH		=	./src
INC_PATH		=	./inc
LIB_PATH		=	./lib
MLX_PATH		=	./minilibx-linux

SRC				=	fdf.c \
					draw_map.c \
					fill_matrix.c \
					handle_events.c \
					handle_keys.c \
					handle_mouse.c \
					init_mlx.c \
					projections.c \
					read_map.c \
					rotate.c \
					utils.c
					
OBJ				=	$(addprefix $(SRC_PATH)/, $(SRC:.c=.o))

INC				=	-I$(INC_PATH)
LIBFT			=	$(LIB_PATH)/libft.a
LIBMLX			=	$(MLX_PATH)/libmlx.a -lXext -lX11 -lm -lz

all:				$(NAME)

$(NAME):			$(OBJ) $(LIBFT)
						$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) -o $(NAME)


$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH)/fdf.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
					make -C $(LIB_PATH) -s

clean:
					$(RM) $(OBJ)
					make clean -C $(LIB_PATH) -s

fclean:				clean
					$(RM) $(NAME)
					make fclean -C $(LIB_PATH) -s

re:					fclean all

bonus:				all

.PHONY:		all bonus clean fclean re