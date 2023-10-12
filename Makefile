NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror 
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft
LIBFT_A	:= lib/libft/libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJDIR	:= .objFiles
OBJS	:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

#Colors:
GREEN		= \e[92;5;118m
YELLOW		= \e[93;5;226m
GRAY		= \e[33;2;37m
RESET		= \e[0m
CURSIVE		= \e[33;3m

#Debug 
ifeq ($(DEBUG), 1)
   OPTS = -g
endif

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \

$(LIBFT_A):
	@cd lib/libft && make

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -g
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"

clean:
	@rm -rf $(OBJDIR) $(OBJS)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

clean_mlx:
	@rm -rf $(LIBMLX)/build

fclean_libft:
	@cd lib/libft && make fclean

fclean: fclean_libft clean
	@rm -rf $(NAME)
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all
