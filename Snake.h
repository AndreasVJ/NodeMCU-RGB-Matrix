// Oppdaterer listen med kommandoer for slangen.
// Hvert trykk blir lagret og deretter lest når bildet oppdaterer.
// Hensikten er at man ikke skal kunne endre retningen flere ganger før slangen flytter seg, 
// og på denne måten hoppe over kommandoer.
void updateMoves(int moveDirection,  int maxNumberOfMoves, int &numberOfMoves, int *moves) {
  if (numberOfMoves < maxNumberOfMoves and moveDirection != moves[numberOfMoves-1]) {
    moves[numberOfMoves] = moveDirection;
    numberOfMoves++;
  }
}

// Flytter en bit av slangen basert på verdien til bitens posisjon.
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


void playSnake(int numberOfRows, int numberOfColumns, int moveDelay, CRGB leds[]) {
  FastLED.clear();
  breakLoop = false;
  left = false;
  down = false;
  right = false;
  up = false;

  int grid[numberOfRows][numberOfColumns]; // Lager griden
  const int middleRow = round(numberOfRows/2); // Finner midten
  // Endrer alle verdiene i griden til 0. Dersom man ikke gjør dette vil den inneholde tilfeldige verdier
  for (int i = 0; i<numberOfRows; i++){
    for (int n = 0; n<numberOfColumns; n++) {
      grid[i][n] = 0;
    }
  }
  // Lager de fire første bitene av slangen
  for (int i = 1; i<5; i++) {
    grid[middleRow][i] = 2;
    leds[serpentine_xy(1+i, middleRow)].setRGB(0,255,0);
  }
  grid[middleRow][numberOfColumns-2] = 5; // Lager eplet

  int headGridPosition[] = {middleRow, 4};
  int tailGridPosition[] = {middleRow, 1};
  int headDirection = 2;
  int tailDirection = 2;
  int appleGridPosition[] = {middleRow, numberOfColumns-2};
  leds[serpentine_xy(appleGridPosition[1], appleGridPosition[0])].setRGB(255,0,0);
  bool apple = false;

  // Lager listen som skal inneholde kommandoer for å endre retningen på slangen
  const int maxNumberOfMoves = 6;
  int moves[maxNumberOfMoves+1];
  for (int i = 0; i<maxNumberOfMoves+1; i++) {
    moves[i] = 0;
  }
  int numberOfMoves = 0;

  unsigned long currentTime, previousTime = 0;
  int score = 0;
  bool gameOver = false;

  Serial.println("Game Started");
  // Printer spillet
  for (int i = 0; i<numberOfRows; i++){
        for (int n = 0; n<numberOfColumns; n++) {
          Serial.print("{");
          Serial.print(grid[i][n]);
          Serial.print("},");
        }
        Serial.println();
        Serial.println();
      }

  // Starter spill loopen
  while (breakLoop == false) {
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
    if (currentTime - previousTime > moveDelay) {
      previousTime = currentTime;
      Serial.println(previousTime);

      // Endrer retningen på slangen dersom "moves" listen ikke er tom
      if (numberOfMoves > 0) {
        headDirection = moves[0];
        for (int i = 0; i < numberOfMoves; i++) {
          moves[i] = moves[i+1];
        }
        grid[headGridPosition[0]][headGridPosition[1]] = headDirection;
        numberOfMoves--;
      }
      moveSnakePart(headGridPosition[0], headGridPosition[1], headDirection); // Flytter hodet basert på retningen

      // Sjekker om det er kollisjon med eplet
      if (grid[headGridPosition[0]][headGridPosition[1]] == 5) {
        score++;
        if (score == numberOfRows*numberOfColumns - 4) {
          Serial.println("You Win");
          breakLoop = true;
          gameOver = true;
        }
        apple = true;
      }
      // Sletter verdien i halens posisjon og flytter deretter halens posisjon.
      if (apple == false) { // Kjører bare dersom det ikke ble spist et eple. Dette gjør at slangen blir lengre
        tailDirection = grid[tailGridPosition[0]][tailGridPosition[1]];
        grid[tailGridPosition[0]][tailGridPosition[1]] = 0;
        leds[serpentine_xy(tailGridPosition[1], tailGridPosition[0])].setRGB(0,0,0);
        moveSnakePart(tailGridPosition[0], tailGridPosition[1], tailDirection);
      }
      // Gir en ny tilfeldig posisjon til eplet
      else {
        while (grid[appleGridPosition[0]][appleGridPosition[1]] != 0) {
          appleGridPosition[0] = random(numberOfRows);
          appleGridPosition[1] = random(numberOfColumns);
          Serial.print(appleGridPosition[0]);
          Serial.print("    ");
          Serial.println(appleGridPosition[1]);
        }
        grid[appleGridPosition[0]][appleGridPosition[1]] = 5;
        leds[serpentine_xy(appleGridPosition[1], appleGridPosition[0])].setRGB(255,0,0);
        apple = false;
      }
      // Sjekker kollisjon
      if (grid[headGridPosition[0]][headGridPosition[1]] != 0 and grid[headGridPosition[0]][headGridPosition[1]] != 5) {
        Serial.println("Game Over");
        //server.send(200, "text/html", mainMenuHTML());
        breakLoop = true;
          gameOver = true;
      }
      if (headGridPosition[0] > numberOfRows-1 or headGridPosition[1] > numberOfColumns-1 or
          headGridPosition[0] < 0 or headGridPosition[1] < 0) {
        Serial.println("Game Over");
        //server.send(200, "text/html", mainMenuHTML());
        breakLoop = true;
          gameOver = true;
      }
      grid[headGridPosition[0]][headGridPosition[1]] = headDirection;
      leds[serpentine_xy(headGridPosition[1], headGridPosition[0])].setRGB(0,255,0);
      for (int i = 0; i<numberOfRows; i++){
        for (int n = 0; n<numberOfColumns; n++) {
          Serial.print("{");
          Serial.print(grid[i][n]);
          Serial.print("},");
        }
        Serial.println();
        Serial.println();
      }
      FastLED.show();
    }
  }
  if (gameOver) {
    queue = "scrolling text";
    text = "Game Over";
  }
}
