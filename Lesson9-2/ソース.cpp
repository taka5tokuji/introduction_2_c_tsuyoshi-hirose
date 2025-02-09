#define _USE_MATH_DEFINES
#include "Dxlib.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const int WIDTH = 960, HEIGHT = 640;
    const int GRAY = GetColor(128, 128, 128);

    SetWindowText("三角関数を用いたエフェクト");
    SetGraphMode(WIDTH, HEIGHT, 32);
    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) return -1;
    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK);

    const int RADIUS = 300;
    int degree = 0;

    while (1)
    {
        ClearDrawScreen();


        DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, GRAY);
        DrawLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, GRAY);
        DrawLine(WIDTH / 2, HEIGHT / 2, RADIUS, GRAY, FALSE);

        degree++;
        double radian = M_PI * degree / 180;
        DrawFormatString(0, 0, GRAY, "degree = %d", degree);
        DrawFormatString(0, 20, GRAY, "radian = %f", radian);
        for (int i = 0; i <= 180; i += 30)
        {
            int x = WIDTH / 2 + RADIUS * cos(M_PI * (degree + i) / 180);
            int y = HEIGHT / 2 + RADIUS * sin(M_PI * (degree + i) / 180);
            DrawCircle(x, y, 20, GetColor(0, 255, 255), TRUE);
        }


        int x = RADIUS * cos(radian);
        int y = RADIUS * sin(radian);
        int cx = x + WIDTH / 2;
        int cy = y + HEIGHT / 2;
        DrawBox(cx - 10, cy - 10, cx + 10, cy + 10, GetColor(0, 255, 255), TRUE);

        ScreenFlip();
        WaitTimer(16);
        if (ProcessMessage() == -1) break;
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
    }

    DxLib_End();
    return 0;
}
