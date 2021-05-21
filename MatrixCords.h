/* Returns a correct coordinate if the wiring is the same as on the picture below 
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
