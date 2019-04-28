#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <string>
#include <cstdint>
#include <stdexcept>
namespace structures {

template<typename T>
//! List Data structure class
class ArrayList {
 public:
    //! Simple constructor
    ArrayList();
    //! Dynamic sized constructor
    explicit ArrayList(std::size_t max);
    //! Destructor
    ~ArrayList();
    //! Method that clears the data structure
    void clear();
    //! Adds element on the last position of the list
    void push_back(const T& data);
    //! Adds element on the first position of the list
    void push_front(const T& data);
    //! Inserts element on desired postion
    void insert(const T& data, std::size_t index);
    //! Inserts element in sorted position, if the list is sorted
    void insert_sorted(const T& data);
    //! Removes element from desired inddex from the list and returns it
    T pop(std::size_t index);
    //! Removes last element from the list and returns it
    T pop_back();
    //! Removes first element from the list and returns it
    T pop_front();
    //! Removes desired element from the list
    void remove(const T& data);
    //! Returns if list is full
    bool full() const;
    //! Returns if list is empty
    bool empty() const;
    //! Returns if the list contains a selected object
    bool contains(const T& data) const;
    //! Returns the position of an object in the  list
    std::size_t find(const T& data) const;
    //! Returns current size of the list
    std::size_t size() const;
    //! Returns max size of the list
    std::size_t max_size() const;
    //! Returns element on the desired position
    T& at(std::size_t index);
    //! Returns element on the desired position
    T& operator[](std::size_t index);
    //! Returns element on the desired position
    const T& at(std::size_t index) const;
    //! Returns element on the desired position
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  //  namespace structures

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    size_ = 0;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    size_ = 0;
    contents = new T[max];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("list is full");
    }
    contents[size_] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("list is full");
    }
    for (int i = size_; i > 0; --i) {
        contents[i] = contents[i - 1];
    }
    contents[0] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full() || index >= max_size_) {
        throw std::out_of_range("list is full");
    }
    for (int i = size_; i > index; --i) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("list is full");
    } else if (empty()) {
        push_back(data);
        return;
    }
    for (int i = 0; i < size_; i++) {
        if (data < contents[i]) {
            insert(data, i);
            return;
        }
    }
    push_back(data);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("list is empty");
    } else if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    T removed = contents[index];
    for (int i = index + 1; i < size_; ++i) {
        contents[i - 1] = contents[i];
    }
    size_--;
    return removed;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("list is empty");
    }
    T data = contents[size_ - 1];
    size_--;
    return data;
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("list is empty");
    }
    T first = contents[0];
    for (int i = 0; i < size_; ++i) {
        contents[i] = contents[i + 1];
    }
    size_--;
    return first;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    std::size_t index = find(data);
    pop(index);
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; ++i) {
        if (data == contents[i]) return i;
    }
    return size_;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_; ++i) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return contents[index];
}
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return at(index);
}

#endif
