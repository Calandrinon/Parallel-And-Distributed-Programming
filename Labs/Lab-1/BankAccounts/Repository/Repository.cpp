//
// Created by calandrinon on 10/2/21.
//

#include "Repository.h"

template<class T>
Repository<T>::Repository() {}

template<class T>
std::vector<T> Repository<T>::getContainer() {
    return this->container;
}

template<class T>
Repository<T>::~Repository() {
}