#include "Dxlib.h"
#include <stdlib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	const int WIDTH = 1200, HEIGHT = 720;

	SetWindowText("3Dシューティングゲーム");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	int timer = 0;

	int mdl[4] =
	{
		MV1LoadModel("model/fighter.mqoz"),
		MV1LoadModel("model/missile.mqoz"),
		MV1LoadModel("model/object0.mqoz"),
		MV1LoadModel("model/object1.mqoz")
	};


	float playerX = 0.0f, playerY = 0.0f, playerZ = 0.0f;
	int playerZa = 0;
	int spcBk = 0;


	const int MISSILE_MAX = 20;
	float missileX[MISSILE_MAX], missileY[MISSILE_MAX], missileZ[MISSILE_MAX];
	int missileFlg[MISSILE_MAX];
	for (int i = 0; i < MISSILE_MAX; i++) missileFlg[i] = 0;


	const int ENEMY_MAX = 10;
	float enemyX[ENEMY_MAX], enemyY[ENEMY_MAX], enemyZ[ENEMY_MAX];
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemyX[i] = -300.0f + rand() % 600;
		enemyY[i] = -200.0f + rand() % 400;
		enemyZ[i] = 10000.0f;
	}

	ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.5f));

	VECTOR camPos = VGet(0, 100, -600);
	VECTOR camTar = VGet(0, 0, 1000);
	SetCameraPositionAndTarget_UpVecY(camPos, camTar);

	while (1)
	{
		ClearDrawScreen();

		timer++;
		DrawFormatString(0, 0, GetColor(255, 255, 0), "%d", timer);


		for (int n = 0; n < 20; n++) {
			float bz = 800.0f * n - (timer % 20) * 40;
			int c = (30 - n) * 6;
			DrawLine3D(VGet(-400.0f, -240.0f, bz), VGet(400.0f, -240.0f, bz), GetColor(c, c, c));
		}


		if (CheckHitKey(KEY_INPUT_UP) && playerY < 200) playerY += 8;
		if (CheckHitKey(KEY_INPUT_DOWN) && playerY > -200) playerY -= 8;
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			if (playerX > -300) playerX -= 12;
			if (playerZa < 30) playerZa += 10;
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT)) {
			if (playerX < 300) playerX += 12;
			if (playerZa > -30) playerZa -= 10;
		}
		else  {
			playerZa /= 2;
		}
		MV1SetRotationXYZ(mdl[0], VGet(0.0f, 0.0f, 3.1416 * playerZa / 180));
		MV1SetPosition(mdl[0], VGet(playerX, playerY, playerZ));
		MV1DrawModel(mdl[0]);


		if (CheckHitKey(KEY_INPUT_SPACE) && spcBk == 0) {
			for (int i = 0; i < MISSILE_MAX; i++) {
				if (missileFlg[i] == 1) continue;
				missileX[i] = playerX;
				missileY[i] = playerY;
				missileZ[i] = playerZ + 100;
				missileFlg[i] = 1;
				break;
			}
		}
		spcBk = CheckHitKey(KEY_INPUT_SPACE);
		for (int i = 0; i < MISSILE_MAX; i++) {
			if (missileFlg[i] == 0) continue;
			missileZ[i] += 200;
			MV1SetPosition(mdl[1], VGet(missileX[i], missileY[i], missileZ[i]));
			MV1DrawModel(mdl[1]);
			if (missileZ[i] > 10000) missileFlg[i] = 0;
		}


		for (int i = 0; i < ENEMY_MAX; i++) {
			enemyZ[i] = enemyZ[i] - 10 - i * 2;
			if (enemyZ[i] < -200) enemyZ[i] = 10000;
			int mn = 2 + i % 2;
			MV1SetPosition(mdl[mn], VGet(enemyX[i], enemyY[i], enemyZ[i]));
			MV1DrawModel(mdl[mn]);
			for (int j = 0; j < MISSILE_MAX; j++) {
				if (missileFlg[j] == 0) continue;
				int dx = abs((int)(enemyX[i] - missileX[j]));
				int dy = abs((int)(enemyY[i] - missileX[j]));
				int dz = abs((int)(enemyZ[i] - missileZ[j]));
				if (dx < 100 && dy < 100 && dz < 120) {
					enemyZ[i] = -200;
					missileFlg[j] = 0;
				}
			}
		}

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}