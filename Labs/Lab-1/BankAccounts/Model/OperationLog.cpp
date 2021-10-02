//
// Created by calandrinon on 10/2/21.
//

#include "OperationLog.h"

OperationLog::OperationLog() {}

void OperationLog::addOperation(Operation *operation) {
    this->operations.push_back(operation);
}

std::vector<Operation*> OperationLog::getOperations() {
    return this->operations;
}

OperationLog::~OperationLog() {
    for (Operation* operation: this->operations) {
        delete operation;
    }
}
