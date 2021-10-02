//
// Created by calandrinon on 10/2/21.
//

#include "BankAccountRepository.h"


BankAccountRepository::BankAccountRepository() {
    this->bankDetailsState = new BankDetailsState();
}

void BankAccountRepository::save(BankAccount *account) {
    this->container.push_back(account);
}

BankDetailsState *BankAccountRepository::getBankDetailsState() const {
    return bankDetailsState;
}

void BankAccountRepository::setBankDetailsState(BankDetailsState* bankDetailsState) {
    this->bankDetailsState = bankDetailsState;
}

std::vector<BankAccount*> BankAccountRepository::getContainer() const {
    return this->container;
}
