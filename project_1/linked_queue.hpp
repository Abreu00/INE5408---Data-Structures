// copyright [2019] Fábio de abreu
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <stdexcept>
#include <cstdint>

namespace structures {
//! Classe fila
template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();
    //! limpar
    void clear();
	//! enfilerar
    void enqueue(const T& data);
	//! desenfilerar
    T dequeue();
	//! primeiro dado
    T& front() const;
	//! último dado
    T& back() const;
	//! fila vazia
    bool empty() const;
	//! tamanho
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

		Node* next() {
			return next_;
		}

		const Node* next() const {
		    return next_;
		}

		T& data() {
		    return data_;
		}

		const T& data() const {
		    return data_;
		}

		void next(Node* next) {
			next_ = next;
		}

     private:
        T data_;
        Node* next_;
    };


    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0};  // tamanho
};
}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
	clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
	Node* node = new Node(data);
	if (node == nullptr) {
		delete node;
		throw std::out_of_range("List is full");
	}
	if (size_ == 0) {
		head = node;
		tail = node;
	} else {
		tail->next(node);
		tail = node;
	}
	size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
	if (empty()) {
		throw std::out_of_range("List is empty");
	}
	Node* to_remove = head;
	T data = to_remove->data();
	head = head->next();
	delete to_remove;
	size_--;
	return data;
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
	if (empty()) {
	    throw std::out_of_range("List is empty");
	}
	return head->data();
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
	if (empty()) {
	    throw std::out_of_range("List is empty");
	}
	return tail->data();
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
	return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
	return size_;
}

#endif
