#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
template<typename T>
ABS<T>::ABS() {
    array_ = nullptr;
    capacity_ = 0;
    curr_size_ = 0;
}
template<typename T>
ABS<T>::ABS(const size_t capacity) {
    array_ = new T[capacity];
    capacity_ = capacity;
    curr_size_ = 0;
}
template<typename T>
ABS<T>::ABS(const ABS<T>& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; i++) {
        array_[i] = &new T(other[i]);
    }
}
template<typename T>
ABS<T>::ABS(ABS<T>&& other) noexcept {
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = other.array_;
    other.array_ = nullptr;
    other.curr_size_ = 0;
    other.capacity_ = 0;
}
template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& rhs) {
    if (this != rhs) {
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = &new T(rhs[i]);
        }
    }
    return *this;
}
template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this != &rhs) {
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
    }
    rhs.array_ = nullptr;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
    return *this;
}
template<typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ == capacity_) {
        capacity_ *= scale_factor_;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        array_[curr_size_] = data;
        curr_size_++;
    } else {
        array_[curr_size_] = data;
        curr_size_++;
    }
}
template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) {
        throw std::runtime_error("pop");
    }
    curr_size_--;
    return array_[curr_size_];
}
template<typename T>
T ABS<T>::peek() const {
    return array_[curr_size_ - 1];
}
template<typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}
template<typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}
template<typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}
template<typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
    curr_size_ = 0;
    capacity_ = 0;
}