#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	*path;

	path = getenv("PATH");
	if (path != NULL)
		printf("path : %s\n", path);
	return (0);
}
