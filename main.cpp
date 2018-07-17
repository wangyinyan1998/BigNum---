#include <iostream>
#include <fstream>
#include "BigNum.h"
#include "Operations.h"
using namespace std;

int main(int argc,char* argv[]) {
    Operations operations;
    operations.controller(argv[1],argv[2]);
   // operations.controller("sample.in","result.txt");
    return 0;
}
