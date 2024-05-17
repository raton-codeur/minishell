NAME = minishell
FLAGS = -Wall -Werror -Wextra -I . -I libft
LIBFT = libft/libft.a
OBJS = $(addprefix tmp/, $(notdir $(SRCS:.c=.o)))
OBJS_BONUS = $(addprefix tmp/, $(notdir $(SRCS_BONUS:.c=.o)))
SRCS = $(addprefix src/, $(shell ls src))

tmp/%.o : src/%.c
	@ mkdir -p tmp
	@ cc $(FLAGS) -c $< -o $@ && printf "\rcompilation for $(NAME) : %d / %d" $$(ls tmp | wc -w) $(words $(SRCS))

$(NAME) : $(LIBFT) $(OBJS)
	@ cc $(FLAGS) $(OBJS) $(LIBFT) -o $@ && printf "\n$@ created\n"

$(LIBFT) :
	@ make --no-print-directory -C libft

all : $(NAME)

clean :
	@ make clean --no-print-directory -C libft
	@ rm -rf tmp && printf "$(NAME) cleaned\n"

fclean : clean
	@ make fclean --no-print-directory -C libft > /dev/null && printf "libft.a deleted\n"
	@ rm -f $(NAME) && printf "$(NAME) deleted\n"

re : fclean all

.PHONY : all clean fclean re