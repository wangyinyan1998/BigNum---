//
// Created by lenovo on 2018/6/3.
//

#ifndef OOPLAB4_OPERATIONS_H
#define OOPLAB4_OPERATIONS_H

#include "BigNum.h"
//这个类作为读取文件操作的 controller
class Operations {
public:
    void controller(const char* readName,const char* writeName);
    BigNum operation(BigNum first,BigNum second,char oper);
};


#endif //OOPLAB4_OPERATIONS_H
