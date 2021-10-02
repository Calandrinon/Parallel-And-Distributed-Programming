//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKACCOUNT_H
#define BANKACCOUNTS_BANKACCOUNT_H
#include "OperationLog.h"

class BankAccount {
    private:
        int id;
        double balance;
        OperationLog* operationLog;
        std::string owner;
        std::time_t creationDate;

    public:
        BankAccount(std::string owner);
        double getBalance();
        void setBalance(double balance);
        ~BankAccount();
        OperationLog* getOperationLog() const;
        void setOperationLog(OperationLog *operationLog);
        const std::string &getOwner() const;
        void setOwner(const std::string &owner);
        time_t getCreationDate() const;
        void setCreationDate(time_t creationDate);
        int getId();
        void setId(int id);
};


#endif //BANKACCOUNTS_BANKACCOUNT_H
