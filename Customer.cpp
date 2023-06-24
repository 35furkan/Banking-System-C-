#include<stdio.h>
#include<iostream>
using namespace std;
#include "Customer.h"
Customer::Customer(int id, string name) {
    this->id = id;
    this->name = name;
    accounts = new Account[1];
    numOfAccounts = 0;
}
Customer::Customer() {
    accounts = new Account[1];
    numOfAccounts = 0;
}
Customer::Customer(const Customer& obj) {
    this->id = obj.id;
    this->name = obj.name;
    this->numOfAccounts = obj.numOfAccounts;
    accounts = new Account[max(1, obj.numOfAccounts)];
    for (int i = 0; i < numOfAccounts; i++) {
        accounts[i] = obj.accounts[i];
   }
}
Customer::~Customer() {
    
    if (accounts != nullptr) {
        delete[] accounts;
    }
    
}
void Customer::operator=(Customer& obj) {
    
    delete[] accounts;
    accounts = new Account[max(1, obj.numOfAccounts)];
    this->id = obj.id;
    this->name = obj.name;
    this->numOfAccounts = obj.numOfAccounts;
    for (int i = 0; i < numOfAccounts; i++) {
        accounts[i] = obj.accounts[i];
    }
}
void Customer::addNewAccount(const int branchId, const int accountID, const double amount) {
    Account* newAccounts = nullptr;
    if (numOfAccounts >= 0) {
        numOfAccounts++;
        newAccounts = new Account[numOfAccounts];
        for (int i = 0; i < numOfAccounts-1; i++) {
            newAccounts[i] = accounts[i];
        }
        delete[] accounts;
        accounts = newAccounts;
        newAccounts = nullptr;
        Account newAccount(accountID, amount, branchId);
        accounts[numOfAccounts-1] = newAccount;
        
    }
    else {
        
    }
    
}
void Customer::deleteAllAccounts() {
    if (accounts != nullptr) {
        delete[] accounts;
        accounts = nullptr;
        numOfAccounts = 0;
    }
}
void Customer::deleteAnAccount(const int accountId) {
    Account* newAccounts = nullptr;
    bool found = false;
    if (numOfAccounts == 0) {
        cout << "Account " << accountId << " does not exist" << endl;
    }
    else {
        newAccounts = new Account[max(1,numOfAccounts-1)];
        for (int k = 0; k < numOfAccounts; k++) {
            if (accounts[k].getId() == accountId) {
                found = true;
                int index = k;
                if (found) {
                    for (int i = 0; i < index; i++) {
                        newAccounts[i] = accounts[i];
                    }
                    for (int i = index + 1; i < numOfAccounts; i++) {
                        newAccounts[i - 1] = accounts[i];
                    }
                    delete[] accounts;
                    accounts = newAccounts;
                    newAccounts = nullptr;
                    numOfAccounts--;
                }
                

                break;
            }

        }
    }
    
    
    if (!found && numOfAccounts!=0) {
        cout << "Account " << accountId<< " does not exist" << endl;
        delete[] newAccounts;
    }
   
   
}
void  Customer::setName(string name) {
    this->name = name;
}
void Customer::setId(int id) {
    this->id = id;
}
string Customer::getName() {
    return name;
}
int Customer::getId() {
    return id;
}
int Customer::getNumOfAccounts() {
    return numOfAccounts;
}
Account* Customer::getAccountPtr(int index) {
    Account* accountPtr = &accounts[index];
    return accountPtr;
}