#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor

    LLS() = default;
    LLS(const LLS &origin) = default;
    LLS(LLS &&origin) = default;
    LLS &operator=(const LLS &origin) = default;
    LLS &operator=(LLS &&origin) = default;
    ~LLS() override = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() == 0)
            throw std::runtime_error("LLS pop on empty list");
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0)
            throw std::runtime_error("LLS peek on empty list");
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};