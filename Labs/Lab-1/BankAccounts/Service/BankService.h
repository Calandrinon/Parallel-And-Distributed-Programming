//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKSERVICE_H
#define BANKACCOUNTS_BANKSERVICE_H

#include "../Repository/BankAccountRepository.h"

class BankService {
    private:
        BankAccountRepository* repository;
        std::mutex operationMutex;

    public:
        BankService(BankAccountRepository* repository);
        BankAccount* createAccount(std::string ownerName);
        void transferMoney(BankAccount* transferer, BankAccount* transferee, double amount);
        std::vector<BankAccount*> getAccounts();
        std::mutex getOperationMutex();
        ~BankService();
};


#endif //BANKACCOUNTS_BANKSERVICE_H
