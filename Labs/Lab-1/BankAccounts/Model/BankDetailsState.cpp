//
// Created by calandrinon on 10/2/21.
//

#include "BankDetailsState.h"

BankDetailsState::BankDetailsState() {

}

BankDetailsState::~BankDetailsState() {

}

int BankDetailsState::getTransactionSerialNumber() const {
    return transactionSerialNumber;
}

void BankDetailsState::setTransactionSerialNumber(int transactionSerialNumber) {
    BankDetailsState::transactionSerialNumber = transactionSerialNumber;
}

void BankDetailsState::incrementTransactionSerialNumber() {
    this->transactionSerialNumber++;
}
