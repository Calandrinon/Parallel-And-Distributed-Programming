//
// Created by calandrinon on 10/2/21.
//

#ifndef BANKACCOUNTS_REPOSITORY_H
#define BANKACCOUNTS_REPOSITORY_H
#include <iostream>
#include <vector>
#include "../Model/Model.h"

template <class T>
class Repository {
    protected:
        std::vector<T> container;
    public:
        Repository();
        virtual void save(T element) = 0;
        std::vector<T> getContainer();
        ~Repository();
};


#endif //BANKACCOUNTS_REPOSITORY_H
