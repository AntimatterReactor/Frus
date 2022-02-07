#include <stdio.h>
#include <stdlib.h>

#define THROW_IF(cond, msg) if (cond) { fputs(msg, stderr); return EXIT_FAILURE; }
#define THROW_VAL_IF(cond, msg, val) if (cond) { fprintf(stderr, msg, val); return EXIT_FAILURE; }

static char pstack[30000] = {0}, *stkit = pstack, *buf = NULL, skip = 0;
static long lstack[600] = {0}, lindex = 0, br_index = 0, i, len;
static FILE *fp = NULL;

void free_all(void) {
	if (buf) free(buf);
	if (fp) fclose(fp);
}

int main(int argc, char **argv) {
	atexit(free_all);

	THROW_IF(argc != 2, "Invalid number of arguments | Usage: frus <filename>\n");

	fp = fopen(argv[1], "r");
	THROW_VAL_IF(fp == NULL, "Err: Unable to open file '%s'\n", argv[1]);

	THROW_IF(fseek(fp, 0L, SEEK_END) != 0, "Err: Unable to seek to end of file\n");

	len = ftell(fp);
	THROW_IF(len == -1L, "Err: Unable to tell the length of the file\n");

	THROW_IF(fseek(fp, 0L, SEEK_SET) != 0, "Err: Unable to seek back to start of file\n");

	buf = (char*) calloc(len, sizeof(char));
	THROW_IF(buf == NULL, "Err: Not enough memory to allocate buffer\n");

	fread(buf, sizeof(char), len, fp);
	THROW_IF(ferror(fp), "Err: Unable read the file\n");

	for (i = 0; i < len; i++) {
		if (skip > 0) {
			if (buf[i] == ']') skip -= 1;
			else if (buf[i] == '[') skip += 1;
			continue;
		}

		switch (buf[i]) {
			case '>': stkit++; break;
			case '<': stkit--; break;

			case '+': ++*stkit; break;
			case '-': --*stkit; break;

			case '[':
				if	(*stkit != 0) lstack[++lindex] = i;
				else if	(*stkit == 0) skip += 1, br_index = i;
				break;

			case ']':
				if (*stkit != 0) i = lstack[lindex--] - 1;
				else lstack[lindex--] = 0;
				THROW_VAL_IF(lindex < 0, "Err: Unmatched ']' at index: %ld\n", i);
				break;

			case '.': putchar(*stkit); break;
			case ',': *stkit = getchar(); break;
		}
	}
	THROW_VAL_IF(skip == 1 || lindex > 0, "Err: Unmatched '[' at index: %ld\n", br_index);

	return EXIT_SUCCESS;
}

#undef THROW_IF
#undef THROW_VAL_IF
