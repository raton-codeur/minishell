NAME = minishell
CFLAGS = -Wall -Werror -Wextra -I inc -I libft -g3
LFLAGS = -lreadline
LIBFT = libft/libft.a
SRCS = $(shell find src -type f)
OBJS = $(patsubst src/%,tmp/%,$(SRCS:.c=.o))

tmp/%.o : src/%.c
	@ mkdir -p $(dir $@)
	@ cc $(CFLAGS) -c $< -o $@ && printf "\rcompilation for $(NAME) : %d / %d" $$(ls tmp | wc -w) $(words $(SRCS))

$(NAME) : $(LIBFT) $(OBJS)
	@ cc $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $@ && printf "\n$@ created\n"

$(LIBFT) :
	@ make --no-print-directory -C libft

all : $(NAME)

clean :
	@ make clean --no-print-directory -C libft
	@ rm -rf tmp && printf "$(NAME) cleaned\n"

fclean : clean
	@ make fclean --no-print-directory -C libft > /dev/null && printf "libft.a deleted\n"
	@ rm -f $(NAME) && printf "$(NAME) deleted\n"

# re : fclean all
re : clean all

.PHONY : all clean fclean re

test :
	make re
	./minishell