#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        list = new LinkedList<T>();
    }

    // Insertion
    void enqueue(const T& item) override {
        list->addTail(item);
    }

    // Deletion
    T dequeue() override {
        T data = list->getHead();
        list->removeHead();
        return data;
    }

    // Access
    T peek() const override {
        return list->getHead();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list->getSize();
    }
    ~LLQ() override {
        list.~LinkedList<T>();
    }
};