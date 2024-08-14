NAME = libft.a
FLAGS = -Wall -Wextra -Werror -I. -g3 #-fsanitize=address
OBJS = $(addprefix tmp/, $(notdir $(SRCS:.c=.o)))
SRCS = $(addprefix src/, \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_length_unsigned_hex.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_print_char_and_string.c \
	ft_printf.c \
	ft_print_hex_and_pointer.c \
	ft_print_int_and_unsigned.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c \
	list_add_back.c \
	list_add_front.c \
	list_clear.c \
	list_last.c \
	list_new.c \
	list_print.c \
	list_size.c \
	ft_split_quote.c \
	ft_split_quote_utils.c \
	array_size.c \
	ft_atof.c \
	ft_strisspace.c \
	ft_isspace.c \
	list_remove_node.c \
	ft_strjoin_list.c \
	deep_free.c \
	save_add.c \
	isword.c \
	list_node_index.c \
	ft_strisdigit.c \
	skip_zeros.c \
)

$(NAME) : $(OBJS)
	@ ar rc $@ $^ && printf "\n$@ created\n"

tmp/%.o : src/%.c
	@ mkdir -p tmp
	@ cc $(FLAGS) -c $< -o $@ && printf "\rcompilation for $(NAME) : %d / %d" $$(ls tmp | wc -w) $(words $(SRCS))

all : $(NAME)

clean :
	@ rm -rf tmp && printf "$(NAME) cleaned\n"

fclean : clean
	@ rm -f $(NAME) && printf "$(NAME) deleted\n"

re : fclean all

.PHONY : all clean fclean re