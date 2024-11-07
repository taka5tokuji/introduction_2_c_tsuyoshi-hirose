#include "DxLib.h"
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const int WIDTH = 960, HEIGHT = 640;

	SetWindowText("�e�j�X�Q�[��");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == 1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int ballX = 40;
	int ballY = 80;
	int ballVx = 5;
	int ballVy = 5;
	int ballR = 10;

	int racketX = WIDTH / 2;
	int racketY = HEIGHT - 50;
	int racketW = 120;
	int racketH = 12;

	enum { TITLE, PLAY, OVER };
	int scene = TITLE;
	int timer = 0;
	int score = 0;
	int highScore = 1000;
	int dx, dy;

	int imgBg = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter6/image/bg.png");

	int bgm = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter6/sound/bgm.mp3");
	int jin = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter6/sound/gameover.mp3");
	int se = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter6/sound/hit.mp3");
	ChangeVolumeSoundMem(128, bgm);
	ChangeVolumeSoundMem(128,jin);

	while (1)
	{
		ClearDrawScreen();
		DrawGraph(0, 0, imgBg, FALSE);
		timer++;

		switch (scene)
		{
		case TITLE:
			SetFontSize(50);
			DrawString(WIDTH / 2 - 50 / 2 * 12 / 2, HEIGHT / 3, "Tennis Game", 0x00ff00);
			if (timer % 60 < 30) {
				SetFontSize(30);
				DrawString(WIDTH / 2 - 30 / 2 * 21 / 2, HEIGHT * 2 / 3, "Press SPACE to start.", 0x00ffff);
			}
			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				ballX = 40;
				ballY = 80;
				ballVx = 5;
				ballVy = 5;
				racketX = WIDTH / 2;
				racketY = HEIGHT - 50;
				score = 0;
				scene = PLAY;
				PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			}
			break;
		case PLAY:
			ballX = ballX + ballVx;
			if (ballX < ballR && ballVx < 0)ballVx = -ballVx;
			if (ballX > WIDTH - ballR && ballVx > 0)ballVx = -ballVx;
			ballY = ballY + ballVy;
			if (ballY < ballR && ballVy < 0)ballVy = -ballVy;
			if (ballY > HEIGHT)
			{
				scene = OVER;
				timer = 0;
				StopSoundMem(bgm);
				PlaySoundMem(jin, DX_PLAYTYPE_BACK);
				break;
			}
			DrawCircle(ballX, ballY, ballR, 0xff0000, TRUE);
			DrawCircle(ballX - ballR / 4, ballY - ballR / 4, ballR / 2, 0xffa0a0, TRUE);
			DrawCircle(ballX - ballR / 4, ballY - ballR / 4, ballR / 4, 0xffffff, TRUE);

			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				racketX = racketX - 10;
				if (racketX < racketW / 2) racketX = racketW / 2;
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				racketX = racketX + 10;
				if (racketX > WIDTH - racketW / 2)racketX = WIDTH - racketW / 2;
			}
			DrawBox(racketX - racketW / 2 - 2, racketY - racketH / 2 - 2, racketX + racketW / 2, racketY + racketH / 2, 0x40c0ff, TRUE);
			DrawBox(racketX - racketW / 2, racketY - racketH / 2, racketX + racketW / 2 + 2, racketY + racketH / 2 + 2, 0x204080, TRUE);
			DrawBox(racketX - racketW / 2, racketY - racketH / 2, racketX + racketW / 2, racketY + racketH / 2, 0x0080ff, TRUE);

			dx = ballX - racketX;
			dy = ballY - racketY;
			if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0)
			{
				ballVy = -5 - rand() % 5;
				score = score + 100;
				if (score > highScore) highScore = score;
				PlaySoundMem(se, DX_PLAYTYPE_BACK);
			}
			break;

		case OVER:
			SetFontSize(40);
			DrawString(WIDTH / 2 - 40 / 2 * 9 / 2, HEIGHT / 3, "GAME OVER", 0xff0000);
			if (timer > 60 * 5) scene = TITLE;
			break;
		}


		ballX = ballX + ballVx;
		if (ballX < ballR && ballVx < 0)ballVx = -ballVx;
		if (ballX > WIDTH - ballR && ballVx > 0) ballVx = -ballVx;
		ballY = ballY + ballVy;
		if (ballY < ballR && ballVy < 0) ballVy = -ballVy;
		if (ballY > HEIGHT && ballVy > 0) ballVy = -ballVy;
		DrawCircle(ballX, ballY, ballR, 0xff0000, TRUE);

		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			racketX = racketX - 10;
			if (racketX < racketW / 2) racketX = racketW / 2;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			racketX = racketX + 10;
			if (racketX > WIDTH - racketW / 2) racketX = WIDTH - racketW / 2;

		}
		DrawBox(racketX - racketW / 2, racketY - racketH / 2, racketX + racketW / 2, racketY + racketH / 2, 0x0080ff, TRUE);

		int dx = ballX - racketX;
		int dy = ballY - racketY;
		if (-racketW / 2 - 10 < dx && dx < racketW / 2 + 10 && -20 < dy && dy < 0)
		{
			ballVy = -5 - rand() % 5;
			score = score + 100;
			if (score > highScore) highScore = score;
		}

		SetFontSize(30);
		DrawFormatString(10, 10, 0xffffff, "SCORE %d", score);
		DrawFormatString(WIDTH - 200, 10, 0xffff00, "HI-SC %d", highScore);

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

	}

	DxLib_End();
	return 0;
}