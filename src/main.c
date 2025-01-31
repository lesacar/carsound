#include <raylib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(1000, 540, "x86_64 raylib cars main window");
    InitAudioDevice();
	int geartops[] = {999,140,195,240,285,330};
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    bool window_close = false;

    // Wave wave_acc = LoadWave("res/acc.wav");
    Wave wave_acc = LoadWave("res/macc.wav");
    Sound snd_acc = LoadSoundFromWave(wave_acc);
	bool pause_sound = false;
    UnloadWave(wave_acc);

	float pitch = 0.7f;
	float speed = 0.0f;
	float idle_pitch = 0.7f;
	int gear = 1;
	SetRandomSeed(time(NULL));
    while (!window_close) {
        if (!IsSoundPlaying(snd_acc) && !pause_sound) {
            PlaySound(snd_acc);
        }


        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(2, 2);
        DrawText(TextFormat("%.3f", pitch), 2, 22, 18, WHITE);
        DrawText(TextFormat("%d", gear), 420, 220, 30, WHITE);
        DrawText(TextFormat("%.0f KMH", speed), 400, 250, 38, WHITE);
        EndDrawing();
		if (speed > 40.0f) {
			speed = speed + GetRandomValue(-10, 10)/40.0f;

		}
		if (IsKeyDown(KEY_W) && speed < geartops[gear]) {
			speed += (1.0f/gear)/2.0f;
		}
		if (!IsKeyDown(KEY_W) && speed > 0) {
			//speed -= (1.0f/gear)/4.0f;
			speed -= (speed/300.0f)/24.0f;
		}
		if (IsKeyDown(KEY_S)) {
			if (speed - (gear/1.75f) > 0.0f) {
				speed -= 0.7f;
			 } 
		}
		if (IsKeyPressed(KEY_E) && gear < 6) {
			gear++;
			speed-= 10.0f;
		} else if (IsKeyPressed(KEY_Q)) {
			if (gear >= 2) {
				gear--;
				speed-= 6.0f;
			}
		}

		if (gear == 1) {
			pitch = idle_pitch + speed/gear * 0.006;
		  } else if (gear == 2) {
			pitch = idle_pitch + speed/gear * 0.006; // TODO
		  }
		SetSoundPitch(snd_acc, pitch);

		if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_Q)) {
                window_close = true;
            }
        }
    }

    UnloadSound(snd_acc);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
