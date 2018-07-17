//
// Created by lenovo on 2018/6/2.
//

#ifndef OOPLAB4_BIGNUM_H
#define OOPLAB4_BIGNUM_H
#include<vector>
#include <string>
#include <fstream>
#include <iostream>
class BigNum {
    void add(int num);
    void change(std::vector<int>& small,std::vector<int>& big,std::vector<int> a,std::vector<int> b);
    BigNum deleteZero(BigNum* result);
public:
    std::vector <int> bigNumber;
    BigNum(){};
    void add(std::string s);
    BigNum(std::string s);
    BigNum operator+(const BigNum& a);
    BigNum operator-(const BigNum& a);
    BigNum operator*(const BigNum& a);
    BigNum operator/(const BigNum& a);
    bool operator<=(const BigNum& a);
    bool operator>(const BigNum& a);
    std::string toString() const ;
    friend std::ostream& operator<<(std::ostream& os, BigNum& bigNum);
    friend std::istream &operator>>(std::istream  &input, BigNum &bigNum);
};


#endif //OOPLAB4_BIGNUM_H
