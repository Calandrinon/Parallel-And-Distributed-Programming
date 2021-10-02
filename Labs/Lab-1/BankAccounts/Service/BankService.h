//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKSERVICE_H
#define BANKACCOUNTS_BANKSERVICE_H

#include "../Repository/BankAccountRepository.h"

class BankService {
    private:
        BankAccountRepository* repository;

    public:
        BankService(BankAccountRepository* repository);
        void createAccount(std::string ownerName);
        void transferMoney(BankAccount* transferer, BankAccount* transferee, double amount);
        ~BankService();
};


#endif //BANKACCOUNTS_BANKSERVICE_H
