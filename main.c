#include <limits.h>
#include <raylib.h>
#include <stdio.h>
#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)
#define screenWidth 800
#define screenHeight 600

int main(void) {

  Rectangle player1 = {0, 250, 20, 100};
  Rectangle player2 = {780, 250, 20, 100};
  Rectangle ball = {380, 280, 20, 20};
  float speed = 3.0f;

  float xChange = speed, yChange = speed / 2.0f;
  int score1 = 0, score2 = 0;

  InitWindow(screenWidth, screenHeight, "Pong");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_W) && !CheckCollisionPointRec((Vector2){0, 0}, player1)) {
      player1.y -= speed;
    }
    if (IsKeyDown(KEY_S) &&
        !CheckCollisionPointRec((Vector2){0, screenHeight}, player1)) {
      player1.y += speed;
    }

    if (IsKeyDown(KEY_UP) &&
        !CheckCollisionPointRec((Vector2){screenWidth - 1.0f, 0}, player2)) {
      player2.y -= speed;
    }
    if (IsKeyDown(KEY_DOWN) &&
        !CheckCollisionPointRec((Vector2){screenWidth - 1.0f, screenHeight},
                                player2)) {
      player2.y += speed;
    }

    ball.x += xChange;
    ball.y += yChange;

    if (CheckCollisionRecs(ball, player2) ||
        CheckCollisionRecs(ball, player1)) {
      xChange *= -1.0f;
      yChange *= -1.0f;
    } else if (ball.x >= (screenWidth)) {
      xChange *= -1.0f;
      score1++;
      speed += 0.1f;
      xChange += 0.1f;
      yChange += 0.1f;
    } else if (ball.x <= 0) {
      xChange *= -1.0f;
      score2++;
      speed += 0.1f;
      xChange += 0.1f;
      yChange += 0.1f;
    } else if ((ball.y >= (screenHeight)) || (ball.y <= 0)) {
      yChange *= -1.0f;
    }

    while (ball.x >= (screenWidth) || ball.x <= 0) {
      ball.x += xChange;
    }

    while ((ball.y >= (screenHeight)) || (ball.y <= 0)) {
      ball.y += yChange;
    }

    char scoreStr1[ENOUGH], scoreStr2[ENOUGH];
    sprintf(scoreStr1, "%d", score1);
    sprintf(scoreStr2, "%d", score2);

    DrawRectangleRec(player1, WHITE);
    DrawRectangleRec(player2, WHITE);
    DrawRectangleRec(ball, WHITE);
    DrawLine(screenWidth / 2.0f, 0, screenWidth / 2.0f, screenHeight, WHITE);
    DrawText(scoreStr1, 10.0f, 10.0f, 25, WHITE);
    DrawText(scoreStr2, screenWidth - MeasureText(scoreStr2, 25) - 10.0f, 10.0f,
             25, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
