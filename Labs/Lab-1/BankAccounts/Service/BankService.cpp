//
// Created by calandrinon on 10/2/21.
//

#include "BankService.h"

BankService::BankService(BankAccountRepository *repository) {
    this->repository = repository;
}

BankAccount* BankService::createAccount(std::string ownerName) {
    BankAccount* newAccount = new BankAccount(ownerName);
    int accountSerialNumber = this->repository->getBankDetailsState()->getAccountSerialNumber() + 1;
    this->repository->getBankDetailsState()->setAccountSerialNumber(accountSerialNumber);
    newAccount->setId(accountSerialNumber);
    this->repository->save(newAccount);

    return newAccount;
}

void BankService::transferMoney(BankAccount *transferer, BankAccount *transferee, double amount) {
    OperationLog* transfererOperationLog = transferer->getOperationLog();
    OperationLog* transfereeOperationLog = transferee->getOperationLog();
    auto* transferOperation = new Operation(transferer->getOwner(), transferee->getOwner(), amount);
    transfererOperationLog->addOperation(transferOperation);
    transfereeOperationLog->addOperation(transferOperation);

    transferer->setBalance(transferer->getBalance() - amount);
    transferee->setBalance(transferee->getBalance() + amount);
}

std::vector<BankAccount*> BankService::getAccounts() {
    return this->repository->getContainer();
}

BankService::~BankService() {

}

