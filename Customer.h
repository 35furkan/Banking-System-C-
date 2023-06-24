#ifndef CUSTOMER_H
#define CUSTOMER_H
#include<stdio.h>
#include<iostream>
#include "Account.h"
using namespace std;
class Customer {
private:
    int id;
    string name;
    Account* accounts;
    int numOfAccounts;

public:
    void setName(string name);
    void setId(int id);
    string getName();
    Customer(const Customer& obj);
    void operator=(Customer& obj);
    int getId();
    int getNumOfAccounts();
    Account* getAccountPtr(int index);
    void addNewAccount(const int branchId, const int accountID, const double amount);
    void deleteAnAccount(const int accountId);
    void deleteAllAccounts();
    Customer(int id, string name);
    Customer();
    ~Customer();


};
#endif // CUSTOMER_Hagma once
