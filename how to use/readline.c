
void	rl_exemple(void)
{
	char	*input;

	int i = 0;

	input = readline("input something > ");
	if (!input || input[i] == '\0')
	{
		free(input);
		return ;
	}
	printf("your input : %s\n", input);
	free(input);
}
