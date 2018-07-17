//
// Created by lenovo on 2018/6/3.
//
#include <iostream>
#include <fstream>
#include "Operations.h"
using namespace std;
/*读取文件，并将结果输入到文件中*/
void Operations::controller(const char* readName,const char* writeName){
    ifstream in(readName);
    ofstream out(writeName);
    string s;
    BigNum first;
    BigNum second;
    BigNum result;
    char oper;
    getline(in,s);
    int count =  stoi(s);
    int countNumber = 0;
    in >> s;
    while (countNumber<count) {
        first.add(s);
        in >> oper;
        in >> second;
        result = operation(first, second, oper);
        in >> s;
        while (s.length()==1){
            oper = s[0];
            in>>second;
            result = operation(result,second,oper);
            in >> s;
            if(in.eof())
                break;
        }
        out<<result<<endl;
        countNumber++;
        first.bigNumber.clear();
    }
    in.close();
    out.close();
}
/*处理运算*/
BigNum Operations::operation(BigNum first, BigNum second, char oper) {
    switch (oper){
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            return first / second;
    }
}