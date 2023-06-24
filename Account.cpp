#include <stdio.h>
#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(const int id, const double balance, const int branchId) {
    this->id = id;
    this->balance = balance;
    this->branchId = branchId;
}
Account::Account() {
    id = -1;
    balance = -1;
    branchId = -1;

}
void Account::setBalance(double balance)
{
    this->balance = balance;
}
void Account::setId(int id)
{
    this->id = id;
}
double Account::getBalance()
{
    return balance;
}
int Account::getId()
{
    return id;
}
int Account::getBranchId()
{
    return branchId;
}