#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <stdexcept>
#include <cstdint>

namespace structures {

//! Classe pilha encadeada
template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();
    //!  limpa pilha
    void clear();
    //! empilha
    void push(const T& data);
    //! desempilha
    T pop();
    //! dado no topo
    T& top() const;
    //! pilha vazia
    bool empty() const;
    //! tamanho da pilha
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {  // getter
            return data_;
        }

        const T& data() const {  // getter-constante: info
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* next) {  // setter
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_{0};  // tamanho
};
}  // namespace structures

template <typename T>
structures::LinkedStack<T>::LinkedStack() {}

template <typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template <typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return top_->data();
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_element = new Node(data);
    if (new_element == nullptr) {
        delete new_element;
        throw std::out_of_range("List is full");
    }
    if (empty()) {
        top_ = new_element;
    } else {
        new_element->next(top_);
        top_ = new_element;
    }
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    T data = top();
    Node* to_remove = top_;
    if (size_ > 1) {
        top_ = top_->next();
    }
    delete to_remove;
    size_--;
    return data;
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}

#endif
