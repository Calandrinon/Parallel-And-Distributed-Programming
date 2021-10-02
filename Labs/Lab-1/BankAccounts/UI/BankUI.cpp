//
// Created by calandrinon on 10/2/21.
//

#include "BankUI.h"

BankUI::BankUI(BankService *service) {
    this->service = service;
}

void BankUI::runExample() {
    std::cout << "BankUI started successfully.\n";
    BankAccount* jack = this->service->createAccount("Jack");
    BankAccount* jill = this->service->createAccount("Jill");
    jack->setBalance(1000);
    jill->setBalance(1000);

    for (BankAccount* account: this->service->getAccounts()) {
        std::cout << "Account ID: " << account->getId() << "; Account owner: " << account->getOwner() << ";\n";
    }

    this->service->transferMoney(jack, jill, 100);

    std::cout << "Jack's balance: " << jack->getBalance() << "\n";
    std::cout << "Jill's balance: " << jill->getBalance() << "\n";

    std::cout << "Jack's operations: " << "\n";
    for (Operation* operation: jack->getOperationLog()->getOperations()) {
        std::cout << operation->getAmount() << "$ transferred from " << operation->getTransferer() << " to " << operation->getTransferee() << "\n";
    }

    std::cout << "Jill's operations: " << "\n";
    for (Operation* operation: jill->getOperationLog()->getOperations()) {
        std::cout << operation->getAmount() << "$ transferred from " << operation->getTransferer() << " to " << operation->getTransferee() << "\n";
    }
}
