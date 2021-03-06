#include <stdio.h>
#include <string.h>

#define catAmount 12

// ((catAmount-2)*16) + 2 is due to the following:
// The category table includes from 0 to B, codes go from run 0 to run F. The AC tables go from 1 to A, except for EOB and ZRL which are 0,0 and F,0
#define codeTableSize (((catAmount - 2) * 16) + 2)

unsigned char outString[32] = {0b00011000, 0b00000000, 0b00000000, 0b00011001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000};
size_t maxBitPos = sizeof(outString) * 8;
size_t bitPosInOutString = 0;

// This adds bits to the huffman output string
int AddToBitString(int len, signed short bitsToAdd, int isNegative) {
    if(isNegative) {
        bitsToAdd = bitsToAdd-1;
    }

	unsigned char b;

	for(int i = len - 1; 0 <= i; i--) {
		/* If we reach the boundary of our buffer, exit */
		if(bitPosInOutString+1 >= maxBitPos) return 0;

		b = (bitsToAdd >> i) & 0b01;

		if(b) {
			outString[(bitPosInOutString/8)] |= (b<<(7-bitPosInOutString+(8*(bitPosInOutString/8))));
		}
		else {
			outString[(bitPosInOutString/8)] &= ~(b<<(7-bitPosInOutString+(8*(bitPosInOutString/8))));
		}

		// printf("Byte 1: %d  ", huffOutput[0]);
		// printf("Byte 2: %d  ", huffOutput[1]);
		// printf("Byte 3: %d  ", huffOutput[2]);
		// printf("Byte 4: %d  ", huffOutput[3]);
		// printf("Byte 5: %d  ", huffOutput[4]);
		// printf("Byte 6: %d  ", huffOutput[5]);
		// printf("bitPos: %d  ", bitPosInOutString);
		// printf("bitPos/8: %d\n", (bitPosInOutString/8));

		bitPosInOutString++;

        if(bitPosInOutString%8 == 0) {
            // printf("aaaa\n");
            if(outString[(bitPosInOutString/8) - 1] == 255) {
                // printf("AAAA\n");
                bitPosInOutString = bitPosInOutString + 8;
            }
        }
	}

	return 1;
}

// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("\n");
}

int main() {
	signed short testNumbers[13] = {
		213,
		3,
		0,
		-9,
		0,
		0,
		22,
		94,
		0,
		-14,
		0,
		-127,
		-117,
	};

	for(int i = 0; i < 13; i++) {
		printBits(sizeof(short), &testNumbers[i]);
	}

	return 0;
}

// int main()
// {
// 	static const size_t huffCatTable[catAmount][2] = {
// 		{0,0}, {1,1}, {2,3}, {4,7}, {8,15}, {16,31}, {32,63},
// 		{64,127}, {128,255}, {256,511}, {512,1023}, {1024,2047}
// 	};

// 	static const unsigned short dcLumiCodeTable[catAmount][2] = {
// 		{2, 0b00},
// 		{3, 0b010},
// 		{3, 0b011},
// 		{3, 0b100},
// 		{3, 0b101},
// 		{3, 0b110},
// 		{4, 0b1110},
// 		{5, 0b11110},
// 		{6, 0b111110},
// 		{7, 0b1111110},
// 		{8, 0b11111110},
// 		{9, 0b111111110},
// 	};

// 	static const unsigned short dcChromiCodeTable[catAmount][2] = {
// 		{2, 0b00},
// 		{2, 0b01},
// 		{2, 0b10},
// 		{3, 0b110},
// 		{4, 0b1110},
// 		{5, 0b11110},
// 		{6, 0b111110},
// 		{7, 0b1111110},
// 		{8, 0b11111110},
// 		{9, 0b111111110},
// 		{10, 0b1111111110},
// 		{11, 0b11111111110},
// 	};

// 	static const unsigned short acLumiCodeTable[codeTableSize][2] = {
// 		{4, 0b1010},
// 		{2, 0b00},
// 		{2, 0b01},
// 		{3, 0b100},
// 		{4, 0b1011},
// 		{5, 0b11010},
// 		{7, 0b1111000},
// 		{8, 0b11111000},
// 		{10, 0b1111110110},
// 		{16, 0b1111111110000010},
// 		{16, 0b1111111110000011},
// 		{4, 0b1100},
// 		{5, 0b11011},
// 		{7, 0b1111001},
// 		{9, 0b111110110},
// 		{11, 0b11111110110},
// 		{16, 0b1111111110000100},
// 		{16, 0b1111111110000101},
// 		{16, 0b1111111110000110},
// 		{16, 0b1111111110000111},
// 		{16, 0b1111111110001000},
// 		{5, 0b11100},
// 		{8, 0b11111001},
// 		{10, 0b1111110111},
// 		{12, 0b111111110100},
// 		{16, 0b1111111110001001},
// 		{16, 0b1111111110001010},
// 		{16, 0b1111111110001011},
// 		{16, 0b1111111110001100},
// 		{16, 0b1111111110001101},
// 		{16, 0b1111111110001110},
// 		{6, 0b111010},
// 		{9, 0b111110111},
// 		{12, 0b111111110101},
// 		{16, 0b1111111110001111},
// 		{16, 0b1111111110010000},
// 		{16, 0b1111111110010001},
// 		{16, 0b1111111110010010},
// 		{16, 0b1111111110010011},
// 		{16, 0b1111111110010100},
// 		{16, 0b1111111110010101},
// 		{6, 0b111011},
// 		{10, 0b1111111000},
// 		{16, 0b1111111110010110},
// 		{16, 0b1111111110010111},
// 		{16, 0b1111111110011000},
// 		{16, 0b1111111110011001},
// 		{16, 0b1111111110011010},
// 		{16, 0b1111111110011011},
// 		{16, 0b1111111110011100},
// 		{16, 0b1111111110011101},
// 		{7, 0b1111010},
// 		{11, 0b11111110111},
// 		{16, 0b1111111110011110},
// 		{16, 0b1111111110011111},
// 		{16, 0b1111111110100000},
// 		{16, 0b1111111110100001},
// 		{16, 0b1111111110100010},
// 		{16, 0b1111111110100011},
// 		{16, 0b1111111110100100},
// 		{16, 0b1111111110100101},
// 		{7, 0b1111011},
// 		{12, 0b111111110110},
// 		{16, 0b1111111110100110},
// 		{16, 0b1111111110100111},
// 		{16, 0b1111111110101000},
// 		{16, 0b1111111110101001},
// 		{16, 0b1111111110101010},
// 		{16, 0b1111111110101011},
// 		{16, 0b1111111110101100},
// 		{16, 0b1111111110101101},
// 		{8, 0b11111010},
// 		{12, 0b111111110111},
// 		{16, 0b1111111110101110},
// 		{16, 0b1111111110101111},
// 		{16, 0b1111111110110000},
// 		{16, 0b1111111110110001},
// 		{16, 0b1111111110110010},
// 		{16, 0b1111111110110011},
// 		{16, 0b1111111110110100},
// 		{16, 0b1111111110110101},
// 		{9, 0b111111000},
// 		{15, 0b111111111000000},
// 		{16, 0b1111111110110110},
// 		{16, 0b1111111110110111},
// 		{16, 0b1111111110111000},
// 		{16, 0b1111111110111001},
// 		{16, 0b1111111110111010},
// 		{16, 0b1111111110111011},
// 		{16, 0b1111111110111100},
// 		{16, 0b1111111110111101},
// 		{9, 0b111111001},
// 		{16, 0b1111111110111110},
// 		{16, 0b1111111110111111},
// 		{16, 0b1111111111000000},
// 		{16, 0b1111111111000001},
// 		{16, 0b1111111111000010},
// 		{16, 0b1111111111000011},
// 		{16, 0b1111111111000100},
// 		{16, 0b1111111111000101},
// 		{16, 0b1111111111000110},
// 		{9, 0b111111010},
// 		{16, 0b1111111111000111},
// 		{16, 0b1111111111001000},
// 		{16, 0b1111111111001001},
// 		{16, 0b1111111111001010},
// 		{16, 0b1111111111001011},
// 		{16, 0b1111111111001100},
// 		{16, 0b1111111111001101},
// 		{16, 0b1111111111001110},
// 		{16, 0b1111111111001111},
// 		{10, 0b1111111001},
// 		{16, 0b1111111111010000},
// 		{16, 0b1111111111010001},
// 		{16, 0b1111111111010010},
// 		{16, 0b1111111111010011},
// 		{16, 0b1111111111010100},
// 		{16, 0b1111111111010101},
// 		{16, 0b1111111111010110},
// 		{16, 0b1111111111010111},
// 		{16, 0b1111111111011000},
// 		{10, 0b1111111010},
// 		{16, 0b1111111111011001},
// 		{16, 0b1111111111011010},
// 		{16, 0b1111111111011011},
// 		{16, 0b1111111111011100},
// 		{16, 0b1111111111011101},
// 		{16, 0b1111111111011110},
// 		{16, 0b1111111111011111},
// 		{16, 0b1111111111100000},
// 		{16, 0b1111111111100001},
// 		{11, 0b11111111000},
// 		{16, 0b1111111111100010},
// 		{16, 0b1111111111100011},
// 		{16, 0b1111111111100100},
// 		{16, 0b1111111111100101},
// 		{16, 0b1111111111100110},
// 		{16, 0b1111111111100111},
// 		{16, 0b1111111111101000},
// 		{16, 0b1111111111101001},
// 		{16, 0b1111111111101010},
// 		{16, 0b1111111111101011},
// 		{16, 0b1111111111101100},
// 		{16, 0b1111111111101101},
// 		{16, 0b1111111111101110},
// 		{16, 0b1111111111101111},
// 		{16, 0b1111111111110000},
// 		{16, 0b1111111111110001},
// 		{16, 0b1111111111110010},
// 		{16, 0b1111111111110011},
// 		{16, 0b1111111111110100},
// 		{11, 0b11111111001},
// 		{16, 0b1111111111110101},
// 		{16, 0b1111111111110110},
// 		{16, 0b1111111111110111},
// 		{16, 0b1111111111111000},
// 		{16, 0b1111111111111001},
// 		{16, 0b1111111111111010},
// 		{16, 0b1111111111111011},
// 		{16, 0b1111111111111100},
// 		{16, 0b1111111111111101},
// 		{16, 0b1111111111111110},
// 	};

// 	static const unsigned short acChromiCodeTable[codeTableSize][2] = {
// 		{2, 0b00},
// 		{2, 0b01},
// 		{3, 0b100},
// 		{4, 0b1010},
// 		{5, 0b11000},
// 		{5, 0b11001},
// 		{6, 0b111000},
// 		{7, 0b1111000},
// 		{9, 0b111110100},
// 		{10, 0b1111110110},
// 		{12, 0b111111110100},
// 		{4, 0b1011},
// 		{6, 0b111001},
// 		{8, 0b11110110},
// 		{9, 0b111110101},
// 		{11, 0b11111110110},
// 		{12, 0b111111110101},
// 		{16, 0b1111111110001000},
// 		{16, 0b1111111110001001},
// 		{16, 0b1111111110001010},
// 		{16, 0b1111111110001011},
// 		{5, 0b11010},
// 		{8, 0b11110111},
// 		{10, 0b1111110111},
// 		{12, 0b111111110110},
// 		{15, 0b111111111000010},
// 		{16, 0b1111111110001100},
// 		{16, 0b1111111110001101},
// 		{16, 0b1111111110001110},
// 		{16, 0b1111111110001111},
// 		{16, 0b1111111110010000},
// 		{5, 0b11011},
// 		{8, 0b11111000},
// 		{10, 0b1111111000},
// 		{12, 0b111111110111},
// 		{16, 0b1111111110010001},
// 		{16, 0b1111111110010010},
// 		{16, 0b1111111110010011},
// 		{16, 0b1111111110010100},
// 		{16, 0b1111111110010101},
// 		{16, 0b1111111110010110},
// 		{6, 0b111010},
// 		{9, 0b111110110},
// 		{16, 0b1111111110010111},
// 		{16, 0b1111111110011000},
// 		{16, 0b1111111110011001},
// 		{16, 0b1111111110011010},
// 		{16, 0b1111111110011011},
// 		{16, 0b1111111110011100},
// 		{16, 0b1111111110011101},
// 		{16, 0b1111111110011110},
// 		{6, 0b111011},
// 		{10, 0b1111111001},
// 		{16, 0b1111111110011111},
// 		{16, 0b1111111110100000},
// 		{16, 0b1111111110100001},
// 		{16, 0b1111111110100010},
// 		{16, 0b1111111110100011},
// 		{16, 0b1111111110100100},
// 		{16, 0b1111111110100101},
// 		{16, 0b1111111110100110},
// 		{7, 0b1111001},
// 		{11, 0b11111110111},
// 		{16, 0b1111111110100111},
// 		{16, 0b1111111110101000},
// 		{16, 0b1111111110101001},
// 		{16, 0b1111111110101010},
// 		{16, 0b1111111110101011},
// 		{16, 0b1111111110101100},
// 		{16, 0b1111111110101101},
// 		{16, 0b1111111110101110},
// 		{7, 0b1111010},
// 		{11, 0b11111111000},
// 		{16, 0b1111111110101111},
// 		{16, 0b1111111110110000},
// 		{16, 0b1111111110110001},
// 		{16, 0b1111111110110010},
// 		{16, 0b1111111110110011},
// 		{16, 0b1111111110110100},
// 		{16, 0b1111111110110101},
// 		{16, 0b1111111110110110},
// 		{8, 0b11111001},
// 		{16, 0b1111111110110111},
// 		{16, 0b1111111110111000},
// 		{16, 0b1111111110111001},
// 		{16, 0b1111111110111010},
// 		{16, 0b1111111110111011},
// 		{16, 0b1111111110111100},
// 		{16, 0b1111111110111101},
// 		{16, 0b1111111110111110},
// 		{16, 0b1111111110111111},
// 		{9, 0b111110111},
// 		{16, 0b1111111111000000},
// 		{16, 0b1111111111000001},
// 		{16, 0b1111111111000010},
// 		{16, 0b1111111111000011},
// 		{16, 0b1111111111000100},
// 		{16, 0b1111111111000101},
// 		{16, 0b1111111111000110},
// 		{16, 0b1111111111000111},
// 		{16, 0b1111111111001000},
// 		{9, 0b111111000},
// 		{16, 0b1111111111001001},
// 		{16, 0b1111111111001010},
// 		{16, 0b1111111111001011},
// 		{16, 0b1111111111001100},
// 		{16, 0b1111111111001101},
// 		{16, 0b1111111111001110},
// 		{16, 0b1111111111001111},
// 		{16, 0b1111111111010000},
// 		{16, 0b1111111111010001},
// 		{9, 0b111111001},
// 		{16, 0b1111111111010010},
// 		{16, 0b1111111111010011},
// 		{16, 0b1111111111010100},
// 		{16, 0b1111111111010101},
// 		{16, 0b1111111111010110},
// 		{16, 0b1111111111010111},
// 		{16, 0b1111111111011000},
// 		{16, 0b1111111111011001},
// 		{16, 0b1111111111011010},
// 		{9, 0b111111010},
// 		{16, 0b1111111111011011},
// 		{16, 0b1111111111011100},
// 		{16, 0b1111111111011101},
// 		{16, 0b1111111111011110},
// 		{16, 0b1111111111011111},
// 		{16, 0b1111111111100000},
// 		{16, 0b1111111111100001},
// 		{16, 0b1111111111100010},
// 		{16, 0b1111111111100011},
// 		{11, 0b11111111001},
// 		{16, 0b1111111111100100},
// 		{16, 0b1111111111100101},
// 		{16, 0b1111111111100110},
// 		{16, 0b1111111111100111},
// 		{16, 0b1111111111101000},
// 		{16, 0b1111111111101001},
// 		{16, 0b1111111111101010},
// 		{16, 0b1111111111101011},
// 		{16, 0b1111111111101100},
// 		{14, 0b11111111100000},
// 		{16, 0b1111111111101101},
// 		{16, 0b1111111111101110},
// 		{16, 0b1111111111101111},
// 		{16, 0b1111111111110000},
// 		{16, 0b1111111111110001},
// 		{16, 0b1111111111110010},
// 		{16, 0b1111111111110011},
// 		{16, 0b1111111111110100},
// 		{16, 0b1111111111110101},
// 		{10, 0b1111111010},
// 		{15, 0b111111111000011},
// 		{16, 0b1111111111110110},
// 		{16, 0b1111111111110111},
// 		{16, 0b1111111111111000},
// 		{16, 0b1111111111111001},
// 		{16, 0b1111111111111010},
// 		{16, 0b1111111111111011},
// 		{16, 0b1111111111111100},
// 		{16, 0b1111111111111101},
// 		{16, 0b1111111111111110},
// 	};

// 	unsigned short testString[7][2] = {
// 		{16, 0b0110001110011001},
// 		{11, 0b00111001101},
// 		{6, 0b101011},
// 		{8, 0b00011100},
// 		{5, 0b10110},
// 		{3, 0b011},
// 		{8, 0b10011001},
// 	};

// 	unsigned char outString[8] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000};

// 	size_t bitPos = 0;
// 	size_t bytePos = 0;

// 	unsigned char b;
// 	while(1) {
// 		for(int j = 0; j < 7; j++) {
// 			for(int i = testString[j][0] - 1; 0 <= i; i--) {
// 				b = (testString[j][1] >> (i)) & 0b01;

// 				if(b) {
// 					outString[(bitPos/8)] |= (b<<(7-bitPos+(8*(bitPos/8))));
// 				}
// 				else {
// 					outString[(bitPos/8)] &= ~(b<<(7-bitPos+(8*(bitPos/8))));
// 				}

// 				printf("Byte: %d  byte data: %d  j: %d  bitPos: %d\n", (bitPos/8), outString[bitPos/8], j, bitPos);
// 				// printf("Byte 1: %d  ", outString[0]);
// 				// printf("Byte 2: %d  ", outString[1]);
// 				// printf("Byte 3: %d  ", outString[2]);
// 				// printf("Byte 4: %d  ", outString[3]);
// 				// printf("Byte 5: %d  ", outString[4]);
// 				// printf("Byte 6: %d  ", outString[5]);
// 				// printf("j: %d  ", j);
// 				// printf("bitPos: %d  ", bitPos);
// 				// printf("bitPos/8: %d\n", (bitPos/8));
// 				bitPos++;
// 			}
// 		}

// 		printf("Done printing\n");
// 		break;
// 	}

// 	return 0;
// }

// int main() {
// 	for(int i = 0; i < 32; i++) {
// 		printf("%d ", outString[i]);
// 	}
// 	printf("\n");
// 	memset(outString, 0, 32);
// 	for(int i = 0; i < 32; i++) {
// 		printf("%d ", outString[i]);
// 	}
// 	printf("\n");

// 	/* Tables for categories */
// 	static const size_t huffCatTable[catAmount][2] = {
// 		{0,0}, {1,1}, {2,3}, {4,7}, {8,15}, {16,31}, {32,63},
// 		{64,127}, {128,255}, {256,511}, {512,1023}, {1024,2047}
// 	};

// 	/* Tables for Huffman codes */
// 	static const unsigned short dcLumiCodeTable[catAmount][2] = {
// 		{2, 0b00},
// 		{3, 0b010},
// 		{3, 0b011},
// 		{3, 0b100},
// 		{3, 0b101},
// 		{3, 0b110},
// 		{4, 0b1110},
// 		{5, 0b11110},
// 		{6, 0b111110},
// 		{7, 0b1111110},
// 		{8, 0b11111110},
// 		{9, 0b111111110},
// 	};

// 	static const unsigned short dcChromiCodeTable[catAmount][2] = {
// 		{2, 0b00},
// 		{2, 0b01},
// 		{2, 0b10},
// 		{3, 0b110},
// 		{4, 0b1110},
// 		{5, 0b11110},
// 		{6, 0b111110},
// 		{7, 0b1111110},
// 		{8, 0b11111110},
// 		{9, 0b111111110},
// 		{10, 0b1111111110},
// 		{11, 0b11111111110},
// 	};

// 	static const unsigned short acLumiCodeTable[codeTableSize][2] = {
// 		{4, 0b1010},
// 		{2, 0b00},
// 		{2, 0b01},
// 		{3, 0b100},
// 		{4, 0b1011},
// 		{5, 0b11010},
// 		{7, 0b1111000},
// 		{8, 0b11111000},
// 		{10, 0b1111110110},
// 		{16, 0b1111111110000010},
// 		{16, 0b1111111110000011},
// 		{4, 0b1100},
// 		{5, 0b11011},
// 		{7, 0b1111001},
// 		{9, 0b111110110},
// 		{11, 0b11111110110},
// 		{16, 0b1111111110000100},
// 		{16, 0b1111111110000101},
// 		{16, 0b1111111110000110},
// 		{16, 0b1111111110000111},
// 		{16, 0b1111111110001000},
// 		{5, 0b11100},
// 		{8, 0b11111001},
// 		{10, 0b1111110111},
// 		{12, 0b111111110100},
// 		{16, 0b1111111110001001},
// 		{16, 0b1111111110001010},
// 		{16, 0b1111111110001011},
// 		{16, 0b1111111110001100},
// 		{16, 0b1111111110001101},
// 		{16, 0b1111111110001110},
// 		{6, 0b111010},
// 		{9, 0b111110111},
// 		{12, 0b111111110101},
// 		{16, 0b1111111110001111},
// 		{16, 0b1111111110010000},
// 		{16, 0b1111111110010001},
// 		{16, 0b1111111110010010},
// 		{16, 0b1111111110010011},
// 		{16, 0b1111111110010100},
// 		{16, 0b1111111110010101},
// 		{6, 0b111011},
// 		{10, 0b1111111000},
// 		{16, 0b1111111110010110},
// 		{16, 0b1111111110010111},
// 		{16, 0b1111111110011000},
// 		{16, 0b1111111110011001},
// 		{16, 0b1111111110011010},
// 		{16, 0b1111111110011011},
// 		{16, 0b1111111110011100},
// 		{16, 0b1111111110011101},
// 		{7, 0b1111010},
// 		{11, 0b11111110111},
// 		{16, 0b1111111110011110},
// 		{16, 0b1111111110011111},
// 		{16, 0b1111111110100000},
// 		{16, 0b1111111110100001},
// 		{16, 0b1111111110100010},
// 		{16, 0b1111111110100011},
// 		{16, 0b1111111110100100},
// 		{16, 0b1111111110100101},
// 		{7, 0b1111011},
// 		{12, 0b111111110110},
// 		{16, 0b1111111110100110},
// 		{16, 0b1111111110100111},
// 		{16, 0b1111111110101000},
// 		{16, 0b1111111110101001},
// 		{16, 0b1111111110101010},
// 		{16, 0b1111111110101011},
// 		{16, 0b1111111110101100},
// 		{16, 0b1111111110101101},
// 		{8, 0b11111010},
// 		{12, 0b111111110111},
// 		{16, 0b1111111110101110},
// 		{16, 0b1111111110101111},
// 		{16, 0b1111111110110000},
// 		{16, 0b1111111110110001},
// 		{16, 0b1111111110110010},
// 		{16, 0b1111111110110011},
// 		{16, 0b1111111110110100},
// 		{16, 0b1111111110110101},
// 		{9, 0b111111000},
// 		{15, 0b111111111000000},
// 		{16, 0b1111111110110110},
// 		{16, 0b1111111110110111},
// 		{16, 0b1111111110111000},
// 		{16, 0b1111111110111001},
// 		{16, 0b1111111110111010},
// 		{16, 0b1111111110111011},
// 		{16, 0b1111111110111100},
// 		{16, 0b1111111110111101},
// 		{9, 0b111111001},
// 		{16, 0b1111111110111110},
// 		{16, 0b1111111110111111},
// 		{16, 0b1111111111000000},
// 		{16, 0b1111111111000001},
// 		{16, 0b1111111111000010},
// 		{16, 0b1111111111000011},
// 		{16, 0b1111111111000100},
// 		{16, 0b1111111111000101},
// 		{16, 0b1111111111000110},
// 		{9, 0b111111010},
// 		{16, 0b1111111111000111},
// 		{16, 0b1111111111001000},
// 		{16, 0b1111111111001001},
// 		{16, 0b1111111111001010},
// 		{16, 0b1111111111001011},
// 		{16, 0b1111111111001100},
// 		{16, 0b1111111111001101},
// 		{16, 0b1111111111001110},
// 		{16, 0b1111111111001111},
// 		{10, 0b1111111001},
// 		{16, 0b1111111111010000},
// 		{16, 0b1111111111010001},
// 		{16, 0b1111111111010010},
// 		{16, 0b1111111111010011},
// 		{16, 0b1111111111010100},
// 		{16, 0b1111111111010101},
// 		{16, 0b1111111111010110},
// 		{16, 0b1111111111010111},
// 		{16, 0b1111111111011000},
// 		{10, 0b1111111010},
// 		{16, 0b1111111111011001},
// 		{16, 0b1111111111011010},
// 		{16, 0b1111111111011011},
// 		{16, 0b1111111111011100},
// 		{16, 0b1111111111011101},
// 		{16, 0b1111111111011110},
// 		{16, 0b1111111111011111},
// 		{16, 0b1111111111100000},
// 		{16, 0b1111111111100001},
// 		{11, 0b11111111000},
// 		{16, 0b1111111111100010},
// 		{16, 0b1111111111100011},
// 		{16, 0b1111111111100100},
// 		{16, 0b1111111111100101},
// 		{16, 0b1111111111100110},
// 		{16, 0b1111111111100111},
// 		{16, 0b1111111111101000},
// 		{16, 0b1111111111101001},
// 		{16, 0b1111111111101010},
// 		{16, 0b1111111111101011},
// 		{16, 0b1111111111101100},
// 		{16, 0b1111111111101101},
// 		{16, 0b1111111111101110},
// 		{16, 0b1111111111101111},
// 		{16, 0b1111111111110000},
// 		{16, 0b1111111111110001},
// 		{16, 0b1111111111110010},
// 		{16, 0b1111111111110011},
// 		{16, 0b1111111111110100},
// 		{16, 0b1111111111110101},
// 		{16, 0b1111111111110110},
// 		{16, 0b1111111111110111},
// 		{16, 0b1111111111111000},
// 		{16, 0b1111111111111001},
// 		{16, 0b1111111111111010},
// 		{16, 0b1111111111111011},
// 		{16, 0b1111111111111100},
// 		{16, 0b1111111111111101},
// 		{16, 0b1111111111111110},
// 		{11, 0b11111111001},
// 	};

// 	static const unsigned short acChromiCodeTable[codeTableSize][2] = {
// 		{2, 0b00},
// 		{2, 0b01},
// 		{3, 0b100},
// 		{4, 0b1010},
// 		{5, 0b11000},
// 		{5, 0b11001},
// 		{6, 0b111000},
// 		{7, 0b1111000},
// 		{9, 0b111110100},
// 		{10, 0b1111110110},
// 		{12, 0b111111110100},
// 		{4, 0b1011},
// 		{6, 0b111001},
// 		{8, 0b11110110},
// 		{9, 0b111110101},
// 		{11, 0b11111110110},
// 		{12, 0b111111110101},
// 		{16, 0b1111111110001000},
// 		{16, 0b1111111110001001},
// 		{16, 0b1111111110001010},
// 		{16, 0b1111111110001011},
// 		{5, 0b11010},
// 		{8, 0b11110111},
// 		{10, 0b1111110111},
// 		{12, 0b111111110110},
// 		{15, 0b111111111000010},
// 		{16, 0b1111111110001100},
// 		{16, 0b1111111110001101},
// 		{16, 0b1111111110001110},
// 		{16, 0b1111111110001111},
// 		{16, 0b1111111110010000},
// 		{5, 0b11011},
// 		{8, 0b11111000},
// 		{10, 0b1111111000},
// 		{12, 0b111111110111},
// 		{16, 0b1111111110010001},
// 		{16, 0b1111111110010010},
// 		{16, 0b1111111110010011},
// 		{16, 0b1111111110010100},
// 		{16, 0b1111111110010101},
// 		{16, 0b1111111110010110},
// 		{6, 0b111010},
// 		{9, 0b111110110},
// 		{16, 0b1111111110010111},
// 		{16, 0b1111111110011000},
// 		{16, 0b1111111110011001},
// 		{16, 0b1111111110011010},
// 		{16, 0b1111111110011011},
// 		{16, 0b1111111110011100},
// 		{16, 0b1111111110011101},
// 		{16, 0b1111111110011110},
// 		{6, 0b111011},
// 		{10, 0b1111111001},
// 		{16, 0b1111111110011111},
// 		{16, 0b1111111110100000},
// 		{16, 0b1111111110100001},
// 		{16, 0b1111111110100010},
// 		{16, 0b1111111110100011},
// 		{16, 0b1111111110100100},
// 		{16, 0b1111111110100101},
// 		{16, 0b1111111110100110},
// 		{7, 0b1111001},
// 		{11, 0b11111110111},
// 		{16, 0b1111111110100111},
// 		{16, 0b1111111110101000},
// 		{16, 0b1111111110101001},
// 		{16, 0b1111111110101010},
// 		{16, 0b1111111110101011},
// 		{16, 0b1111111110101100},
// 		{16, 0b1111111110101101},
// 		{16, 0b1111111110101110},
// 		{7, 0b1111010},
// 		{11, 0b11111111000},
// 		{16, 0b1111111110101111},
// 		{16, 0b1111111110110000},
// 		{16, 0b1111111110110001},
// 		{16, 0b1111111110110010},
// 		{16, 0b1111111110110011},
// 		{16, 0b1111111110110100},
// 		{16, 0b1111111110110101},
// 		{16, 0b1111111110110110},
// 		{8, 0b11111001},
// 		{16, 0b1111111110110111},
// 		{16, 0b1111111110111000},
// 		{16, 0b1111111110111001},
// 		{16, 0b1111111110111010},
// 		{16, 0b1111111110111011},
// 		{16, 0b1111111110111100},
// 		{16, 0b1111111110111101},
// 		{16, 0b1111111110111110},
// 		{16, 0b1111111110111111},
// 		{9, 0b111110111},
// 		{16, 0b1111111111000000},
// 		{16, 0b1111111111000001},
// 		{16, 0b1111111111000010},
// 		{16, 0b1111111111000011},
// 		{16, 0b1111111111000100},
// 		{16, 0b1111111111000101},
// 		{16, 0b1111111111000110},
// 		{16, 0b1111111111000111},
// 		{16, 0b1111111111001000},
// 		{9, 0b111111000},
// 		{16, 0b1111111111001001},
// 		{16, 0b1111111111001010},
// 		{16, 0b1111111111001011},
// 		{16, 0b1111111111001100},
// 		{16, 0b1111111111001101},
// 		{16, 0b1111111111001110},
// 		{16, 0b1111111111001111},
// 		{16, 0b1111111111010000},
// 		{16, 0b1111111111010001},
// 		{9, 0b111111001},
// 		{16, 0b1111111111010010},
// 		{16, 0b1111111111010011},
// 		{16, 0b1111111111010100},
// 		{16, 0b1111111111010101},
// 		{16, 0b1111111111010110},
// 		{16, 0b1111111111010111},
// 		{16, 0b1111111111011000},
// 		{16, 0b1111111111011001},
// 		{16, 0b1111111111011010},
// 		{9, 0b111111010},
// 		{16, 0b1111111111011011},
// 		{16, 0b1111111111011100},
// 		{16, 0b1111111111011101},
// 		{16, 0b1111111111011110},
// 		{16, 0b1111111111011111},
// 		{16, 0b1111111111100000},
// 		{16, 0b1111111111100001},
// 		{16, 0b1111111111100010},
// 		{16, 0b1111111111100011},
// 		{11, 0b11111111001},
// 		{16, 0b1111111111100100},
// 		{16, 0b1111111111100101},
// 		{16, 0b1111111111100110},
// 		{16, 0b1111111111100111},
// 		{16, 0b1111111111101000},
// 		{16, 0b1111111111101001},
// 		{16, 0b1111111111101010},
// 		{16, 0b1111111111101011},
// 		{16, 0b1111111111101100},
// 		{14, 0b11111111100000},
// 		{16, 0b1111111111101101},
// 		{16, 0b1111111111101110},
// 		{16, 0b1111111111101111},
// 		{16, 0b1111111111110000},
// 		{16, 0b1111111111110001},
// 		{16, 0b1111111111110010},
// 		{16, 0b1111111111110011},
// 		{16, 0b1111111111110100},
// 		{16, 0b1111111111110101},
// 		{15, 0b111111111000011},
// 		{16, 0b1111111111110110},
// 		{16, 0b1111111111110111},
// 		{16, 0b1111111111111000},
// 		{16, 0b1111111111111001},
// 		{16, 0b1111111111111010},
// 		{16, 0b1111111111111011},
// 		{16, 0b1111111111111100},
// 		{16, 0b1111111111111101},
// 		{16, 0b1111111111111110},
// 		{10, 0b1111111010},
// 	};

// 	unsigned short testString[7][2] = {
// 		{16, 0b0110001110011001},
// 		{11, 0b00111001101},
// 		{6, 0b101011},
// 		{8, 0b00011100},
// 		{5, 0b10110},
// 		{3, 0b011},
// 		{8, 0b10011001},
// 	};

// 	signed short testNumbers[13] = {
// 		213,
// 		3,
// 		0,
// 		-9,
// 		0,
// 		0,
// 		22,
// 		94,
// 		0,
// 		-14,
// 		0,
// 		0,
// 		0,
// 	};



// 	while(1) {
// 		int zeroCtr = 0;
//     	int bigZeroCtr = 0;
		
// 		for(int j = 0; j < 12; j++) {
// 			// Find category
// 			int cat = -1;
// 			for(int i = 0; i < catAmount; i++) {
// 				if((huffCatTable[i][0] <= testNumbers[j] && huffCatTable[i][1] >= testNumbers[j]) 
// 					|| (-huffCatTable[i][0] >= testNumbers[j] && -huffCatTable[i][1] <= testNumbers[j])) {
					
// 					cat = i;
// 					printf("Category: %d\n", cat);
// 					i = catAmount+1;
// 				}
// 			}
// 			if(cat == -1) {
// 				printf("Cat dumb\n");
// 				continue;
// 			}

// 			// Do differently if DC

// 			// This below is AC
// 			if(testNumbers[j] == 0){
// 				zeroCtr++;
// 				if(zeroCtr >= 15) {
// 					zeroCtr = 0;
// 					bigZeroCtr++;
// 				}
// 				continue;
// 			}
// 			else {
// 				// So long as there are 15 zeros in a row
// 				while(bigZeroCtr != 0) {
// 					if(!AddToBitString(acLumiCodeTable[161][0], acLumiCodeTable[161][1])) {
// 						printf("Something went wrong on AddToBitString 3\n");
// 					}
					
// 					bigZeroCtr--;
// 				}

// 				size_t tableIndex = zeroCtr*10 + cat;
				
// 				// Add in base code
// 				if(!AddToBitString(acLumiCodeTable[tableIndex][0], acLumiCodeTable[tableIndex][1])) {
// 					printf("Something went wrong on AddToBitString 1\n");
// 				}

// 				// Add in last bits
// 				int numCtr = 0;
// 				if(cat > 4) numCtr = 4;
// 				else numCtr = cat;

// 				if(!AddToBitString(numCtr, testNumbers[j])) {
// 					printf("Something went wrong on AddToBitString 2\n");
// 				}

// 				zeroCtr = 0;
// 			}

// 			// printf("Byte: %d  byte data: %d  j: %d  bitPos: %d\n", (bitPosInOutString/8), outString[bitPosInOutString/8], j, bitPosInOutString);
// 		}

// 		// Add EOB
// 		zeroCtr = 0;
// 		bigZeroCtr = 0;
// 		AddToBitString(acChromiCodeTable[0][0], acChromiCodeTable[0][1]);
		
// 		printf("Done printing\n");
// 		break;
// 	}

// 	return 0;
// }