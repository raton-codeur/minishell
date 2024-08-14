NAME = minishell
CFLAGS = -Wall -Werror -Wextra -I inc -I libft -g3 #-fsanitize=address
LFLAGS = -lreadline
LIBFT = libft/libft.a
OBJS = $(patsubst src/%,tmp/%,$(SRCS:.c=.o))
SRCS = $(addprefix src/, \
	parsing/change_tokens.c \
	parsing/expand_variables.c \
	parsing/expand_variables_utils.c \
	parsing/find_delimiters.c \
	parsing/init_tokens.c \
	parsing/iterate_on_tokens.c \
	parsing/parse.c \
	parsing/parse_quotes.c \
	parsing/parsing_utils.c \
	parsing/tokens_utils.c \
	init.c \
	env_utils_1.c \
	error_1.c \
	error_2.c \
	free.c \
	free_utils.c \
	get_path.c \
	AST/build_ast.c \
	AST/build_ast_utils.c \
	AST/get_from_tree.c \
	execution/get_heredocs.c \
	execution/cd_utils.c \
	execution/echo.c \
	execution/exit.c \
	execution/execute_pipe.c \
	execution/execute.c \
	execution/exit_utils.c \
	execution/prepare_execution.c \
	execution/pwd.c \
	execution/run_builtin.c \
	execution/run_cmd.c \
	execution/set_redirections.c \
	execution/unset.c \
	execution/export_print.c \
	execution/cd.c \
	execution/export.c \
	execution/env.c \
	signals.c \
	init_env.c \
	init_env2.c \
	minishell.c \
	env_utils_2.c \
	set_signals.c \
)

tmp/%.o : src/%.c
	@ mkdir -p $(dir $@)
	@ cc $(CFLAGS) -c $< -o $@ && printf "\rcompilation for $(NAME) : %d / %d" $$(find tmp -type f | wc -l) $(words $(SRCS))

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

re : fclean all

.PHONY : all clean fclean re