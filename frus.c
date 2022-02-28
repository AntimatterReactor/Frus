#include <stdio.h>

#define EXIT(x) do { if(fp) fclose(fp); return x; } while (0)
#define THROW_VAL_IF(cond, msg, val) if (cond) { fprintf(stderr, msg, val); EXIT(1); }

static char pstack[30000] = {0}, *pit = pstack, skip = 0, c;
static long lstack[600] = {0}, *lit = lstack, br_index;
static FILE *fp = NULL;

int main(const int argc, const char **argv) {
	THROW_VAL_IF(argc != 2, "Invalid number of arguments: %d | Usage: frus <filename>\n", argc-1);

	THROW_VAL_IF((fp = fopen(argv[1], "r")) == NULL, "Err: Unable to open file '%s'\n", argv[1]);

	while ((c = fgetc(fp)) != EOF) {
		if (skip > 0) {
			if(c == ']') skip -= 1;
			else if(c == '[') skip += 1;
		}
		else {
			switch (c) {
			case '>': ++pit; break;
			case '<': --pit; break;

			case '+': ++(*pit); break;
			case '-': --(*pit); break;

			case '[':
				if(*pit) *(++lit) = ftell(fp);
				else skip++, br_index = ftell(fp);
				break;

			case ']':
				if(*pit) fseek(fp, *(lit--) - 1, SEEK_SET);
				else *(lit--) = 0;
				THROW_VAL_IF(lit < lstack, "Err: Unmatched ']' at index: %ld\n", ftell(fp));
				break;

			case '.': putchar(*pit); break;
			case ',': *pit = getchar(); break;
			}
		}
	}
	THROW_VAL_IF(skip || lit > lstack, "Err: Unmatched '[' at index: %ld\n", br_index);

	EXIT(0);
}
