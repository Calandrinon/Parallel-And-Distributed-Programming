//
// Created by calandrinon on 10/2/21.
//

#include <map>
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

int BankService::generateRandomOperations() {
    int numberOfOperations = 100000;

    for (int operationIndex = 0; operationIndex < numberOfOperations; operationIndex++) {
        BankAccount* transferrer = this->pickRandomAccount();
        BankAccount* transferree = this->pickRandomAccount();
        double sum = this->randomEngine() % 100 + 1;
        this->transferMoney(transferrer, transferree, sum);
        this->repository->addGlobalOperationRecord(new Operation(transferrer->getOwner(), transferree->getOwner(), sum));
        this->repository->setNumberOfRecentlyExecutedOperations(this->repository->getNumberOfRecentlyExecutedOperations()+1);
        /**
        if (!(operationIndex % 100))
            this->checkTransferLogsValidity(100);
          **/
    }

    return numberOfOperations;
}

void BankService::createRandomMultithreadedOperations(int numberOfThreads) {
    /**
    threads.emplace_back([this]() {
        while (true) {
            int lagSize = 1000;
            if (this->repository->getNumberOfRecentlyExecutedOperations() > lagSize) {
                assert(this->checkTransferLogsValidity(lagSize));
                this->repository->setNumberOfRecentlyExecutedOperations(0);
            }
        }
    });
     **/

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

bool BankService::checkTransferLogsValidity(int lagSize) {
    /**
     * lagSize: the last lagSize records are checked to see if each record is saved in the logs of both the bank
     *          accounts which participated in the transfer.
     * **/

    //this->operationValidityMutex.lock();
    std::vector<BankAccount*> accounts = this->repository->getContainer();
    std::map<std::string, BankAccount*> account_owners;
    for (BankAccount* account: accounts)
        account_owners[account->getOwner()] = account;

    std::vector<Operation*> operationsVector = this->repository->getGlobalOperationLog()->getOperations();
    auto vector_iterator = operationsVector.rbegin();

    for (; vector_iterator != operationsVector.rbegin() + lagSize; vector_iterator++) {
        Operation* operation = *vector_iterator;
        std::vector<Operation*> transferrerOperationLog = account_owners[operation->getTransferer()]->getOperationLog()->getOperations();
        std::vector<Operation*> transferreeOperationLog = account_owners[operation->getTransferee()]->getOperationLog()->getOperations();
        bool operationNotFoundInFirstLog = std::find(transferrerOperationLog.begin(), transferrerOperationLog.end(), operation) == transferrerOperationLog.end();
        bool operationNotFoundInSecondLog = std::find(transferreeOperationLog.begin(), transferreeOperationLog.end(), operation) == transferreeOperationLog.end();
        if (operationNotFoundInFirstLog || operationNotFoundInSecondLog)
            return false;
        std::cout << *vector_iterator << "\n";
    }

    //this->operationValidityMutex.unlock();

    return true;
}

bool BankService::checkBalanceValidityAfterTransfers() {
    return false;
}

BankService::~BankService() {

}
