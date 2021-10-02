//
// Created by calandrinon on 10/2/21.
//

#include "BankService.h"

BankService::BankService(BankAccountRepository *repository) {
    this->repository = repository;
}

void BankService::createAccount(std::string ownerName) {
    BankAccount* newAccount = new BankAccount(ownerName);
    this->repository->save(newAccount);
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

BankService::~BankService() {

}

