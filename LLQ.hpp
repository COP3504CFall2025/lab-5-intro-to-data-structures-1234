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
    LLQ() = default;
    LLQ(const LLQ &origin) = default;
    LLQ(LLQ &&origin) = default;
    LLQ &operator=(const LLQ &origin) = default;
    LLQ &operator=(LLQ &&origin) = default;
    ~LLQ() override = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() == 0)
            throw std::runtime_error("LLQ dequeue on an empty queue");
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0)
            throw std::runtime_error("LLQ peek on an empty queue");
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getSize();
    }
};