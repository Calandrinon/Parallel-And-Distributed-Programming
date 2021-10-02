//
// Created by calandrinon on 10/2/21.
//

#include "BankAccountRepository.h"

void BankAccountRepository::save(BankAccount *account) {
    this->container.push_back(account);
}

BankDetailsState *BankAccountRepository::getBankDetailsState() const {
    return bankDetailsState;
}

void BankAccountRepository::setBankDetailsState(BankDetailsState *bankDetailsState) {
    BankAccountRepository::bankDetailsState = bankDetailsState;
}
