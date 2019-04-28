#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

//! Classe lista encadeada
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures

template<typename T>
structures::LinkedList<T>::LinkedList() {}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
  clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
	Node* node = head;
    for (int i = 0; i < size_; ++i) {
		delete node;
		node = node->next();
    }
    head = nullptr;
	size_ = 0;
}
template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* new_element = new Node(data, head);
    if (new_element == nullptr) {
        delete new_element;
        throw std::out_of_range("List is full");
    }
    if (empty()) {
        new_element->next(head);
	    head = new_element;
    } else {
        head = new_element;
    }
    size_++;
}
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* new_element = new Node(data);
    if (new_element == nullptr) {
        delete new_element;
        throw std::out_of_range("List is full");
    }
    if (empty()) {
        head = new_element;
    } else {
        end()->next(new_element);
    }
	size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* new_element = new Node(data);
	if (new_element == nullptr) {
		delete new_element;
		throw std::out_of_range("List is full");
	}
    if (index > size_ || index < 0) {
        delete new_element;
        throw std::out_of_range("Index out of range");
    } else if (size_ == 0 || index == 0) {
        push_front(data);
    } else {
        Node* node = head;
        for (int i = 0; i < index - 1; ++i) {
            node = node->next();  // Gets node on position index - 1
        }
        new_element->next(node->next());
        node->next(new_element);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    for (int i  = 0; i < size_; ++i) {
        if (data < at(i)) {
            insert(data, i);
            return;
        }
    }
    push_back(data);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
	if (empty()) {
        throw std::out_of_range("List is empty");
    }
    T data = head->data();
    head = head->next();
    size_--;
	return data;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
	if (empty()) {
        throw std::out_of_range("List is empty");
    }
    T last = end()->data();
	delete end();
	size_--;
	return last;
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
	if (index >= size_ || index < 0) throw std::out_of_range("Index out of range");
	if (index == 0) return pop_front();

	Node* node =  head;
	for (int i = 0; i < index - 1; ++i) {
		node = node->next();  // Gets element on position index - 1
	}
	Node* to_remove = node->next();
	node->next(to_remove->next());
	T data = to_remove->data();
	delete to_remove;
    size_--;
	return data;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
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
bool structures::LinkedList<T>::contains(const T& data) const {
	return find(data) != size_;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
	int index = find(data);
	pop(index);
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
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
