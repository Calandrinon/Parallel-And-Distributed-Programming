//
// Created by calandrinon on 10/2/21.
//

#include "BankService.h"

BankService::BankService(BankAccountRepository *repository) {
    this->repository = repository;
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    this->randomEngine = std::default_random_engine(seed);
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

    randomString.reserve(length);

    for (int i = 0; i < length; ++i)
        randomString += alphabet[this->randomEngine() % (sizeof(alphabet) - 1)];

    return randomString;
}

void BankService::createRandomAccounts(int quantity) {
    for (int accountIndex = 0; accountIndex < quantity; accountIndex++) {
        this->createAccount(generateRandomString(5), this->randomEngine() % 10000 + 1000);
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

void BankService::generateRandomOperations() {
    int numberOfOperations = 100000 + this->randomEngine() % 100000;

    for (int operationIndex = 0; operationIndex < numberOfOperations; operationIndex++) {
        BankAccount* transferrer = this->pickRandomAccount();
        BankAccount* transferree = this->pickRandomAccount();
        double sum = this->randomEngine() % 100 + 1;
        this->transferMoney(transferrer, transferree, sum);
    }
}

void BankService::createRandomMultithreadedOperations(int numberOfThreads) {
    for (int thread_index = 0; thread_index < numberOfThreads; thread_index++)
        threads.emplace_back([this]() {
            this->generateRandomOperations();
        });

    for (std::thread& thread: threads)
        thread.join();
}

BankAccount* BankService::pickRandomAccount() {
    std::vector<BankAccount*> accounts = this->repository->getContainer();
    int randomIndex = this->randomEngine() % accounts.size();

    return accounts[randomIndex];
}

BankService::~BankService() {

}
