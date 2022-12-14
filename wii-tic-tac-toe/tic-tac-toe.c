#include <grrlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define GRID_SIZE 200
#define OFFSET_X ((SCREEN_WIDTH - GRID_SIZE) / 2)
#define OFFSET_Y ((SCREEN_HEIGHT - GRID_SIZE) / 2)

#define CELL_SIZE (GRID_SIZE / 3)

typedef enum {
  NONE,
  X,
  O
} Player;

Player grid[3][3] = {{NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}};
Player currentPlayer = X;

void drawGrid() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int x1 = OFFSET_X + i * CELL_SIZE;
      int y1 = OFFSET_Y + j * CELL_SIZE;
      int x2 = x1 + CELL_SIZE;
      int y2 = y1 + CELL_SIZE;
      GRRLIB_Line(x1, y1, x2, y1, 0xffffffff);
      GRRLIB_Line(x2, y1, x2, y2, 0xffffffff);
      GRRLIB_Line(x2, y2, x1, y2, 0xffffffff);
      GRRLIB_Line(x1, y2, x1, y1, 0xffffffff);
    }
  }
}

void drawX(int x, int y) {
  int x1 = OFFSET_X + x * CELL_SIZE + 5;
  int y1 = OFFSET_Y + y * CELL_SIZE + 5;
  int x2 = x1 + CELL_SIZE - 10;
  int y2 = y1 + CELL_SIZE - 10;
  GRRLIB_Line(x1, y1, x2, y2, 0xffffffff);
  GRRLIB_Line(x2, y1, x1, y2, 0xffffffff);
}

void drawO(int x, int y) {
  int x1 = OFFSET_X + x * CELL_SIZE + CELL_SIZE / 2;
  int y1 = OFFSET_Y + y * CELL_SIZE + CELL_SIZE / 2;
  GRRLIB_Circle(x1, y1, CELL_SIZE / 2 - 5, 20, 0xffffffff);
}

void drawPlayer(int x, int y, Player player) {
  if (player == X) {
    drawX(x, y);
  } else if (player == O) {
    drawO(x, y);
  }
}

void draw() {
  drawGrid();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      drawPlayer(i, j, grid[i][j]);
    }
  }
}

bool checkWin() {
  // check rows
  for (int i = 0; i < 3; i++) {
    if (grid[i][0] != NONE && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
      return true;
    }
  }

  // check columns
  for (int i = 0; i < 3; i++) {
    if (grid[0][i] != NONE && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
      return true;
    }
  }

  // check diagonal
  if (grid[0][0] != NONE && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
    return true;
  }
  if (grid[0][2] != NONE && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
    return true;
  }

  return false;
}

bool checkDraw() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[i][j] == NONE) {
        return false;
      }
    }
  }
  return true;
}

void handleInput() {
  WPAD_ScanPads();
  u32 pressed = WPAD_ButtonsDown(0);

  if (pressed & WPAD_BUTTON_LEFT) {
    int x = (int)((wpad->ir.x - OFFSET_X) / CELL_SIZE);
    int y = (int)((wpad->ir.y - OFFSET_Y) / CELL_SIZE);
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && grid[x][y] == NONE) {
      grid[x][y] = currentPlayer;
      if (currentPlayer == X) {
        currentPlayer = O;
      } else {
        currentPlayer = X;
      }
    }
  }
}

int main() {
  GRRLIB_Init();
  WPAD_Init();

  while(true) {
    WPAD_ScanPads();
    u32 pressed = WPAD_ButtonsDown(0);

    handleInput();
    draw();

    if (checkWin()) {
      GRRLIB_Printf(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10, 0xffffffff, 1, "Player %d wins!", currentPlayer);
      break;
    }
    if (checkDraw()) {
  GRRLIB_Printf(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10, 0xffffffff, 1, "It's a draw!");
  break;
}

if (pressed & WPAD_BUTTON_HOME) {
  break;
}

GRRLIB_Render();
}

GRRLIB_Exit();
return 0;
}
