//
// Created by calandrinon on 10/2/21.
//

#include "BankService.h"
#include <cstdlib>
#include <unistd.h>

BankService::BankService(BankAccountRepository *repository) {
    this->repository = repository;
}

BankAccount* BankService::createAccount(std::string ownerName, double balance) {
    BankAccount* newAccount = new BankAccount(ownerName);
    newAccount->setBalance(balance);
    int accountSerialNumber = this->repository->getBankDetailsState()->getAccountSerialNumber() + 1;
    this->repository->getBankDetailsState()->setAccountSerialNumber(accountSerialNumber);
    newAccount->setId(accountSerialNumber);
    this->repository->save(newAccount);

    return newAccount;
}

void BankService::transferMoney(BankAccount *transferer, BankAccount *transferee, double amount) {
    std::unique_lock<std::mutex> transferLock(this->operationMutex);
    if (transferer->getBalance() < amount)
        return;

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

std::string BankService::generateRandomString(int length) {
    std::string randomString;
    static const char alphabet[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine randomEngine(seed);
    randomString.reserve(length);

    for (int i = 0; i < length; ++i)
        randomString += alphabet[randomEngine() % (sizeof(alphabet) - 1)];

    return randomString;
}

void BankService::createRandomAccounts(int quantity) {
    for (int accountIndex = 0; accountIndex < quantity; accountIndex++) {
        this->createAccount(generateRandomString(30), rand() % 10000 + 1000);
    }
}

double BankService::getTotalAccountsBalance() {
    double totalBalance = 0;
    std::vector<BankAccount*> accounts = this->getAccounts();
    for (BankAccount* account: accounts) {
        totalBalance += account->getBalance();
    }

    return totalBalance;
}

void BankService::createRandomMultithreadedOperations(int numberOfThreads) {
    auto thread_lambda = [this](BankAccount* transferer, BankAccount* transferee, double sum) {
        this->transferMoney(transferer, transferee, sum);
        std::cout << "Transferred " << sum << "$ from " << transferer->getOwner() << " to " << transferee->getOwner() << "\n";
    };

    for (int thread_index = 0; thread_index < numberOfThreads; thread_index++) {
        BankAccount* transferrer = this->pickRandomAccount();
        BankAccount* transferree = this->pickRandomAccount();
        while (transferrer == transferree) {
            BankAccount* transferrer = this->pickRandomAccount();
            BankAccount* transferree = this->pickRandomAccount();
        }
        threads.emplace_back(thread_lambda, transferrer, transferree, rand() % 100);
    }

    for (std::thread& thread: threads) {
        thread.join();
    }
}

BankAccount* BankService::pickRandomAccount() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine randomEngine(seed);
    std::vector<BankAccount*> accounts = this->repository->getContainer();
    int randomIndex = randomEngine() % accounts.size();

    return accounts[randomIndex];
}


BankService::~BankService() {

}
