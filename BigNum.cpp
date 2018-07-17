//
// Created by lenovo on 2018/6/2.
//
#include "strings.h"
#include "BigNum.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//构造函数，其中个位数在第0位上，越高位其位置越靠前，这样可以在运算的时候保持一致性
BigNum::BigNum(string s) {
    int length = s.length();
    for (int i = length - 1; i >= 0; i--) {
        if (s[i] < '0' || s[i] > '9') {
            bigNumber.clear();
            break;
        }
        bigNumber.push_back(s[i] - '0');
    }
}
//向bigNum中加入一个高位
void BigNum::add(int num) {
    bigNumber.push_back(num);
}
//将传入的a b vector按照长度大小顺序 返回
void BigNum::change(vector<int> &small, vector<int> &big, vector<int> a, vector<int> b) {
    int aLength = a.size();
    int bLength = b.size();
    if (aLength > bLength) {
        big = a;
        small = b;
    } else {
        big = b;
        small = a;
    }
}
//将BigNum顺序化，返回string，因为高位在高位置，所以需要倒序遍历
string BigNum::toString() const {
    string s="";
    for (int i = bigNumber.size() - 1; i >= 0; i--) {
        s += to_string(bigNumber.at(i));
    }
    return s;
}
/**加法，加法的实现需要先将两个vector按照长度大小顺序排列，然后按照小的size进行对两组数据的一一对应相加，
 * 如果相加的超过10，则进位（即addLeave=1），然后在下次加的时候将进位addLeave加上，如果无进位，则设置addLeave=0.
 * 然后再将长度大的一个vector剩余的部分加到最后的结果上，需要注意的是，addLeave如果为1，则加到剩余的部分中，
 * 此时仍然要考虑进位的问题
 */
BigNum BigNum::operator+(const BigNum &a) {
    vector<int> smallVector;
    vector<int> bigVector;
    change(smallVector, bigVector, bigNumber, a.bigNumber);
    int smallLength = smallVector.size();
    BigNum *result = new BigNum();
    int addLeave = 0;
    int i;
    int add;
    /*做加法的时候先选择小的size作为循环，然后两个数一一对应相加，如果有进位则将addLeave记为1，并在下次循环计算的时候加上；否则就将addLeave记为0*/
    for (i = 0; i < smallLength; i++) {
        add = smallVector.at(i) + bigVector.at(i) + addLeave;
        if (add > 9) {
            result->add(add - 10);
            addLeave = 1;
        } else {
            result->add(add);
            addLeave = 0;
        }
    }
    /*长度大的vector的多余部分不能进行一一对应的加，还要判断以前相加的addLeave是否为0来进行最后的进位*/
    while (addLeave > 0 || i <bigVector.size()) {
        if(i==bigVector.size()){
            result->add(addLeave);
            break;
        }
        add = bigVector.at(i) + addLeave;
        if (add > 9) {
            result->add(add-10);
            addLeave = 1;
        } else {
            result->add(add);
            addLeave = 0;
        }
        i++;
    }
    return deleteZero(result);
}
/**
 * 去掉开头可能存在的0(如果结果是0除外)
 */
BigNum BigNum::deleteZero(BigNum *result) {
    for(int k=result->bigNumber.size()-1;k>=0;k--){
        if(result->bigNumber.size()==1)
            return *result;
        if(result->bigNumber.at(k)==0)
            result->bigNumber.pop_back();
        else
            return *result;
    }
}
/**
 * 减法：首先进行一一对应相减，如果有借位，那么需要将subLeave设为 1，并在高位中减去。
 * 在对应相减完成后，需要将被减数的剩余部分加到结果中，此时如果subLeave=1，则应该考虑相减借位的问题。
 * 另外，减法会有最终结果高位出现0的问题，这是因为咋=在上两个步骤中，循环会将对应相减得到0加入result中，
 * 因此需要将高位的0 pop出来
 * @param a
 * @return
 */
BigNum BigNum::operator-(const BigNum &a) {
    BigNum *result = new BigNum();
    int i;
    int subtrahend;
    int subLeave = 0;
    //一一对应相减，如果不够的，让subLeave=1，相当于向高位借1
    for (i = 0; i < a.bigNumber.size(); i++) {
        subtrahend = bigNumber.at(i) - a.bigNumber.at(i) - subLeave;
        if (subtrahend < 0) {
            subLeave = 1;
            result->add(subtrahend + 10);
        } else {
            subLeave = 0;
            result->add(subtrahend);
        }
    }
    /*长度大的vector的多余部分不能进行一一对应的减，还要判断以前相减的subLeave是否为0来进行借位*/
    while (subLeave > 0 || i < bigNumber.size()) {
        if(i==bigNumber.size()){
            result->add(-1);
            break;
        }
        subtrahend = bigNumber.at(i) - subLeave;
        if (i == bigNumber.size() - 1 && subtrahend!=0) {
            result->add(subtrahend);
            subLeave = 0;
        }
        else if (subtrahend < 0) {
            result->add(subtrahend + 10);
            subLeave = 1;
        } else if(!(i == bigNumber.size()-1 && subtrahend==0)){
            result->add(subtrahend);
            subLeave = 0;
        }
        i++;
    }
//去掉开头可能存在的0(如果结果是0除外)
    return deleteZero(result);
}
//向高位加一个string
void BigNum::add(string s) {
    int length = s.length();
    if(length==0)
        return;
    for (int i = length - 1; i >= 0; i--) {
        if (s[i] < '0' || s[i] > '9') {
            bigNumber.clear();
            break;
        }
        bigNumber.push_back(s[i] - '0');
    }
}
/**
 * 乘法操作，使用向高位加0进行BigNum的加法计算，从而达到相乘的目的
 * @param a
 * @return
 */
BigNum BigNum::operator*(const BigNum &a) {
    int aLength = a.bigNumber.size();
    int bLength = bigNumber.size();
    int i,j;
    BigNum result;
    int multiply;
    for(i=0;i<aLength;i++){
        multiply = a.bigNumber.at(i)*bigNumber.at(0);
        BigNum tmpMultiply1;
        tmpMultiply1.add(to_string(multiply));
        for(j=1;j<bLength;j++){
            BigNum tmpMultiply2;
            BigNum tmpMultiply3;
            for(int k=0;k<j;k++){
                tmpMultiply2.add(0);
            }
            multiply = a.bigNumber.at(i) * bigNumber.at(j);
            tmpMultiply2.add(to_string(multiply));
            tmpMultiply3 = tmpMultiply1+tmpMultiply2;
            tmpMultiply1 = tmpMultiply3;
        }
        BigNum tmpMultiply10;
        BigNum tmpMultiply20;
        for(int k=0;k<i;k++){
            tmpMultiply10.add(0);
        }
        tmpMultiply10.add(tmpMultiply1.toString());
        tmpMultiply20 = result+tmpMultiply10;
        result = tmpMultiply20;
    }
    return deleteZero(&result);
}
/**
 * 实现了<=  >两个比较 运算符的运算，主要在除法操作中判断使用
 * @param a
 * @return
 */
bool BigNum::operator<=(const BigNum &a) {
    if(bigNumber.size()>a.bigNumber.size())
        return false;
    if(bigNumber.size()<a.bigNumber.size())
        return true;
    for(int i=bigNumber.size()-1;i>=0;i--){
        if(bigNumber.at(i)<a.bigNumber.at(i))
            return true;
        if(bigNumber.at(i)>a.bigNumber.at(i))
            return false;
    }
    return true;
}
bool BigNum::operator>(const BigNum &a) {
    if(bigNumber.size()>a.bigNumber.size())
        return true;
    if(bigNumber.size()<a.bigNumber.size())
        return false;
    for(int i=bigNumber.size()-1;i>=0;i--){
        if(bigNumber.at(i)<a.bigNumber.at(i))
            return false;
        if(bigNumber.at(i)>a.bigNumber.at(i))
            return true;
    }
    return false;
}
/**
 * 除法操作，使用乘法、减法、加法、以及判断来实现
 * @param bigNum
 * @return
 */
BigNum BigNum::operator/(const BigNum &bigNum) {
    int bLength = bigNum.bigNumber.size();
    int aLength = bigNumber.size();
    string bstring = bigNum.toString();
    string astring = toString();
    string resultString="" ;
    if(aLength < bLength)
        return BigNum("0");
    string tmp = astring.substr(0,bLength);
    BigNum tmpBigNum(tmp);
    for(int j=bLength;j<=aLength;j++) {
        for (int i = 0; i <= 9; i++) {
            BigNum tmpBefore;
            tmpBefore.add(i);
            BigNum tmpAfter;
            tmpAfter.add((i + 1));
            if (tmpBefore * bigNum <= tmpBigNum && tmpAfter * bigNum > tmpBigNum) {
                resultString += to_string(i);
                tmpBigNum = tmpBigNum - (tmpBefore * bigNum);
                break;
            }
        }
        if(j==aLength)
           break;
        BigNum tmp2;
        tmp2.add(toString()[j]-'0');
        tmp2.add(tmpBigNum.toString());
        tmpBigNum = tmp2;
    }
    BigNum result(resultString);
    //去掉开头可能存在的0(如果结果是0除外)
    return deleteZero(&result);
}
/**
 * 两个输入输出运算作为友元出现在这个类中。
 * @param os
 * @param bigNum
 * @return
 */
ostream& operator<<(ostream& os, BigNum& bigNum)
{
    os<<bigNum.toString();
    return os;
}
istream &operator>>( istream  &input, BigNum &bigNum )
{
    string s;
    if(s.length()>40) {
        cout <<"您输入的数字已经超过40位，无法进行读入。"<<endl;
        return input;
    }
    input >> s;
    bigNum.bigNumber.clear();
    bigNum.add(s);
    return input;
}