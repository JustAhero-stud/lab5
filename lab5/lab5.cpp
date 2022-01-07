#include <iostream>
#include "Header.h"
#include <iomanip>

int main()
{
    Num num;
    ifstream* input = new ifstream("input.txt");
    num.input(*input);
    num.FindMax();
    num.FindMin();
}
