/*
 * Checkliste til brug af bibliotek
 * 
 * 
 * 
 * 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #include "../lib/SatCamImage.h"
#include "SatCamImage.h"

/*int main() {
    SYSTEMTIME t_start, t_stop;

    GetSystemTime(&t_start); 
    TestInput();
    GetSystemTime(&t_stop);

    printf("The start time was: %02d:%02d:%02d.%03d\n", 
                t_start.wHour, t_start.wMinute, t_start.wSecond, t_start.wMilliseconds);

    printf("The stop time was: %02d:%02d:%02d.%03d\n", 
            t_stop.wHour, t_stop.wMinute, t_stop.wSecond, t_stop.wMilliseconds);


    return 0;
}*/

unsigned int rBuf[16][16];
unsigned int gBuf[16][16];
unsigned int bBuf[16][16];

int PrintR(int printX, int printY, int xIndex, int yIndex) {
    printf("R buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", rBuf[x+xIndex][y+yIndex]);
        }
        printf("\n");
    }
    printf(")\n");

    return 0;    
}

int PrintG(int printX, int printY, int xIndex, int yIndex) {
    printf("G buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", gBuf[x+xIndex][y+yIndex]);
        }
        printf("\n");
    }
    printf(")\n");

    return 0;    
}

int PrintB(int printX, int printY, int xIndex, int yIndex) {
    printf("B buffer:\n(\n");
    for(int y = 0; y < printY; y++) {
        if(y%8 == 0) {
            printf("\n");
        }
        for(int x = 0; x < printX; x++) {
            if(x%8 == 0) {
                printf("   ");
            }
            printf("%d, ", bBuf[x+xIndex][y+yIndex]);
        }
        printf("\n");
    }
    printf(")\n");

    return 0;    
}

int main() {
	FILE* fInput = fopen("C:\\Users\\sande\\Documents\\Git\\EIT4-410-SatCam\\VSCode\\Compression_Test_pureC\\output\\memdump_comp_buf_fhd", "rb");

	// Find length of the file
    fseek(fInput, 0, SEEK_END);
	long fileLength = ftell(fInput);
	fseek(fInput, 0, SEEK_SET);

    // Make a buffer for the file
    char *buffer = (char*) malloc(sizeof(char)*fileLength);

    // Go through the whole file until feof, put it in buffer
	char ch = (char) fgetc(fInput);
	int buffIndex = 0;
	while(!feof(fInput)) {
		*(buffer + buffIndex) = ch;
		// buffer[i] = ch;
		ch = (char) fgetc(fInput);
		buffIndex++;
	}

    // unsigned char *huffPtrPass;
    // int huffLenPass;

    // RAMToHuffman(buffer, &huffPtrPass, &huffLenPass, TEST2);

    // FILE* fOutput = fopen("testfile.jpg", "wb");
    // RAMToJPEG(buffer, fOutput, MID);

    // return 0;

	// This is for three separate
	for(int y = 0; y < 16; y++) {
		for(int x = 0; x < 16; x++) {
			int dataIndex = (x + (y * 1920)) * 4;
	
	 		rBuf[x][y] = *(buffer + (dataIndex));
     		gBuf[x][y] = *(buffer + (dataIndex + 1));
     		bBuf[x][y] = *(buffer + (dataIndex + 2));
		}
	}
	
	
	PrintR(16, 16, 0, 0);
	PrintG(16, 16, 0, 0);
	PrintB(16, 16, 0, 0);

    // unsigned char *huffPtrPass;
    // int huffLenPass;

    // RAMToHuffman(buffer, &huffPtrPass, &huffLenPass, TEST2);

    FILE* fOutput = fopen("memdump_comp_new.jpeg", "wb");
    RAMToJPEG(buffer, fOutput, MID);
	
	return 0;

    //
	// // This is for one full buffer
	// int buf[48][16];
    //
	// for(int y = 0; y < 16; y++) {
	// 	for(int x = 0; x < 16; x++) {
	// 		int dataIndex = (x + (y * 1920)) * 4;
    //
	// 		buf[3*x][y] = *(buffer + (dataIndex));
	// 		buf[(3*x)+1][y] = *(buffer + (dataIndex + 1));
	// 		buf[(3*x)+2][y] = *(buffer + (dataIndex + 2));
	// 	}
	// }
    //
	// printf("Buffer:\n(\n");
	// for(int y = 0; y < 16; y++) {
	// 	if(y%8 == 0) {
	// 		printf("\n");
	// 	}
	// 	for(int x = 0; x < 48; x++) {
    //         printf("%d, ", buf[x][y]);
    //     }
    //     printf("\n");
	// }
	// printf(")\n");
    //
	// return 0;
}