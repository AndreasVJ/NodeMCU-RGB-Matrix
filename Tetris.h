#include "Buttons.h"

/*
class Tetrimino {
  public:
    Tetrimino(int shape[]);
};


Tetrimino::Tetrimino(int shape[]) {
  for (int i = 0; i<3; i++) {
    Serial.println(shape[i]);
  }
}
*/

void playTetris(Button leftButton, Button downButton, Button rightButton, Button upButton, int numberOfRows, int numberOfColumns) {
  int grid[numberOfRows][numberOfColumns];
  for (int i = 0; i<numberOfRows; i++) {
    for (int n = 0; n<numberOfColumns; n++) {
      grid[i][n] = 0;
    }
  }
  int pieces[7][4][4][2] = {{{{0, 3}, {1, 3}, {1, 4}, {1, 5}}, {{0, 4}, {0, 5}, {1, 4}, {2, 4}},
                             {{1, 3}, {1, 4}, {1, 5}, {2, 5}}, {{0, 4}, {1, 4}, {2, 3}, {2, 4}}},
                             
                            {{{1, 3}, {1, 4}, {1, 5}, {1, 6}}, {{0, 5}, {1, 5}, {2, 5}, {3, 5}},
                             {{2, 3}, {2, 4}, {2, 5}, {2, 6}}, {{0, 4}, {1, 4}, {2, 4}, {3, 4}}},
                             
                            {{{0, 4}, {0, 5}, {1, 3}, {1, 4}}, {{0, 4}, {1, 4}, {1, 5}, {2, 5}},
                             {{1, 4}, {1, 5}, {2, 3}, {2, 4}}, {{0, 3}, {1, 3}, {1, 4}, {2, 4}}},
                             
                            {{{0, 5}, {1, 3}, {1, 4}, {1, 5}}, {{0, 4}, {1, 4}, {2, 4}, {2, 5}},
                             {{1, 3}, {1, 4}, {1, 5}, {2, 3}}, {{0, 3}, {0, 4}, {1, 4}, {2, 4}}},
                             
                            {{{0, 4}, {1, 3}, {1, 4}, {1, 5}}, {{0, 4}, {1, 4}, {1, 5}, {2, 4}},
                             {{1, 3}, {1, 4}, {1, 5}, {2, 4}}, {{0, 4}, {1, 3}, {1, 4}, {2, 4}}},
                             
                            {{{0, 3}, {0, 4}, {1, 4}, {1, 5}}, {{0, 4}, {1, 3}, {1, 4}, {2, 3}},
                             {{1, 3}, {1, 4}, {2, 4}, {2, 5}}, {{0, 5}, {1, 4}, {1, 5}, {2, 4}}},
                             
                            {{{0, 4}, {0, 5}, {1, 4}, {1, 5}}, {{0, 4}, {0, 5}, {1, 4}, {1, 5}},
                             {{0, 4}, {0, 5}, {1, 4}, {1, 5}}, {{0, 4}, {0, 5}, {1, 4}, {1, 5}}}};

/*
  int count;
  int time1 = millis();
  Serial.println(floor(8/3));
  int time2 = millis();
  Serial.println(time2-time1);
  time1 = millis();
  for (int i = 3; i<8; i+=3) {
    count++;
  }
  Serial.println(count);
  time2 = millis();
  Serial.println(time2-time1);
*/
  //Tetrimino blue({0, 1, 0});

  for (int i = 0; i<numberOfRows; i++){
    for (int n = 0; n<numberOfColumns; n++) {
      Serial.print("{");
      Serial.print(grid[i][n]);
      Serial.print("},");
    }
    Serial.println();
    Serial.println();
  }
}
