#include <stdio.h>
#include <stdlib.h>

int interpreter(char *rawIn, long inLen)
{
	long	lstack[600]	= {0};
	char	pstack[30000]	= {0};
	char	*stkit		= pstack;
	char	skip		= 0;
	long	lindex		= 0;
	long	br_index	= 0;
	long	i;

	for (i = 0; i < inLen; i++)
	{
		if (skip > 0)
		{
			if (rawIn[i] == ']') skip -= 1;
			if (rawIn[i] == '[') skip += 1;
			continue;
		}

		switch (rawIn[i])
		{
			case '>': stkit++; break;
			case '<': stkit--; break;

			case '+': ++*stkit; break;
			case '-': --*stkit; break;

			case '[':
				if	(*stkit != 0) lstack[++lindex] = i;
				else if	(*stkit == 0)
				{
					skip += 1;
					br_index = i;
				}
				break;

			case ']':
				if (*stkit != 0) i = lstack[lindex--] - 1;
				else lstack[lindex--] = 0;
				if (lindex < 0)
				{
					fprintf(stderr, "Error: Unmatched ']' at index: %ld\n", i);
					return 1;
				}
				break;

			case '.': putchar(*stkit); break;
			case ',': *stkit = getchar(); break;
		}
	}
	if (skip == 1 || lindex > 0)
	{
		fprintf(stderr, "Error: Unmatched '[' at index: %ld\n", br_index);
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	char *buffer;
	FILE *fp;
	long len;

	if (argc < 2)
	{
		fprintf(stderr,
		"Error: Not enough arguments\n| Usage: <filename>\n");
		return EXIT_FAILURE;
	}
	else if (argc > 2)
	{
		fprintf(stderr,
		"Error: Too much arguments\n| Usage: <filename>\n");
		return EXIT_FAILURE;
	}

	fp = fopen(argv[1], "r");

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buffer = (char*) calloc(len, sizeof(char));

	fread(buffer, 1, len, fp);

	if(interpreter(buffer, len))
	{
		return EXIT_FAILURE;
	}

	free(buffer);
	return EXIT_SUCCESS;
}
