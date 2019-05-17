#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstring>
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
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
    T* contents;
    std::size_t size_;
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

//! ArrayListString e' uma especializacao da classe ArrayList
namespace structures {
//! string list an ArrayList subclass
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();
    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    bool contains(const char *data);
    //!  ...
    void remove(const char *data);
    //! ...
    std::size_t find(const char *data);
};
};  // namespace structures

structures::ArrayListString::~ArrayListString() {
    clear();
}

void structures::ArrayListString::clear() {
    for (std::size_t i = 0; i < size(); ++i) {
        delete [] at(i);
    }
    ArrayList<char*>::clear();
}

void structures::ArrayListString::push_back(const char *data) {
    std::size_t lenght = strlen(data) + 1;
    char* ptr = new char[lenght + 1];
    snprintf(ptr, lenght, "%s", data);
    try {
        ArrayList<char*>::push_back(ptr);
    }
    catch(std::out_of_range) {
        delete [] ptr;
        throw std::out_of_range("list is full");
    }
}
void structures::ArrayListString::push_front(const char *data) {
    std::size_t lenght = strlen(data) + 1;
    char* ptr = new char[lenght + 1];
    snprintf(ptr, lenght, "%s", data);
    try {
        ArrayList<char *>::push_front(ptr);
    }
    catch (std::out_of_range) {
        delete [] ptr;
        throw std::out_of_range("list is full");
    }
}
void structures::ArrayListString::insert(const char *data, std::size_t index) {
    std::size_t lenght = strlen(data) + 1;
    char* ptr = new char[lenght + 1];
    snprintf(ptr, lenght, "%s", data);
    try {
        ArrayList<char*>::insert(ptr, index);
    }
    catch(std::out_of_range) {
        delete [] ptr;
        throw std::out_of_range("list is full");
    }
}
void structures::ArrayListString::insert_sorted(const char *data) {
    if (full()) {
        throw std::out_of_range("list is full");
    }

    for (std::size_t i = 0; i < size(); ++i) {
        if (strcmp(data, at(i)) < 0) {
            insert(data, i);
            return;
        }
    }
    push_back(data);
}
char* structures::ArrayListString::pop(std::size_t index) {
    return ArrayList<char*>::pop(index);
}
char* structures::ArrayListString::pop_front() {
    return ArrayList<char*>::pop_front();
}

char* structures::ArrayListString::pop_back() {
    return ArrayList<char*>::pop_back();
}
void structures::ArrayListString::remove(const char *data) {
    std::size_t index = find(data);
    pop(index);
}

bool structures::ArrayListString::contains(const char *data) {
    std::size_t index = find(data);
    if (index < size()) {
        return true;
    }
    return false;
}

std::size_t structures::ArrayListString::find(const char *data) {
    for (std::size_t i = 0; i < size(); ++i) {
        if (!strcmp(data, at(i))) {
            //  Found
            return i;
        }
    }
    return size();
}

#endif
