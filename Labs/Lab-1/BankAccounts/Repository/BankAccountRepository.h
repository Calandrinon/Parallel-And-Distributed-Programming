//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
#define BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
#include "../Model/BankAccount.h"
#include "../Model/BankDetailsState.h"


class BankAccountRepository {
    private:
        std::vector<BankAccount*> container;
        BankDetailsState* bankDetailsState;

    public:
        BankAccountRepository();
        void save(BankAccount* account);
        BankDetailsState *getBankDetailsState() const;
        void setBankDetailsState(BankDetailsState *bankDetailsState);
        std::vector<BankAccount*> getContainer() const;
};


#endif //BANKACCOUNTS_BANKACCOUNTREPOSITORY_H
