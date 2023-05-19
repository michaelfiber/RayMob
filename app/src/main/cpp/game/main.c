#include "raylib.h"
#include "admob.h"

int main(void)
{
    InitWindow(0, 0, "AdMob for Raylib");
    SetTargetFPS(60);

    bool adRequested = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hey, well done handsome! Welcome to your app :D", 190, 200, 32, BLACK);

        if (adRequested)
        {
            if (IsInterstitialAdLoaded())
            {
                DrawText("The advertisement is loaded, tap again to display it!", 290, 400, 32, BLACK);
                if (IsGestureDetected(GESTURE_TAP))
                {
                    ShowInterstitialAd();
                    adRequested = false;
                }
            }
            else
            {
                DrawText("Wait until the advertising loads handsome ;)", 290, 400, 32, BLACK);
            }
        }
        else
        {
            DrawText("Tap to request an ad.", 290, 400, 32, BLACK);
            if (IsGestureDetected(GESTURE_TAP))
            {
                RequestInterstitialAd();
                adRequested = true;
            }
        }

        EndDrawing();
    }

    ReleaseNativeLoader();
    CloseWindow();

    return 0;
}