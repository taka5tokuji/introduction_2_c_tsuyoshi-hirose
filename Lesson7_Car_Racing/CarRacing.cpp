#include "DxLib.h"
#include <stdlib.h>

enum { RED, YELLOW, BLUE, TRUCK };
const int CAR_MAX = 4;
int imgCar[CAR_MAX];
const int CAR_W[CAR_MAX] = { 32,26,26,40 };
const int CAR_H[CAR_MAX] = { 48,48,48,100 }; 

void drawCar(int x, int y, int type)
{
	DrawGraph(x - CAR_W[type] / 2, y - CAR_H[type] / 2, imgCar[type], TRUE);
}

void drawText(int x, int y, int col, const char* txt, int val, int siz)
{
	SetFontSize(siz);
	DrawFormatString(x + 2, y + 2, 0x000000, txt, val);
	DrawFormatString(x, y, col, txt, val);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const int WIDTH = 720, HEIGHT = 640;

	SetWindowText("�J�[���[�X");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == 1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int bgY = 0;
	int imgBG = LoadGraph("C:/Users/takak/Downloads/501766 - sample/Chapter7/image/bg.png");

	imgCar[RED] = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter7/image/car_red.png");
	imgCar[YELLOW] = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter7/image/car_yellow.png");
	imgCar[BLUE] = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter7/image/car_blue.png");
	imgCar[TRUCK] = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter7/image/truck.png");

	int playerX = WIDTH / 2;
	int playerY = HEIGHT / 2;
	int playerType = RED;

	const int COM_MAX = 8;
	int computerX[COM_MAX], computerY[COM_MAX], computerType[COM_MAX], computerFlag[COM_MAX];
	for (int i = 0; i < COM_MAX; i++)
	{
		computerX[i] = rand() % 180 + 270;
		computerY[i] = -100;
		computerType[i] = YELLOW + rand() % 3;
		computerFlag[i] = 0;
	}

	int score = 0;
	int highScore = 5000;

	int fuel = 0;
	int fuelX = WIDTH / 2;
	int fuelY = 0;
	int imgFuel = LoadGraph("C:/Users/takak/Downloads/501766-sample/Chapter7/image/fuel.png");

	enum { TITLE, PLAY, OVER };
	int scene = TITLE;
	int timer = 0;

	/*int bgm = LoadSoundMem("sound/bgm.mp3");*/
	int bgm = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter7/sound/bgm.mp3");
	int jin = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter7/sound/gameover.mp3");
	int seFuel = LoadSoundMem("C:/Users/takak/Downloads/501766-sample/Chapter7/sound/fuel.mp3");
	int seCrash = LoadSoundMem("C:/Users/takak/Downloads/501766 - sample/Chapter7/sound/crash.mp3");
	ChangeVolumeSoundMem(128, bgm);
	ChangeVolumeSoundMem(128, jin);

	while (1)
	{
		ClearDrawScreen();

		if (scene == PLAY) bgY = (bgY + 10) % HEIGHT;
		DrawGraph(0, bgY - HEIGHT, imgBG, FALSE);
		DrawGraph(0, bgY, imgBG, FALSE);

		if (scene == PLAY)
		{
			GetMousePoint(&playerX, &playerY);
			if (playerX < 260) playerX = 260;
			if (playerX > 460) playerX = 460;
			if (playerY < 40) playerX = 40;
			if (playerY > 600) playerY = 600;
		}
		drawCar(playerX, playerY, playerType);

		for (int i = 0; i < COM_MAX; i++)
		{
			if (scene == PLAY)
			{
				computerY[i] = computerY[i] + 1 + i;
				if (computerY[i] > HEIGHT + 100)
				{
					computerX[i] = rand() % 180 + 270;
					computerY[i] = -100;
					computerType[i] = YELLOW + rand() % 3;
					computerFlag[i] = 0;
				}
				int dx = abs(computerX[i] - playerX);
				int dy = abs(computerY[i] - playerY);
				int wid = CAR_W[playerType] / 2 + CAR_W[computerType[i]] / 2 - 4;
				int hei = CAR_H[playerType] / 2 + CAR_H[computerType[i]] / 2 - 4;
				if (dx < wid && dy < hei)
				{
					int col = GetColor(rand() % 256, rand() % 256, rand() % 256);
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
					DrawBox(playerX - CAR_W[playerType] / 2, playerY - CAR_H[playerType] / 2, playerX + CAR_W[playerType] / 2, playerY + CAR_H[playerType] / 2, col, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					PlaySoundMem(seCrash, DX_PLAYTYPE_BACK);
					fuel -= 10;
				}

				if (computerY[i] > playerY && computerFlag[i] == 0)
				{
					computerFlag[i] = 1;
					score += 100;
					if (score > highScore) highScore = score;
				}
			}
			else
			{
				computerY[i] = computerY[i] - 1 - i;
				if (computerY[i] < -100)computerY[i] = HEIGHT + 100;
			}
			drawCar(computerX[i], computerY[i], computerType[i]);
		}

		if (scene == PLAY)
		{
			fuelY += 4;
			if (fuelY > HEIGHT) fuelY = -100;
			if (abs(fuelX - playerX) < CAR_W[playerType] / 2 + 12 && abs(fuelY - playerY) < CAR_H[playerType] / 2 + 12)
			{
				fuelX = rand() % 180 + 270;
				fuelY = -500;
				fuel += 200;
				PlaySoundMem(seFuel, DX_PLAYTYPE_BACK);
			}
			DrawGraph(fuelX - 12, fuelY - 12, imgFuel, TRUE);
		}

		timer++;
		switch (scene)
		{
		case TITLE:
			drawText(160, 160, 0xffffff, "Car Race", 0, 100);
			if (timer % 60 < 30) drawText(210, 400, 0x00ff00, "Click to start.", 0, 40);
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				playerX = WIDTH / 2;
				playerY = HEIGHT / 2;
				for (int i = 0; i < COM_MAX; i++)
				{
					computerY[i] = HEIGHT + 100;
					computerFlag[i] = 0;
				}
				fuelX = WIDTH / 2;
				fuelY = -100;
				score = 0;
				fuel = 1000;
				scene = PLAY;
				PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			}
			break;

		case PLAY:
			fuel -= 1;
			if (fuel < 0)
			{
				fuel = 0;
				scene = OVER;
				timer = 0;
				StopSoundMem(bgm);
				PlaySoundMem(jin, DX_PLAYTYPE_BACK);
			}
			break;

		case OVER:
			drawText(180, 240, 0xff0000, "GAME OVER", 0, 80);
			if (timer > 60 * 5) scene = TITLE;
			break;
		}

		drawText(10, 10, 0x00ffff, "SCORE %d", score, 30);
		drawText(WIDTH - 200, 10, 0xffff00, "HI-SC %d", highScore, 30);
		int col = 0x00ff00;
		if (fuel < 400) col = 0xffc000;
		if (fuel < 200) col = 0xff0000;
		drawText(10, HEIGHT - 40, col, "FULL %d", fuel, 30);

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;

}

	