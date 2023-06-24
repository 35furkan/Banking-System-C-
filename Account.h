#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<stdio.h>
#include<iostream>
using namespace std;
class Account {
private:
    int id;
    int branchId;
    double balance;


public:
    void setBalance(double balance);
    void setId(int id);
    double getBalance();
    int getId();
    int getBranchId();
    Account();
    Account(const int id, const double balance, const int branchId);

};
#endif // ACCOUNT_H
