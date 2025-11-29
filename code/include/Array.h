#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <algorithm>

template<class T>
class Array {
private:
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;

    void resize(size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        
        std::shared_ptr<T[]> newData(new T[newCapacity]);
        
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    Array() : size_(0), capacity_(10) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }
    
    explicit Array(size_t initialCapacity) : size_(0), capacity_(initialCapacity) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
    }
    
    ~Array() = default;
    
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::shared_ptr<T[]>(new T[capacity_]);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::shared_ptr<T[]>(new T[capacity_]);
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_] = std::move(value);
        ++size_;
    }
    
    void remove(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const {
        return size_;
    }
    
    size_t capacity() const {
        return capacity_;
    }
    
    bool empty() const {
        return size_ == 0;
    }
    
    void clear() {
        size_ = 0;
    }
};

#endif

