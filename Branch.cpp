#include<stdio.h>
#include<iostream>
using namespace std;
#include "Branch.h"

Branch::Branch(int id, string name) {
    this->id = id;
    this->name = name;
    customers = new Customer[1];
    numOfCustomers = 0;
}
Branch::Branch() {
    customers = new Customer[1];
    numOfCustomers = 0;
    this->id = 123;
    this->name = "dewbfj";
}
Branch::Branch(const Branch& obj) {
    customers = new Customer[max(1,obj.numOfCustomers)];
    this->id = obj.id;
    this->name = obj.name;
    this->numOfCustomers = obj.numOfCustomers;
    for (int i = 0; i < numOfCustomers; i++) {
        customers[i] = obj.customers[i];
    }
}
void Branch::operator=(const Branch& obj) {
    delete [] customers;

    customers = new Customer[max(1, obj.numOfCustomers)];
    this->id = obj.id;
    this->name = obj.name;
    this->numOfCustomers = obj.numOfCustomers;
    for (int i = 0; i < numOfCustomers; i++) {
        customers[i] = obj.customers[i];
    }
}
Branch::~Branch() {
    if (customers != nullptr) {
        delete[] customers;
    }
}
void Branch::addCustomer(Customer cust) {
    Customer* newCustomers = nullptr;
    bool find = false;
    for (int i = 0; i < numOfCustomers; i++) {
        if (customers[i].getId() == cust.getId()) {
            find = true;
        }
    }
    if (!find) {
        numOfCustomers++;
        newCustomers = new Customer[numOfCustomers];
        for (int i = 0; i < numOfCustomers-1; i++) {
            newCustomers[i] = customers[i];
        }
        delete[] customers;
        customers = newCustomers;
        newCustomers = nullptr;
        customers[numOfCustomers-1] = cust;
        
    }
   
    else {
        delete[] newCustomers;
    }
    


}
Customer* Branch::getCustomersPtr(int index) {
    return &customers[index];
}
int Branch::getId() {
    return id;
}
int Branch::getNumOfCustomers() {
    return numOfCustomers;
}
string Branch::getName() {
    return name;
}
void Branch::setId(int Id) {
    this->id = id;
}
void Branch::setName(string name) {
    this->name = name;
}