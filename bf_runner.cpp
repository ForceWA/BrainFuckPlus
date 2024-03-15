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
		printf("我们在Github上的仓库(查看dev分支)：https://github.com/ForceWA/BrainFuckPlus\n然而不会频繁更新\n");
		printf("我们可能在后续版本将bf++与C++联系，使其能调用C++函数\n");
		printf("我们可能在后续版本将bf改为可定制的，使其安全性更好\n");
		printf("我们毋庸置疑会在后续版本增加更多语法，但始终保持像BrainFuck一样整洁\n");
		printf("\n\nbf++可能有以下用途：\n");
		printf("用于防止软件被破解，bf++的语法晦涩难懂，防止反编译\n");
		printf("用于实现简单的逻辑\n");
		printf("用于分享和炫技，因为是解析型语言，所以像Python一样可以到处运行\n...\n");
		goto RETURN;
	}
	else if (!strcmp(buff, "learn")){
		printf("与BrainFuck的使用方式类似\nhttps://baike.baidu.com/item/Brainfuck/1152785?fr=ge_ala\n查看百度百科以学习BrainFuck\n");
		printf("bf++的使用方法类似，但是阉割了输入功能\n现在\":\"代表输出字符，\".\"是输出数字\n\n对于bf_main.exe，你需要在命令行运行，使用方法是bf_main.exe <需要运行的文件(此文件内写了bf++代码)> <给bf++的内存大小>\n我们已经准备了bf_hello_world.txt，里面的bf代码会输出Hello World!\n它至少要8个单位内存\n\n在未来的版本中会增加更多功能\n输入about了解功能前瞻\n");
		goto RETURN;
	}
	else if (!strcmp(buff, "reset")) {
		free(tape);
		init_BF(255);
		printf("重置了bf++的运行内存\n");
	}
	else if(!strcmp(buff, "check")) {
		printf("这是从工作指针到内存末尾的内存\n");
		for (int i=reading_pointer-tape;i+tape<reading_pointer+255;i++) {
			if (i+tape >= tape + 255) {
				printf("\n显示了%d个单位的内存\n", 255-(reading_pointer-tape));
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
	printf("BrainFuck++ V1.0.0\n\nBrainFuck++是BrainFuck语言的超集，是一门图灵完备的解析型语言，致力于增强BrainFuck的能力(以下简称bf++)\n");
	printf("输入learn学习使用bf++\n");
	printf("输入about了解我们\n输入check查看从bf++工作指针到工作内存之间的内存\n输入reset重置bf++的工作内存\n输入exit以退出\n如果输入不符合上述的任何一条，则视为bf++的代码运行\n");
	
	do {
	for (int i=0;i<255;i++)
		buff[i] = ' ';
	printf("\n>>>");
	scanf("%s", buff);
	
	} while(explain(buff));
	
	
	return 0;
}
