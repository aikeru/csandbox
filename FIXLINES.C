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
	int i = 0;
	int read = 0;
	int countReads = 0;

	origFile = fopen("c:\\tcfiles\\mode13.c", "r");
	outFile = fopen("c:\\tcfiles\\mode13.dos", "w");
	do {
		countReads++;
		read = fgetc(origFile);
		if(read != (int)EOF) {
			inputChar = (char)read;
			printf("\r\nRead %s and %d", &inputChar, &read);
			if(inputChar == '\n') {
				fputc((int)'\r', outFile);
			}
			fputc((int)inputChar, outFile);
		}
	} while(read != (int)EOF && countReads < 1000);

	fclose(origFile);
	fclose(outFile);

}