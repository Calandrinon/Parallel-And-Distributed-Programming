//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKSERVICE_H
#define BANKACCOUNTS_BANKSERVICE_H

#include "../Repository/BankAccountRepository.h"
#include <thread>
#include <random>

class BankService {
    private:
        BankAccountRepository* repository;
        std::mutex operationMutex;
        std::vector<std::thread> threads;
        std::default_random_engine randomEngine;

public:
        BankService(BankAccountRepository* repository);
        BankAccount* createAccount(std::string ownerName, double balance);
        void transferMoney(BankAccount* transferer, BankAccount* transferee, double amount);
        std::vector<BankAccount*> getAccounts();
        void createRandomAccounts(int quantity);
        void createRandomMultithreadedOperations(int numberOfThreads);
        BankAccount* pickRandomAccount();
        double getTotalAccountsBalance();
        std::string generateRandomString(int length);
        void generateRandomOperations();
        ~BankService();
};


#endif //BANKACCOUNTS_BANKSERVICE_H
