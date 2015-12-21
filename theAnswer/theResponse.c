/*
	NcN CTF 2015
	theAnswer binary solution
	@sha0coder
*/

#include <stdio.h>
#define KEY_SIZE 255

char flag_cyphertext[] = {
	0x53, 0x77, 0x90, 0x1c, 0x10, 0x8a, 0x0e, 0x69, 0x60, 0x25, 0xca,
	0x35, 0x04, 0x27, 0x90, 0x48, 0x15, 0x8d, 0x03, 0x6b, 0x68, 0x77,
	0xcf, 0x37, 0x54, 0x22, 0xcd, 0x4e, 0x40, 0xdd, 0x08, 0x69, 0x34,
	0x22, 0xcb, 0x31, 0x54, 0x27, 0xc6, 0x1e, 0x42, 0x83, 0x59, 0x69,
	0x35, 0x21, 0xc5, 0x67, 0x55, 0x26, 0xcd, 0x47, 0x17, 0xd9, 0x5e,
	0x3d, 0x35, 0x76, 0x99, 0x64, 0x05, 0x25, 0x92, 0x47, 0x47, 0xd8,
	0x0f, 0x38, 0x31, 0x76, 0x9b, 0x6a, 0x55, 0x2d, 0xc2, 0x19, 0x11,
	0x8d, 0x0f, 0x6b, 0x33, 0x75, 0xcb, 0x6b, 0x05, 0x2d, 0x92, 0x4a,
	0x42, 0x8f, 0x0f, 0x6b, 0x66, 0x27, 0xc9, 0x63, 0x50, 0x76, 0xcc,
	0x46, 0x40, 0x8e, 0x5b, 0x35, 0x00
};

char *key;
int seed = 0xDEADBEEF; // the key for predict the randoms
float bucket;


void printFlag(char *key) {
	// from the decompiled
	for(int i=0; i<strlen(flag_cyphertext); i++) 
        	printf("%c", (unsigned char)(flag_cyphertext[i] ^ key[(i % strlen(key))]));
	printf("\n");
}

int randInt(int min, int max) {
	// from the decompiled
	int aux;
	if (max < min) {
        	aux = max;
        	max = min;
        	min = aux;
	}
	return rand() % (max - min + 1) + min;
}

char *computeXorKey() {
	// the key is hidden in the random predictability
	char *key = (char *)malloc(KEY_SIZE);
	memset(key,0,KEY_SIZE);
	srand(seed);
	bucket = (rand()*rand() ^ ~rand()) + rand() + rand();
	for (int thread_id=0; thread_id < KEY_SIZE; thread_id++) {
		//randInt(1,3);
		key[thread_id] = randInt(0x00, 0xff) ^ thread_id;  // simulate a correct order execution of the threads
	}

	return key;
}

int main(void) {
	printFlag(computeXorKey());
	return 1;
}







