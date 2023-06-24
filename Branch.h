#ifndef BRANCH_H
#define BRANCH_H
#include<stdio.h>
#include<iostream>
#include "Customer.h"
using namespace std;
class Branch {
private:
    int id;
    string name;
    int numOfCustomers;
    Customer* customers;

public:
    void setName(string name);
    void setId(int id);
    string getName();
    int getId();
    void operator=(const Branch& obj);
    int getNumOfCustomers();
    void addCustomer(Customer cust);
    Customer* getCustomersPtr(int index);
    Branch(int id, string name);
    Branch();
    Branch(const Branch& obj);
    ~Branch();

};
#endif // BRANCH_H
