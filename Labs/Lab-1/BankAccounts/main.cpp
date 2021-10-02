#include <iostream>
#include "Repository/BankAccountRepository.h"
#include "Service/BankService.h"
#include "UI/BankUI.h"

int main() {
    BankAccountRepository* repository = new BankAccountRepository();
    BankService* service = new BankService(repository);
    BankUI* ui = new BankUI(service);
    //ui->runExample();
    ui->runValidThreadConfigurationWithLocks();
    return 0;
}
