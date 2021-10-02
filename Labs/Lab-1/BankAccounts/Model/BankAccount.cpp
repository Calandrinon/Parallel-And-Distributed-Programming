//
// Created by calandrinon on 10/2/21.
//

#include "BankAccount.h"

BankAccount::BankAccount() {
    this->balance = 0;
    this->operationLog = new OperationLog();
    this->creationDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

BankAccount::~BankAccount() {

}

double BankAccount::getBalance() {
    return this->balance;
}

void BankAccount::setBalance(double balance) {
    this->balance = balance;
}

void BankAccount::transferToAccount(BankAccount *anotherAccount, double amount) {
    anotherAccount->setBalance(anotherAccount->getBalance() + amount);
    this->operationLog->addOperation(new Operation(this->getOwner(), anotherAccount->getOwner(), amount));
    this->balance -= amount;
    anotherAccount->getOperationLog()->addOperation(new Operation(this->getOwner(), anotherAccount->getOwner(), amount));
}

OperationLog *BankAccount::getOperationLog() const {
    return operationLog;
}

void BankAccount::setOperationLog(OperationLog *operationLog) {
    BankAccount::operationLog = operationLog;
}

const std::string &BankAccount::getOwner() const {
    return owner;
}

void BankAccount::setOwner(const std::string &owner) {
    BankAccount::owner = owner;
}

time_t BankAccount::getCreationDate() const {
    return creationDate;
}

void BankAccount::setCreationDate(time_t creationDate) {
    BankAccount::creationDate = creationDate;
}
