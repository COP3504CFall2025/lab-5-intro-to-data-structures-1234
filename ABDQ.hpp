#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        data_ = new T[1];
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    explicit ABDQ(std::size_t capacity) {
        data_ = new T[capacity];
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        for (std::size_t i = front_; i <= back_; i++) {
            T on = new T(&other.data_[i]);
            data_[i] = on;
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        for (std::size_t i = front_; i <= back_; i++) {
            T on = new T(&other.data_[i]);
            data_[i] = on;
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            other = nullptr;
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
            other.front_ = 0;
            other.back_ = 0;
            return *this;
        }
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* holder = new T[capacity_];
            for (std::size_t i = front_; i <= size_; i++) {
                holder[i] = data_[i];
            }
            delete[] data_;
            data_ = holder;
        }
        if (front_ == 0) {
            front_ = capacity_ - 1;
            data_[front_] = item;
            size_++;
        } else {
            data_[front_ - 1 ] = item;
            front_--;
            size_++;
        }
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* holder = new T[capacity_];
            for (std::size_t i = 0; i < size_; i++) {
                holder[i] = data_[i];
            }
            delete[] data_;
            data_ = holder;
        }
        if (back_ == capacity_ - 1) {
            back_ = 0;
            data_[back_] = item;
            size_++;
        } else {
            back_++;
            size_++;
            data_[back_] = item;
        }
    }

    // Deletion
    T popFront() override {
        if (front_ == back_) {
            throw std::out_of_range("Empty queue");
        }
        T data = data_[front_];
        if (front_ == capacity_ - 1) {
            front_ = 0;
            size_--;
        } else {
            front_++;
            size_--;
        }
        return data;
    }
    T popBack() override {
        if (front_ == back_) {
            throw std::out_of_range("Empty queue");
        }
        T data = data_[back_];
        if (back_ == 0) {
            back_ = capacity_ - 1;
            size_--;
        } else {
            back_--;
            size_--;
        }
        return data;
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }
    const T& back() const override {
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
