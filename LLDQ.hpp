#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("LLDQ::popFront: Empty list");
        }
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }
    T popBack() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("LLDQ::popBack: Empty list");
        }
        T data = list.getTail()->data;
        list.removeTail();
        return data;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("LLDQ::front: Empty list");
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("LLDQ::back: Empty list");
        }
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getSize();
    }
    ~LLDQ() override {
        list.~LinkedList<T>();
    }
};






