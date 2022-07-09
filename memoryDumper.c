



#define _GNU_SOURCE

#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <math.h>





void dumpMemory(char *mPath, long int csa, long int cssa) {

	FILE *dumpMemory = fopen(mPath, "rb");

	fseek(dumpMemory, csa, SEEK_CUR);

	int length = cssa - csa;

	if(length <= 0) {

		char buffer[2];

		for(int i = 0; i < 50000; i++) {

			fread(buffer, 1, 1, dumpMemory);

			printf("%s\n", buffer);

			bzero(buffer, 2);

		}


	}

	else {

		char buffer[2];

		for(int i = 0; i < length; i++) {

			fread(buffer, 1, 1, dumpMemory);

			printf("%s\n", buffer);

			bzero(buffer, 2);

		}

		printf("%s\n", "done!");

		fclose(dumpMemory);
	}

}






void startParsing(char *line, char *memPath) {

	int tracker = 0;

	char startAddress[20];

	char stopAddress[20];

	long int cleanStartAddress;

	long int cleanStopAddress;

	for(int i = 0; i < strlen(line); i++) {

		if(line[i] == '-') {

			long int n = strtol(startAddress, NULL, 16);

			cleanStartAddress = n;

			i++;

			for(i; i < strlen(line); i++) {

				if(line[i] == ' ') {

					long int nn = strtol(stopAddress, NULL, 16);

					cleanStopAddress = nn;

					//printf("start address %ld\n", cleanStartAddress);

					//printf("stop address %ld\n", cleanStopAddress);

					dumpMemory(memPath, cleanStartAddress, cleanStopAddress);

					break;

				}

				else {

					stopAddress[tracker] = line[i];

					tracker++;


				}


			}

			break;
		}

		else {

			startAddress[i] = line[i];

		}

	}

}



int main(int argc, char *argv[]) {

        FILE *fp;

        char * line = NULL;

        size_t len = 0;

        ssize_t read;

	char directory[20] = "/proc/";

	char directoryy[20] = "/proc/";

	char *semiPath = strcat(directory, argv[1]);

	char *almostPath = strcat(semiPath, "/");

	char *fullPath = strcat(almostPath, "maps");

        char *semiMemPath = strcat(directoryy, argv[1]);

        char *almostMemPath = strcat(semiMemPath, "/");

        char *fullMemPath = strcat(almostMemPath, "mem");

	fp = fopen(fullPath, "r");

	if(fp == NULL) {

		printf("%s\n", "Error Opening Memory Mapping!");

		exit(0);

	}

	while((read = getline(&line, &len, fp)) != -1) {

		startParsing(line, fullMemPath);

	}


	fclose(fp);


}
