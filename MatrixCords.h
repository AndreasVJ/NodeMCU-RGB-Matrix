// Returnerer koordinatet til et lys dersom koblingen er som på bildet under
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
int serpentine_xy(int x, int y){
  int pos;
  if(y%2 == 1) {
    int reverseX = (ROWS-1) - x;
    pos = (y * COLUMNS) + reverseX;
  } 
  else {
    pos = (y * COLUMNS) + x;
  }
  return pos;
}
