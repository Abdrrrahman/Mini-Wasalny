#include <raylib.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Graphs");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Hello, Alia!", WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20, 20,
             BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}