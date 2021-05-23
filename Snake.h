// Updates list containing commands for changing the direction. Commands will be queded and read when the frame updates
void updateMoves(int moveDirection,  int maxNumberOfMoves, int &numberOfMoves, int *moves) {
  if (numberOfMoves < maxNumberOfMoves and moveDirection != moves[numberOfMoves-1]) {
    moves[numberOfMoves] = moveDirection;
    numberOfMoves++;
  }
}

// Moves a part of the snake based on the value insdie it's coordinates
void moveSnakePart(int &gridColumnPosition, int &gridRowPosition, int snakePartDirection) {
  switch(snakePartDirection) {
    case 1:
      gridColumnPosition--;
      break;
    case 2:
      gridRowPosition++;
      break;
    case 3:
      gridColumnPosition++;
      break;
    case 4:
      gridRowPosition--;
      break;
  }
}


void playSnake() {
  FastLED.clear();
  breakLoop = false;
  left = false;
  down = false;
  right = false;
  up = false;

  int grid[ROWS][COLUMNS]; // Makes game grid
  const int middleRow = round(ROWS/2); // Finds the middle
  // Changes all grid values to 0
  for (int i = 0; i<ROWS; i++){
    for (int n = 0; n<COLUMNS; n++) {
      grid[i][n] = 0;
    }
  }
  // Adds four snake parts
  for (int i = 1; i<5; i++) {
    grid[middleRow][i] = 2;
    leds[serpentine_xy(1+i, middleRow)].setRGB(0,255,0);
  }
  grid[middleRow][COLUMNS-2] = 5; // Adds apple

  int headGridPosition[] = {middleRow, 4};
  int tailGridPosition[] = {middleRow, 1};
  int headDirection = 2;
  int tailDirection = 2;
  int appleGridPosition[] = {middleRow, COLUMNS-2};
  leds[serpentine_xy(appleGridPosition[1], appleGridPosition[0])].setRGB(255,0,0);
  bool apple = false;

  // Makes list containing commands for direction change
  const int maxNumberOfMoves = 6;
  int moves[maxNumberOfMoves+1];
  for (int i = 0; i<maxNumberOfMoves+1; i++) {
    moves[i] = 0;
  }
  int numberOfMoves = 0;

  unsigned long currentTime, previousTime = 0;
  int score = 0;
  bool gameOver = false;


  while (breakLoop == false) { // Starts game loop
    server.handleClient();
    if (left) {
      updateMoves(4, maxNumberOfMoves, numberOfMoves, moves);
      left = false;
    }
    if (down) {
    updateMoves(3, maxNumberOfMoves, numberOfMoves, moves);
    down = false;
    }
    if (right) {
    updateMoves(2, maxNumberOfMoves, numberOfMoves, moves);
    right = false;
    }
    if (up) {
    updateMoves(1, maxNumberOfMoves, numberOfMoves, moves);
    up = false;
    }

    currentTime = millis();
    if (currentTime - previousTime > 500) {
      previousTime = currentTime;

      // Changes direction
      if (numberOfMoves > 0) {
        headDirection = moves[0];
        for (int i = 0; i < numberOfMoves; i++) {
          moves[i] = moves[i+1];
        }
        grid[headGridPosition[0]][headGridPosition[1]] = headDirection;
        numberOfMoves--;
      }
      moveSnakePart(headGridPosition[0], headGridPosition[1], headDirection); // Moves head

      // Checks collision with apple
      if (grid[headGridPosition[0]][headGridPosition[1]] == 5) {
        score++;
        if (score == ROWS*COLUMNS - 4) {
          text = "You won";
          breakLoop = true;
          gameOver = true;
        }
        apple = true;
      }
      // Deletes the value inside the tail's position and turns of the led before moving the tail
      if (apple == false) { // Only runs when an apple has not been eaten. Eating an apple will therefore make the snake longer     
        tailDirection = grid[tailGridPosition[0]][tailGridPosition[1]];
        grid[tailGridPosition[0]][tailGridPosition[1]] = 0;
        leds[serpentine_xy(tailGridPosition[1], tailGridPosition[0])].setRGB(0,0,0);
        moveSnakePart(tailGridPosition[0], tailGridPosition[1], tailDirection);
      }
      // Gives a new random position to the apple
      else {
        while (grid[appleGridPosition[0]][appleGridPosition[1]] != 0) {
          appleGridPosition[0] = random(ROWS);
          appleGridPosition[1] = random(COLUMNS);
        }
        grid[appleGridPosition[0]][appleGridPosition[1]] = 5;
        leds[serpentine_xy(appleGridPosition[1], appleGridPosition[0])].setRGB(255,0,0);
        apple = false;
      }
      // Checks collision with it self
      if (grid[headGridPosition[0]][headGridPosition[1]] != 0 and grid[headGridPosition[0]][headGridPosition[1]] != 5) {
        breakLoop = true;
        gameOver = true;
        text = "Game Over";
      }
      // Checks collision with walls
      if (headGridPosition[0] > ROWS-1 or headGridPosition[1] > COLUMNS-1 or headGridPosition[0] < 0 or headGridPosition[1] < 0) {
        breakLoop = true;
        gameOver = true;
        text = "Game Over";
      }
      grid[headGridPosition[0]][headGridPosition[1]] = headDirection;
      leds[serpentine_xy(headGridPosition[1], headGridPosition[0])].setRGB(0,255,0);

      FastLED.show();
    }
  }
  // Sets scrolling text as next animation if game ended because of collision or max score
  if (gameOver) {
    queue = "Scrolling text";
  }
}
