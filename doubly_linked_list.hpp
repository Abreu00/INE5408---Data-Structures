// Copyright [2019] <Fábio de abreu>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Lista duplamente encadeada
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    //! limpa lista
    void clear();
    //! insere no fim
    void push_back(const T& data);
    //! insere no início
    void push_front(const T& data);
    //! insere na posição
    void insert(const T& data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const T& data);

    //! retira da posição
    T pop(std::size_t index);
    //! retira do fim
    T pop_back();
    //! retira do início
    T pop_front();
    //! retira específico
    void remove(const T& data);
    //! lista vazia
    bool empty() const;
    //! contém
    bool contains(const T& data) const;
    //! acesso a um elemento (checando limites)
    T& at(std::size_t index);
    //! getter constante a um elemento
    const T& at(std::size_t index) const;
    //! posição de um dado
    std::size_t find(const T& data) const;
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

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }


        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head{nullptr};  // primeiro da lista
    Node* tail{nullptr};  // ultimo da lista
    std::size_t size_{0};
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) pop_front();
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* new_element = new Node(data);
    if (new_element == nullptr) {
        delete new_element;
        throw std::out_of_range("List is full");
    }
    if (empty()) {
        head = new_element;
        tail = new_element;
    } else {
        new_element->prev(tail);
        tail->next(new_element);
        tail = new_element;
    }
	size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* new_element = new Node(data, head);
    if (new_element == nullptr) {
        delete new_element;
        throw std::out_of_range("List is full");
    }
    if (empty()) {
        head = new_element;
    } else {
        head->prev(new_element);
        head = new_element;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("Index out of range");
    } else if (index == 0) {
        push_front(data);
        return;
    }
    Node* new_element = new Node(data);

	if (new_element == nullptr) {
		delete new_element;
		throw std::out_of_range("List is full");
	} else {
        Node* before = head;
        for (int i = 0; i < index - 1; ++i) {
            before = before->next();  // Gets node on position index - 1
        }
        new_element->next(before->next());
        new_element->prev(before);
        new_element->next()->prev(new_element);
        before->next(new_element);
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node* node = head;
    for (int i  = 0; i < size_; ++i) {
        if (data < node->data()) {
            insert(data, i);
            return;
        }
        node = node->next();
    }
    push_back(data);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
	if (empty()) {
        throw std::out_of_range("List is empty");
    }
    T data = head->data();
    Node* to_remove = head;
    head = head->next();
    delete to_remove;
    size_--;
	return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
	if (empty()) {
        throw std::out_of_range("List is empty");
    }
    T last = tail->data();
	Node* to_remove = tail;
    tail = tail->prev();
    delete to_remove;
	size_--;
	return last;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
	if (index >= size_ || index < 0) throw std::out_of_range("Index out of range");
	if (index == 0) return pop_front();

	Node* before =  head;
	for (int i = 0; i < index - 1; ++i) {
		before = before->next();  // Gets element before index
	}
    Node* to_remove = before->next();
    T data = to_remove->data();
    before->next(to_remove->next());
    to_remove->next()->prev(before);
    delete to_remove;
    size_--;
	return data;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
	Node* node  = head;
	for (int i = 0; i < size_; ++i) {
		if (node->data() == data) {
			return i;
		}
        node = node->next();
	}
	return size_;
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
	return find(data) != size_;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
	int index = find(data);
	pop(index);
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
	if (index > size_ || index < 0) {
        throw std::out_of_range("Index out of range");
	}
    Node* node = head;
	for (int i  = 0; i < index; ++i) {
		node = node->next();
	}
	return node->data();
}

#endif
