#include <iostream>
#include<stdio.h>

using namespace std;
#include "BankingSystem.h"

BankingSystem::BankingSystem()
{
    branches = new Branch[1];
    customers = new Customer[1];
    numOfCustomers = 0;
    numOfBranches = 0;
}
BankingSystem::~BankingSystem() {
  delete[] branches;
  delete[] customers;
}
void BankingSystem::addBranch(const int branchId, const string branchName)
{
    
    if (numOfBranches == 0)
    {
        Branch newBranch(branchId, branchName);
        branches[0] = newBranch;
        numOfBranches++;
        cout << "Branch " << branchId << " has been added" << endl;
    }
    else
    {
        bool found = false;
        for (int i = 0; i < numOfBranches; i++)
        {
            if (branches[i].getId() == branchId)
            {

                found = true;
            }
        }
        if (found == true) {
            cout << "Branch " << branchId << " already exists" << endl;
        }
        if (!found) {
            Branch* newBranches = new Branch[numOfBranches+1];
            for (int i = 0; i < numOfBranches; i++)
            {
                newBranches[i] = branches[i];
            }
            delete[] branches;
            branches = newBranches;
            newBranches = nullptr;

            numOfBranches++;
            Branch newBranch(branchId, branchName);
            branches[numOfBranches-1] = newBranch;
            cout << "Branch " << branchId << " has been added" << endl;
        }
            
           
        
    }

}

void BankingSystem::deleteBranch(const int branchId)
{
    Branch* newBranches = nullptr;
    if (numOfBranches == 0) {
        cout << "Branch " << branchId << " does not exist" << endl;
    }
    else {
         newBranches = new Branch[max(1,numOfBranches-1)];
    }
    
    bool found = false;
    if (numOfBranches > 0)
    {
        for (int i = 0; i < numOfBranches && !found; i++)
        {
            
            if (branches[i].getId() == branchId)
            {   
                found = true;
                int index = i;
                for (int k = 0; k < numOfCustomers; k++) {
                    for (int i = 0; i < customers[k].getNumOfAccounts(); i++) {
                        if (customers[k].getAccountPtr(i)->getBranchId() == branchId) {
                            customers[k].deleteAnAccount(customers[k].getAccountPtr(i)->getId());
                            i--;
                        }
                    }
                    
                }

                for (int k = 0; k < index; k++)
                {       
                    
                    newBranches[k] = branches[k];
                }
                for (int k = index+1; k < numOfBranches; k++)
                {

                    newBranches[k-1] = branches[k];
                }
                delete[] branches;
                branches = newBranches;
                newBranches = nullptr;
               

                numOfBranches--;
               
                cout << "Branch " << branchId << " has been deleted" << endl;
            }
            
        }

    }
    if (!found && numOfBranches > 0) {
   
    
     cout << "Branch " << branchId << " does not exist" << endl;
     delete[] newBranches;
        
    
    }
}

void BankingSystem::addCustomer(const int customerId, const string customerName)
{
    if (numOfCustomers == 0)
    {
        Customer newCustomer(customerId, customerName);
        customers[0] = newCustomer;
        numOfCustomers++;
        cout << "Customer " << customerId << " has been added" << endl;
    }
    else
    {
        bool found = false;
        for (int i = 0; i < numOfCustomers; i++)
        {
            if (customers[i].getId() == customerId)
            {
                cout << "Customer " << customerId << " already exists" << endl;
                found = true;
                break;
            }
        }
        if (found == false) {
            Customer newCustomer(customerId, customerName);
            numOfCustomers++;
            Customer* newCustomers = new Customer[numOfCustomers];
            for (int i = 0; i < numOfCustomers-1; i++)
            {
                newCustomers[i] = customers[i];
            }
            delete[] customers;
            customers = newCustomers;
            newCustomers = nullptr;
            customers[numOfCustomers - 1] = newCustomer;
            cout << "Customer " << customerId << " has been added" << endl;
        }
            
            
        
        
    }
    
}

void BankingSystem::deleteCustomer(const int customerId) {
    Customer* newCustomers = nullptr;
    if (numOfCustomers == 0) {
        cout << "Customer " << customerId << " does not exist" << endl;
    }
    else {
        newCustomers = new Customer[max(1, numOfCustomers - 1)];
    }
    Customer* customerPtr = nullptr;
    bool found = false;
    for (int i = 0; i < numOfCustomers; i++)
    {
        if (customers[i].getId() == customerId)
        {
            found = true;
            customerPtr = &customers[i];
        }

    }
    if (!found&& numOfCustomers>0) {
       
        cout << "Customer " << customerId << " does not exist" << endl;
        delete[] newCustomers;
       

    }
    else {
        if (numOfCustomers > 0)
        {
            for (int i = 0; i < numOfCustomers; i++)
            {
                if (customers[i].getId() == customerId)
                {  
                    int index = i;

                    for (int k=0; k < index; k++)
                    {
                        newCustomers[k] = customers[k];
                    }
                    for (int k = index+1; k < numOfCustomers; k++)
                    {
                        newCustomers[k-1] = customers[k];
                    }

                    numOfCustomers--;
                    customerPtr->deleteAllAccounts();
                    delete[] customers;
                    customers = newCustomers;
                    newCustomers = nullptr;
                    cout << "Customer " << customerId << " has been deleted" << endl;


                }

            }
        }
    }
}
int BankingSystem::addAccount(const int branchId, const int customerId, const double amount) {
    static int uniqueAccountNumber = 0;
    Customer* customerPtr = nullptr;
    Branch* branchPtr = nullptr;
    for (int i = 0; i < numOfBranches; i++) {
        if (branches[i].getId() == branchId) {
            branchPtr = &branches[i];
            break;
        }
    }
    for (int k = 0; k < numOfCustomers; k++) {
        if (customers[k].getId() == customerId) {
            customerPtr = &customers[k];
            break;
        }
    }
    if (branchPtr == nullptr) {
        cout << "Branch " << branchId << " does not exist" << endl;
        return -1;

    }
    else if (customerPtr == nullptr) {
        cout << "Customer " << customerId << " does not exist" << endl;
        return -1;

    }

    if (branchPtr != nullptr && customerPtr != nullptr) {
        uniqueAccountNumber++;
        customerPtr->addNewAccount(branchId, uniqueAccountNumber, amount);
        branchPtr->addCustomer(*customerPtr);
        cout << "Account " << uniqueAccountNumber << " added for customer " << customerId << " at branch " << branchId << endl;
        

    }
    return uniqueAccountNumber;
    
}
void BankingSystem::deleteAccount(const int accountId) {
    bool found = false;
    
    for (int i = 0; i < numOfCustomers; i++)
    {
        
        
        for (int k = 0; k < customers[i].getNumOfAccounts(); k++)
        {   
          
                                                                                                       
            if (customers[i].getAccountPtr(k)->getId() == accountId) {
                
                found = true;
                customers[i].deleteAnAccount(accountId);
                cout << "Account " << accountId << " has been deleted" << endl;

            }
          

        }

    }
    if (!found) {
        cout << "Account " << accountId << " does not exist" << endl;

    }
}
/*void BankingSystem::showAllAccounts() {
    cout << "Account id" << " " << "Branch id" << " " << "Branch name" << " " << "Customer id" << " " << "Customer name" << " " << "Balance" << endl;
   
    /*bool found = false;
    for (int i = 0; i < numOfCustomers; i++) {
        for (int k = 0; k < customers[i].getNumOfAccounts(); k++) {
           
            int accountId = 0;
            int branchId = 0;
            string branchName;
            int customerId = 0;
            string customerName;
            double balance = 0;
          
            for (int f = 0; f < numOfBranches; f++) {
                if (customers[i].getAccountPtr(k)->getBranchId() == branches[f].getId()) {
                    found = true;
                    branchId = branches[f].getId();
                    branchName = branches[f].getName();
                    accountId = customers[i].getAccountPtr(k)->getId();
                    customerId = customers[i].getId();
                    customerName = customers[i].getName();
                    balance = customers[i].getAccountPtr(k)->getBalance();
                    cout << accountId << " " << branchId << " " << branchName << " " << customerId << " " << customerName << " " << fixed << setprecision(2) << balance << endl;
                }
            }

        }

    }
}*/
void BankingSystem::showAllAccounts() {
    cout << "Account id" << " " << "Branch id" << " " << "Branch name" << " " << "Customer id" << " " << "Customer name" << " " << "Balance" << endl;
    int totalAccountNumber = 0;
    for (int i = 0; i < numOfCustomers; i++) {
        totalAccountNumber += customers[i].getNumOfAccounts();
    }
    Account* orderedAccounts = new Account[totalAccountNumber];
    int index = 0;
    for (int i = 0; i < numOfCustomers; i++) {
        for (int j = 0; j < customers[i].getNumOfAccounts(); j++) {

            orderedAccounts[index++] = *(customers[i].getAccountPtr(j));
        }
    }
   
    for (int i = 0; i < totalAccountNumber; i++) {
        for (int j = 0; j < totalAccountNumber - i - 1; j++) {
            if (orderedAccounts[j].getId() > orderedAccounts[j + 1].getId()) {
                Account temp = orderedAccounts[j];

                orderedAccounts[j] = orderedAccounts[j + 1];
                orderedAccounts[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < totalAccountNumber; i++) {
        int accountId = orderedAccounts[i].getId();
        int branchId = orderedAccounts[i].getBranchId();

        double balance = orderedAccounts[i].getBalance();
        string branchName, customerName;
        int customerId = 0;
        for (int j = 0; j < numOfBranches; j++) {
            if (branchId == branches[j].getId()) {

                branchName = branches[j].getName();
                break;
            }
        }
        for (int j = 0; j < numOfCustomers; j++) {
            for (int k = 0; k < customers[j].getNumOfAccounts(); k++) {

                if (accountId == customers[j].getAccountPtr(k)->getId()) {
                    customerId = customers[j].getId();

                    customerName = customers[j].getName();
                    break;
                }
            }
            if (customerId != 0) {
                break;
            }
        }
        cout << accountId << " " << branchId << " " << branchName << " " << customerId << " " << customerName << " " << fixed << setprecision(2) << balance << endl;
    }
    delete[] orderedAccounts;
}

void BankingSystem::showBranch(const int branchId) {
    Account* accounts = new Account[1];
    Customer* customersOfBranch = new Customer[1];
    int noOfAccounts = 0;
    Branch* branchPtr = nullptr;
    bool found = false;
    for (int k = 0; k < numOfBranches; k++) {
        if (branches[k].getId() == branchId) {
            branchPtr = &branches[k];
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Branch " << branchId << " does not exist" << endl;
    }
    if (found) {
        string branchName = branchPtr->getName();
        int BranchId = branchPtr->getId();
        for (int k = 0; k < numOfCustomers; k++) {
            for (int i = 0; i < customers[k].getNumOfAccounts(); i++) {
                if (customers[k].getAccountPtr(i)->getBranchId() == branchId) {
                    noOfAccounts++;
                    Account* newAccounts = new Account[noOfAccounts];
                    Customer* newCustomersOfBranch = new Customer[noOfAccounts];
                    for (int i = 0; i < noOfAccounts - 1; i++) {
                        newAccounts[i] = accounts[i];
                        newCustomersOfBranch[i] = customersOfBranch[i];
                    }
                    delete[] accounts;
                    delete[] customersOfBranch;
                    accounts = newAccounts;
                    customersOfBranch = newCustomersOfBranch;
                    accounts[noOfAccounts - 1] = *(customers[k].getAccountPtr(i));
                    customersOfBranch[noOfAccounts - 1] = customers[k];
                }
            }

        }
        cout << "Branch id: " << BranchId << " " << "Branch name: " << branchName << " " << "Number of accounts: " << noOfAccounts << endl;
        if (noOfAccounts > 0) {
            cout << "Accounts at this branch:" << endl;
            cout << "Account id" << " " << "Customer id" << " " << "Customer name" << " " << "Balance" << endl;
            for (int m = 0; m < noOfAccounts; m++) {
                cout << accounts[m].getId() << " " << customersOfBranch[m].getId() << " " << customersOfBranch[m].getName() << " " << accounts[m].getBalance() << endl;
            }
        }
       
    }
    
    
    delete[] accounts;
    delete[] customersOfBranch;
}
void BankingSystem::showCustomer(const int customerId) {
    bool found = false;
    Customer* customerPtr = nullptr;
    int accountId, branchId;
    double balance;
    string branchName;
    
    for (int i = 0; i < numOfCustomers; i++) {
        if (customers[i].getId() == customerId) {
            found = true;
            customerPtr = &customers[i];
            break;
        }
    }
    if (customerPtr != nullptr) {
        cout << "Customer id: " << customerPtr->getId() << " " << "Customer name: " << customerPtr->getName() << " " << "Number of accounts: " << customerPtr->getNumOfAccounts() << endl;
        if (customerPtr->getNumOfAccounts()>0){
        cout << "Accounts of this customer:" << endl;
        cout << "Account id" << " " << "Branch id" << " " << "Branch name" << " " << "Balance" << endl;
        for (int k = 0; k < customerPtr->getNumOfAccounts(); k++) {
            Account* accountPtr = customerPtr->getAccountPtr(k);
            accountId = accountPtr->getId();
            branchId = accountPtr->getBranchId();
            balance = accountPtr->getBalance();
            for (int i = 0; i < numOfBranches; i++) {
                if (accountPtr->getBranchId() == branches[i].getId()) {
                    branchName = branches[i].getName();
                }
            }
            cout << accountId << " " << branchId << " " << branchName << " " << fixed << setprecision(2) <<balance << endl;
        }
        }
    }
    if (!found) {
        cout << "Customer " << customerId << " does not exist" << endl;
    }
}