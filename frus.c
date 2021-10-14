#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int errset = 0;
void err(const char *msg)
{
	fputs(msg, stderr);
	errset = 1;
}

void interpreter(char *rawIn, long inLen)
{
	uint8_t  lstack[UINT8_MAX]	= {0};
	char	 pstack[30000]		= {0};
	char	 *stkit			= pstack;
	int8_t	 skip			= 0;
	uint8_t	 lindex			= 0;
	uint8_t	 br_index		= 0;

	for (size_t i = 0; i < inLen; i++)
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
				else if	(*stkit == 0) skip += 1;
				break;

			case ']':
				if (*stkit != 0) i = lstack[lindex--] - 1;
				else lstack[lindex--] = 0;
				break;

			case '.': putchar(*stkit); break;
			case ',': *stkit = getchar(); break;
		}
	}
	if (skip == 1 || lindex > 0) err("\n\nError: Unmatched '['");
}

int main(int argc, char **argv)
{
	char *buffer;
	FILE *fp;
	long len;

	if (argc < 2) err("Not enough args, need file name");
	else if (argc > 2) err("Too much args");

	if (errset) return 1;

	fp = fopen(argv[1], "r");

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buffer = (char*) calloc(len, sizeof(char));

	fread(buffer, 1, len, fp);

	interpreter(buffer, len);

	if (errset) return 1;

	free(buffer);

	return 0;
}
