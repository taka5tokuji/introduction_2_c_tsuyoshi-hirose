#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main(void)
{
	char QUIZ[3][100] = {
		"�����X�^�[�{�[���𓊂��ă����X�^�[��߂܂���Q�[���̃^�C�g���́H",
		"�X�}�[�g�t�H���Ńq�b�g�����A�����X�^�[�����������Ĕ�΂��Q�[���́H",
		"[DQ]�͂���L���ȃQ�[���̃^�C�g���̗���B���̃Q�[���̐������̂́H",
	};
	char ANS[3][30] = {
		"�|�P�b�g�����X�^�[",
		"�����X�^�[�X�g���C�N",
		"�h���S���N�G�X�g"
	};
	int score = 0;
	char ans[30];
	printf("�N�C�Y�̓�������͂��AENTER�������Ă��������B\n");
	for (int i = 0; i < 3; i++)
	{
		printf("%s\n", QUIZ[i]);
		scanf("%s", ans);
		if (strcmp(ans, ANS[i]) == 0)
		{
			printf("�����ł��B\n");
			score = score + 1;
		}
		else
		{
			printf("�ԈႢ�ł��B������������%s\n", ANS[i]);
		}
	}
	printf("���Ȃ���%d��A�������܂����B", score);
}