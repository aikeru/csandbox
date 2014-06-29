/*
  FIXLINES.C
  A simple C program to convert a file from \r (UNIX) -> \r\n (DOS)

*/
#include <stdio.h>
#include <string.h>

void main() {
	FILE *origFile;
	FILE *outFile;
	char inputStr[255];
	char outputStr[257];
	char *readPtr;
	char inputChar;
	char lastChar;
	int i = 0;
	int read = 0;
	int countReads = 0;
	int mode_crlf = 0;
	int mode_r = 1;
	int mode_n = 2;
	int mode_scan = 3;
	int mode = mode_n;
	int types_found = 0;

	origFile = fopen("c:\\tcfiles\\mode13.c", "r");
	/* origFile = fopen("c:\\tcfiles\\fixlines.c", "r"); */
	outFile = fopen("c:\\tcfiles\\mode13.dos", "w");
	do {
		countReads++;
		read = fgetc(origFile);
		if(read != (int)EOF) {
			lastChar = inputChar;
			inputChar = (char)read;
			printf("\r\nRead %s and %d", &inputChar, &read);
			if(mode == mode_crlf) {
				if(inputChar == '\r') {
					printf("Found a slash R");
				}
				if(inputChar == '\n') {
					printf("Found a slash N");
				}
				if(inputChar == '\n' && lastChar != '\r') {
					fputc((int)'\r', outFile);
				} else if(lastChar == '\r' && inputChar != '\n') {
					fputc((int)'\n', outFile);
				}
			} else if(mode == mode_r) {
				if(inputChar == '\n') {
					inputChar = '\r';
				}
			} else if(mode == mode_n) {
				if(inputChar == '\r') {
					inputChar = '\n';
				}
			} else if(mode == mode_scan) {
				if(inputChar == '\r') {
					if(types_found == 1) {
						types_found = 3;
					} else {
						types_found = 2;
					}
				} else if(inputChar == '\n') {
					if(types_found == 2) {
						types_found = 3;
					} else {
						types_found = 1;
					}

				}

			}

			if(mode != mode_scan) fputc((int)inputChar, outFile);

		}
	} while(read != (int)EOF && countReads < 1000);

	if(mode == mode_scan) {
		if(types_found == 1) printf("Found slash Ns");
		if(types_found == 2) printf("Found slash Rs");
		if(types_found == 3) printf("Found both chars");
	}

	fclose(origFile);
	fclose(outFile);

}