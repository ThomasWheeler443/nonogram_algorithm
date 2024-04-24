#ifndef CHAR_BUFF_H
#define CHAR_BUFF_H

#include "NonogramGrid.h"

class CharBuffer {
  private:
    int rowW;
    int colH;
    int width;
    int height;
    int lCharLength;
    int rCharLength;
    char ***buffer;
    NonogramGrid *nonogram;

  public:
    CharBuffer(NonogramGrid *grid);
    void update();
    void print();
};

#endif