#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int count = 0;
	int answer;
	int rnd = 1 + rand() % 99;
	printf("�����v�������ׂ鐔�𓖂Ă܂��傤�B\n");
	printf("���̐���1-99�̂����ꂩ�̐����ł��B\n");
	while (1)
	{
		printf("���̐��́H");
		scanf("%d", &answer);
		count++;
		if (rnd > answer)
			printf("�Ⴂ�܂��B������傫�Ȑ��ł��B\n");
		else if (rnd < answer)
			printf("�Ⴂ�܂��B�����菬���Ȑ��ł��B\n");
		else
		{
			printf("�����ł��B���Ȃ���%d��œ��Ă܂����B", count);
			break;
		}
	}
}