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
	if (fp == NULL)
	{
		fprintf(stderr,
			"Error: Unable to open file\n"
			"| Tip: Check if the file actually exists\n");
		return EXIT_FAILURE;
	}

	if (fseek(fp, 0L, SEEK_END))
	{
		fprintf(stderr,
			"Error: Unable to seek to the end of file\n"
			"| No fix are available\n"
			"| Please open an issue on github\n");
		return EXIT_FAILURE;
	}

	len = ftell(fp);
	if (len == -1L)
	{
		fprintf(stderr,
			"Error: Unable to tell the length of the file\n"
			"| No fix are available\n"
			"| Please open an issue on github\n");
		return EXIT_FAILURE;
	}
	if (fseek(fp, 0L, SEEK_SET))
	{
		fprintf(stderr,
			"Error: Unable to seek back to the start of the file\n"
			"| No fix are available\n"
			"| Please open an issue on github\n");
		return EXIT_FAILURE;
	}

	buffer = (char*) calloc(len, sizeof(char));
	if (buffer == NULL)
	{
		fprintf(stderr,
			"Error: Unable to allocate string buffer of size %ld\n"
			"| Tip: Check if you have enough memory\n"
			"| Please open an issue on github\n",
			len);
		return EXIT_FAILURE;
	}

	fread(buffer, sizeof(char), len, fp);
	if (ferror(fp))
	{
		fprintf(stderr,
			"Error: Unable read the file\n"
			"| Tip: Check if the file is corrupted\n"
			"| Please open an issue on github\n");
		return EXIT_FAILURE;
	}

	if(interpreter(buffer, len)) return EXIT_FAILURE;

	free(buffer);
	return EXIT_SUCCESS;
}
