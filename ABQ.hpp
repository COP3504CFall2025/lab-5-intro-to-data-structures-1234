#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    [[nodiscard]] T peek() const override;

    // Deletion
    T dequeue() override;
};
template<typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}
template<typename T>
ABQ<T>::ABQ(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}
template<typename T>
ABQ<T>::ABQ(const ABQ& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        array_[i] = &new T(other.array_[i]);
    }
}
template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& rhs) {
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        array_[i] = &new T(rhs.array_[i]);
    }
    return *this;
}
template<typename T>
ABQ<T>::ABQ(ABQ<T>&& rhs) noexcept{
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;
    rhs.array_ = nullptr;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
}
template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept {
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;
    rhs.array_ = nullptr;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
    return *this;
}
template<typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    curr_size_ = 0;
    capacity_ = 0;
}

template<typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}
template<typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}
template<typename T>
[[nodiscard]] T* ABQ<T>::getData() const noexcept {
    return array_;
}
template<typename T>
void ABQ<T>::enqueue(const T &data) {
    if (curr_size_ == capacity_) {
        throw std::out_of_range("ABQ out of range");
    }
    array_[curr_size_] = data;
    curr_size_++;
}
template<typename T>
[[nodiscard]] T ABQ<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::out_of_range("Cannot peek an empty array");
    }
    return array_[0];
}
template<typename T>
T ABQ<T>::dequeue() {
    if (curr_size_ == 0) {
        throw std::out_of_range("Cannot dequeue an empty array");
    }
    T data = array_[0];
    for (size_t i = 0; i < curr_size_ - 1; i++) {
        array_[i] = array_[i + 1];
    }
    curr_size_--;
    return data;
}
