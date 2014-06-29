/*
  FIXLINES.C
  A simple C program to convert between line endings for UNIX, MAC and DOS
  Copyright (C) 2014 aikeru
*/
#include <stdio.h>
#include <string.h>

void scanfile(char *scanFile);

void main(int argc, char *argv[]) {
	FILE *origFile;
	FILE *outFile;
	char inputStr[255];
	char outputStr[257];
	char outDest[255];
	char *readPtr;
	char inputChar;
	char lastChar;
	int i = 0;
	int read = 0;
	int mode_crlf = 0;
	int mode_r = 1;
	int mode_n = 2;
	int mode_scan = 3;
	int mode = mode_n;
	int types_found = 0;

	if(argc < 2) {
		printf("Usage: %s filename mode outfile", argv[0]);
		return;
	}
	if(argc  < 3) {
		mode = mode_scan;
	} else {
		if(argv[2][0] == 'r') mode = mode_r;
		if(argv[2][0] == 'n') mode = mode_n;
		if(argv[2][0] == 'c') mode = mode_crlf;
		if(argv[2][0] == 's') mode = mode_scan;
	}

	if(mode == mode_scan) {
		scanfile(argv[1]);
		return;
	}

	if(argc < 4) {
		strcpy(outDest, "output.c");
	} else {
		strcpy(outDest, argv[3]);
	}

	origFile = fopen(argv[1], "r");
	outFile = fopen(outDest, "w");
	do {
		read = fgetc(origFile);
		if(read != (int)EOF) {
			lastChar = inputChar;
			inputChar = (char)read;
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
			}
			fputc((int)inputChar, outFile);

		}
	} while(read != (int)EOF);

	fclose(origFile);
	fclose(outFile);

}

void scanfile(char *scanFile) {

	FILE *origFile = fopen(scanFile, "r");
	char inputChar;
	int types_found = 0;
	int read = 0;
	do {
		read = fgetc(origFile);
		if(read != (int)EOF) {
			inputChar = (char)read;
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
	} while(read != (int)EOF);

	if(types_found == 1) printf("Found \\n's");
	if(types_found == 2) printf("Found \\r's");
	if(types_found == 3) printf("Found \\n's and \\r's");
	if(types_found == 0) printf("Didn't find anything.");
	fclose(origFile);

	return;
}