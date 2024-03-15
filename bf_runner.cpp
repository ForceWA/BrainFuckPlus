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
				printf("%ld", *reading_pointer);
				break;
			}
			
			case ':': {
				printf("%c", *reading_pointer);
				break;
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

bool explain(char* buff) {
	if (!strcmp(buff, "about")) {
		printf("������Github�ϵĲֿ�(�鿴dev��֧)��https://github.com/ForceWA/BrainFuckPlus\nȻ������Ƶ������\n");
		printf("���ǿ����ں����汾��bf++��C++��ϵ��ʹ���ܵ���C++����\n");
		printf("���ǿ����ں����汾��bf��Ϊ�ɶ��Ƶģ�ʹ�䰲ȫ�Ը���\n");
		printf("������ӹ���ɻ��ں����汾���Ӹ����﷨����ʼ�ձ�����BrainFuckһ������\n");
		printf("\n\nbf++������������;��\n");
		printf("���ڷ�ֹ������ƽ⣬bf++���﷨��ɬ�Ѷ�����ֹ������\n");
		printf("����ʵ�ּ򵥵��߼�\n");
		printf("���ڷ�����ż�����Ϊ�ǽ��������ԣ�������Pythonһ�����Ե�������\n...\n");
		goto RETURN;
	}
	else if (!strcmp(buff, "learn")){
		printf("��BrainFuck��ʹ�÷�ʽ����\nhttps://baike.baidu.com/item/Brainfuck/1152785?fr=ge_ala\n�鿴�ٶȰٿ���ѧϰBrainFuck\n");
		printf("bf++��ʹ�÷������ƣ������˸������빦��\n����\":\"��������ַ���\".\"���������\n\n����bf_main.exe������Ҫ�����������У�ʹ�÷�����bf_main.exe <��Ҫ���е��ļ�(���ļ���д��bf++����)> <��bf++���ڴ��С>\n�����Ѿ�׼����bf_hello_world.txt�������bf��������Hello World!\n������Ҫ8����λ�ڴ�\n\n��δ���İ汾�л����Ӹ��๦��\n����about�˽⹦��ǰհ\n");
		goto RETURN;
	}
	else if (!strcmp(buff, "reset")) {
		free(tape);
		init_BF(255);
		printf("������bf++�������ڴ�\n");
	}
	else if(!strcmp(buff, "check")) {
		printf("���Ǵӹ���ָ�뵽�ڴ�ĩβ���ڴ�\n");
		for (int i=reading_pointer-tape;i+tape<reading_pointer+255;i++) {
			if (i+tape >= tape + 255) {
				printf("\n��ʾ��%d����λ���ڴ�\n", 255-(reading_pointer-tape));
				break;
			}
			printf("%ld ", tape[i]);
		}
	}
	else if (!strcmp(buff, "exit"))
		return false;
	else
		run_BF_code(buff, strlen(buff));
	RETURN:
		return true;
}

int main() {
	using namespace std;

	init_BF(255);
	
	char buff[255];
	printf("BrainFuck++ V1.0.0\n\nBrainFuck++��BrainFuck���Եĳ�������һ��ͼ���걸�Ľ��������ԣ���������ǿBrainFuck������(���¼��bf++)\n");
	printf("����learnѧϰʹ��bf++\n");
	printf("����about�˽�����\n����check�鿴��bf++����ָ�뵽�����ڴ�֮����ڴ�\n����reset����bf++�Ĺ����ڴ�\n����exit���˳�\n������벻�����������κ�һ��������Ϊbf++�Ĵ�������\n");
	
	do {
	for (int i=0;i<255;i++)
		buff[i] = ' ';
	printf("\n>>>");
	scanf("%s", buff);
	
	} while(explain(buff));
	
	
	return 0;
}
