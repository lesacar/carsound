#include <raylib.h>
#include <stdio.h>

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(1000, 540, "x86_64 raylib cars main window");
	InitAudioDevice();
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);
	bool window_close = false;


	//Wave wave_acc = LoadWave("res/acc.wav");
	Wave wave_acc = LoadWave("res/macc.wav");
Sound snd_acc = LoadSoundFromWave(wave_acc);
float pitch = 1.0f;
float idle_pitch = 0.7f;
int gear = 1;
const int max_gear = 6;
const int min_gear = 1;
const float max_pitch = 1.4f;
const float min_pitch = 0.1f;
const float pitch_step = 0.003f;
const float idle_return_step = 0.001f;
UnloadWave(wave_acc);

while (!window_close) {
    if (!IsSoundPlaying(snd_acc)) {
        PlaySound(snd_acc);
    }

    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(2, 2);
    DrawText(TextFormat("%.3f", pitch), 2, 22, 18, WHITE);
    DrawText(TextFormat("%d", gear), 420, 220, 30, WHITE);
    float kmh = ((pitch - idle_pitch) * 120 ) * gear;
    DrawText(TextFormat("%.0f KMH", kmh), 400, 250, 38, WHITE);
    EndDrawing();

    if (IsKeyPressed(KEY_E) && gear < max_gear) {
        gear++;
        pitch = idle_pitch + ((pitch - idle_pitch) / 2); // Consistent factor for upshifting
    }
    if (IsKeyPressed(KEY_Q) && gear > min_gear) {
        gear--;
        pitch = idle_pitch + ((pitch - idle_pitch) * 2); // Consistent factor for downshifting
        if (pitch > max_pitch) pitch = max_pitch;
    }
    if (IsKeyDown(KEY_W)) {
        pitch += pitch_step;
    }
    if (IsKeyDown(KEY_S)) {
        pitch -= pitch_step;
    } else {
        if (pitch < idle_pitch) {
            pitch += idle_return_step;
        } else if (pitch > idle_pitch) {
            pitch -= idle_return_step;
        }
    }
    if (pitch < min_pitch) {
        pitch = min_pitch;
    } else if (pitch > max_pitch) {
        pitch = max_pitch;
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
