//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKDETAILSSTATE_H
#define BANKACCOUNTS_BANKDETAILSSTATE_H


#include <mutex>

class BankDetailsState {
    private:
        int transactionSerialNumber, accountSerialNumber;

    public:
        BankDetailsState();
        ~BankDetailsState();
        int getTransactionSerialNumber() const;
        void setTransactionSerialNumber(int transactionSerialNumber);
        void incrementTransactionSerialNumber();
        int getAccountSerialNumber() const;
        void setAccountSerialNumber(int accountSerialNumber);
};


#endif //BANKACCOUNTS_BANKDETAILSSTATE_H
