#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main(void)
{
	char QUIZ[5][101] =
	{
		"2020�N�ɔ�������A�q�b�g����Nintendo Swich�̃Q�[��[�Z�Z�Z�Z�ǂ��Ԃ̐X]�B�Z�Z�Z�Z�ɓ��錾�t�́H",
		"2010�N��ɃX�}�[�g�t�H���Ńq�b�g�����\�[�V�����Q�[��[�p�Y�h��]�̐������̂́H",
		"2000�N��ɃK���P�[�Ńq�b�g�����A���]�Ԃɏ�����_�l�Ԃ𑀍삵�ėV�ԃQ�[���̖��̂́H",
		"1990�N��ɃQ�[���Z���^�[�ɐݒu����A�u�[���ƂȂ����ʐ^�V�[���@[�v���N��]�̐������̂́H",
		"1980�N��ɑ�q�b�g�����ƒ�p�Q�[���@[�t�@�~�R��]�̐������̂́H"
	};
	char ANS[5][23] =
	{
		"���܂�",
		"�p�Y��&�h���S���Y",
		"�`������",
		"�v�����g�N���u",
		"�t�@�~���[�R���s���[�^"
	};
	int score = 0;
	char ans[31];
	for (int i = 0; i < 5; i++)
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
			printf("�ԈႢ�ł��B�����������́A%s\n", ANS[i]);
		}
	}
	printf("���Ȃ���%d��A�������܂����B", score);
}