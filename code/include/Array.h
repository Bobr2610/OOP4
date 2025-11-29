#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>

template<class T>
class Array {
private:
    struct ArrayDeleter {
        std::shared_ptr<size_t> size_ptr_;
        ArrayDeleter(std::shared_ptr<size_t> size_ptr = nullptr) : size_ptr_(size_ptr) {}
        void operator()(T* ptr) const {
            if (ptr && size_ptr_) {
                for (size_t i = 0; i < *size_ptr_; ++i) {
                    ptr[i].~T();
                }
                ::operator delete[](ptr);
            }
        }
    };
    
    std::shared_ptr<T> data_;
    std::shared_ptr<size_t> size_ptr_;
    size_t capacity_;

    void resize(size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        
        T* rawPtr = static_cast<T*>(::operator new[](newCapacity * sizeof(T)));
        
        for (size_t i = 0; i < *size_ptr_; ++i) {
            new (rawPtr + i) T(std::move(data_.get()[i]));
            data_.get()[i].~T();
        }
        
        data_ = std::shared_ptr<T>(rawPtr, ArrayDeleter(size_ptr_));
        capacity_ = newCapacity;
    }

public:
    Array() : size_ptr_(std::make_shared<size_t>(0)), capacity_(10) {
        T* rawPtr = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));
        data_ = std::shared_ptr<T>(rawPtr, ArrayDeleter(size_ptr_));
    }
    
    explicit Array(size_t initialCapacity) : size_ptr_(std::make_shared<size_t>(0)), capacity_(initialCapacity) {
        T* rawPtr = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));
        data_ = std::shared_ptr<T>(rawPtr, ArrayDeleter(size_ptr_));
    }
    
    ~Array() {
        clear();
    }
    
    Array(const Array& other) : size_ptr_(std::make_shared<size_t>(*other.size_ptr_)), capacity_(other.capacity_) {
        T* rawPtr = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));
        data_ = std::shared_ptr<T>(rawPtr, ArrayDeleter(size_ptr_));
        for (size_t i = 0; i < *size_ptr_; ++i) {
            new (rawPtr + i) T(other.data_.get()[i]);
        }
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            for (size_t i = 0; i < *size_ptr_; ++i) {
                data_.get()[i].~T();
            }
            
            size_ptr_ = std::make_shared<size_t>(*other.size_ptr_);
            capacity_ = other.capacity_;
            T* rawPtr = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));
            data_ = std::shared_ptr<T>(rawPtr, ArrayDeleter(size_ptr_));
            for (size_t i = 0; i < *size_ptr_; ++i) {
                new (rawPtr + i) T(other.data_.get()[i]);
            }
        }
        return *this;
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), size_ptr_(std::move(other.size_ptr_)), capacity_(other.capacity_) {
        other.size_ptr_ = std::make_shared<size_t>(0);
        other.capacity_ = 0;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < *size_ptr_; ++i) {
                data_.get()[i].~T();
            }
            
            data_ = std::move(other.data_);
            size_ptr_ = std::move(other.size_ptr_);
            capacity_ = other.capacity_;
            other.size_ptr_ = std::make_shared<size_t>(0);
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (*size_ptr_ >= capacity_) {
            resize(capacity_ * 2);
        }
        new (data_.get() + *size_ptr_) T(value);
        ++(*size_ptr_);
    }
    
    void push_back(T&& value) {
        if (*size_ptr_ >= capacity_) {
            resize(capacity_ * 2);
        }
        new (data_.get() + *size_ptr_) T(std::move(value));
        ++(*size_ptr_);
    }
    
    void remove(size_t index) {
        if (index >= *size_ptr_) {
            throw std::out_of_range("Index out of range");
        }
        
        data_.get()[index].~T();
        for (size_t i = index; i < *size_ptr_ - 1; ++i) {
            new (data_.get() + i) T(std::move(data_.get()[i + 1]));
            data_.get()[i + 1].~T();
        }
        --(*size_ptr_);
    }
    
    T& operator[](size_t index) {
        if (index >= *size_ptr_) {
            throw std::out_of_range("Index out of range");
        }
        return data_.get()[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= *size_ptr_) {
            throw std::out_of_range("Index out of range");
        }
        return data_.get()[index];
    }
    
    size_t size() const {
        return *size_ptr_;
    }
    
    size_t capacity() const {
        return capacity_;
    }
    
    bool empty() const {
        return *size_ptr_ == 0;
    }
    
    void clear() {
        for (size_t i = 0; i < *size_ptr_; ++i) {
            data_.get()[i].~T();
        }
        *size_ptr_ = 0;
    }
};

#endif
