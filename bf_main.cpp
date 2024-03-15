#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_NUM 48

long int* tape = NULL;
long int* reading_pointer = NULL;

long long tape_len = 0;

inline long long pow(int a, int n) {
	long long r = 1;
	
	for (int i=0;i<n-1;i++) {
		r *= a;
	}
	return r;
}

long long covert_chars_to_num(char* c, int len) {
	long long ret = 0;
	for (int i=len-1;i>=0;i--) {
		ret += (c[i] - START_NUM) * pow(10, (len - i));
	}
	return ret;
}

inline unsigned int file_length(FILE* f) {
	fseek(f, 0, SEEK_END);
	unsigned int tmp = ftell(f);
	fseek(f, 0, SEEK_SET);
	return tmp;
}

inline void init_BF(long long tape_count) {
	tape = (long int* )calloc(tape_count, sizeof(long int));
	reading_pointer = tape + (int)tape_count / 2;
}

inline long int run_BF_code(char* code, int lentgh) {
	for (int i=0;i<lentgh;i++) {
		switch (code[i]) {
			case ' ': {
				break;
			}
			
			case '+': {
				*reading_pointer += 1;
				break;
			}
			
			case '-': {
				*reading_pointer -= 1;
				break;
			}
			
			case '>': {
				reading_pointer++;
				break;
			}
			
			case '<': {
				reading_pointer--;
				break;
			}
			
			case '.': {
				printf("%ld\n", *reading_pointer);
				break;
			}
			
			case ':': {
				printf("%c", *reading_pointer);
			}
			
			case '[': {
				if (*reading_pointer == 0) {
					unsigned int ics = 1;
					while (code[i+ics] != ']') {
						ics++;
						if (i + ics > lentgh) {
							printf("Error!\n");
							exit(-1);
						}
					}
					i += ics + 1;
				}
				break;
			}
			
			case ']': {
				if (*reading_pointer != 0) {
					unsigned int fics = 1;
					while (code[i-fics] != '[') {
						fics++;
						if (i < fics) {
							printf("Error!\n");
							exit(-1);					
						}
					}
					i -= fics + 1;
				}
			}
		}
	}
	return *reading_pointer;
}

int main(int argv, char** argc) {
	char* code = NULL;
	int len = 0;
	int bfstr_len = 0;
	FILE* f = fopen(argc[1], "r");
	if (!f) {
		printf("Invalid file!\n");
		return -1;
	}
	printf("%s\n", argc[1]);

	bfstr_len = strlen(argc[2]);

	init_BF(covert_chars_to_num(argc[2], bfstr_len));
	
	len = file_length(f) + 1;
	
	code = (char* )calloc(len, sizeof(char));
	for (int i=0;i<len;i++) {
		code[i] = fgetc(f);
	}
	printf("%s\n", code);
	
	printf("----------------result here------------------\n");
	
	long int ret = run_BF_code(code, len);
	printf("\n\n\nprogram return with value %d\n", ret);
	fclose(f);
	free(tape);
	free(code);
	return 0;
}
