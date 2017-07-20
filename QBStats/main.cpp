/**
  * @brief Assignment 9
  * @author Corey Hemphill
  */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#include "qbfunctions.h"

int main()
{
    Quarterback qbList[NUM_QBS];

    readQbs(qbList, "QBInfo.txt");

    getQbMenu(qbList);

    return 0;
}
