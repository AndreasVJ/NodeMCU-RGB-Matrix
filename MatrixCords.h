/* Returns a correct coordinate if the wiring is the same as below 
 *     0 >  1 >  2 >  3 >  4
 *                        |
 *                        |
 *    9 <  8 <  7 <  6 <  5
 *    |
 *    |
 *    10 > 11 > 12 > 13 > 14
 */
int serpentine_xy(int x, int y){
  int pos;
  if(y%2 == 1) {
    // Reverse row
    int reverseX = (ROWS-1) - x;
    pos = (y * COLUMNS) + reverseX;
  } 
  else {
    // Normal row
    pos = (y * COLUMNS) + x;
  }
  return pos;
}

// Found on https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
void rotateMatrix4(int matrix[][4]){
  int matrixSize = 4;
  // Consider all squares one by one
  for (int x = 0; x < matrixSize / 2; x++) {
    // Consider elements in group
    // of 4 in current square
    for (int y = x; y < matrixSize - x - 1; y++) {
      // Store current cell in temp variable
      int temp = matrix[x][y];

      // Move values from right to top
      matrix[x][y] = matrix[y][matrixSize - 1 - x];

      // Move values from bottom to right
      matrix[y][matrixSize - 1 - x] = matrix[matrixSize - 1 - x][matrixSize - 1 - y];

      // Move values from left to bottom
      matrix[matrixSize - 1 - x][matrixSize - 1 - y] = matrix[matrixSize - 1 - y][x];

      // Assign temp to left
      matrix[matrixSize - 1 - y][x] = temp;
    }
  }
}
