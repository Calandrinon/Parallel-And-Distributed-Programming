//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
#define BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
#include "Repository.h"
#include "../Model/BankAccount.h"
#include "../Model/BankDetailsState.h"

class BankAccountRepository: Repository<BankAccount*> {
    private:
        BankDetailsState* bankDetailsState;

    public:
        void save(BankAccount* account);

        BankDetailsState *getBankDetailsState() const;

        void setBankDetailsState(BankDetailsState *bankDetailsState);
};


#endif //BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
