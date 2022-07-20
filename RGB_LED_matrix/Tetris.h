// Not finished

class Tetrimino {
  public:
    Tetrimino(int color, int shape[][4]);
    int rotate();
    int printShape();
    int _shape[][4];
  private:
    int _color;
    int _size = 4;
};


Tetrimino::Tetrimino(int color, int shape[][4]) {
  _color = color;
  for (int i = 0; i < _size; i++) {
    for (int n = 0; n < _size; n++) {
      _shape[i][n] = shape[i][n];
    }
  }
  printShape();
}


int Tetrimino::rotate() {
  rotateMatrix4(_shape);
  return 1;
}

int Tetrimino::printShape() {
  for (int i = 0; i<4; i++) {
    for (int n = 0; n<4; n++) {
      Serial.print(String(_shape[i][n]) + ", ");
    }
    Serial.println();
  }
  return 1;
}


void playTetris() {
  for (int i = 0; i < 4; i++) {
    //cyan.printShape();
    //cyan.rotate();
    Serial.println("");
  }

  int cyanShape[][4] = {{0, 0, 1, 0},
                        {0, 0, 1, 0},
                        {0, 0, 1, 0},
                        {0, 0, 1, 0}};
  Tetrimino cyan(0x00ffff, cyanShape);

  queue = "Snake";
  Serial.println("almost");
}
