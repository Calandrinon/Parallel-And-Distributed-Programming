//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_BANKDETAILSSTATE_H
#define BANKACCOUNTS_BANKDETAILSSTATE_H


class BankDetailsState {
    private:
        int transactionSerialNumber;

    public:
        BankDetailsState();

        ~BankDetailsState();

        int getTransactionSerialNumber() const;

        void setTransactionSerialNumber(int transactionSerialNumber);

        void incrementTransactionSerialNumber();
};


#endif //BANKACCOUNTS_BANKDETAILSSTATE_H
