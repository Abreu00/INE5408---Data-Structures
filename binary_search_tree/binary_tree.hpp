#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "../linear_strucutures/array_list.hpp"

namespace structures {

//! Classe Arvode binaria
template<typename T>
class BinaryTree {
 public:
    ~BinaryTree();

    //! Insere na arvore
    void insert(const T& data);

    //! Remove da arvore
    void remove(const T& data);

    //! Contém
    bool contains(const T& data) const;

    //! Verifica se a arvore está vazia
    bool empty() const;

    //! Tamanho da arvore
    std::size_t size() const;

    //! pre-order
    ArrayList<T> pre_order() const;

    //! em-ordem
    ArrayList<T> in_order() const;

    //! pos-ordem
    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& value);

        void insert(const T& value);

        bool remove(const T& value);

        bool contains(const T& value) const;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;

        T data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
    size_ = 0u;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (!empty()) {
        if (root->remove(data)) --size_;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (empty()) {
        return false;
    }
    return root->contains(data);
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> v{};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> v{};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> v{};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size_ == 0;
}

/* ======== Node methods ======== */

template<typename T>
structures::BinaryTree<T>::Node::Node(const T& value) {
    data = value;
}

template<typename T>
bool structures::BinaryTree<T>::Node::contains(const T& value) const {
    if (value == data) {
        return true;
    } else if (value <= data) {
        if (left != nullptr) {
            return left->contains(value);
        }
    } else {
        if (right != nullptr) {
            return right->contains(value);
        }
    }
    return false;  // right or left is nullptr
}

template<typename T>
void structures::BinaryTree<T>::Node::insert(const T& value) {
    if (value <= data) {
        if (left == nullptr) {
            left = new Node(value);
        } else {
            left->insert(value);
        }
    } else {
        if (right == nullptr) {
            right = new Node(value);
        } else {
            right->insert(value);
        }
    }
}


template<typename T>
bool structures::BinaryTree<T>::Node::remove(const T& value) {
    if (value == data) {
        if ((left != nullptr) && (right != nullptr)) {
            Node *right_min = right;
            while (right_min->left) {
                right_min = right_min->left;
            }
            data = right_min->data;
            delete right_min;
            return true;
        } else {
            if (right != nullptr) {
                data = right->data;
                return right->remove(data);
            } else if (left != nullptr) {
                data = left->data;
                return left->remove(data);
            } else {  // Leaf Node
                    delete this;
                    return true;
            }
        }
    } else {
        if (right != nullptr && data < value) {
            return right->remove(value);
        } else if (left != nullptr && data > value) {
            return left->remove(value);
        }
    }
    return false;
}

template<typename T>
void structures::BinaryTree<T>::Node::pre_order(structures::ArrayList<T>& v) const {
    v.push_back(data);
    if (left != nullptr) {
        left->pre_order(v);
    }
    if (right != nullptr) {
        right->pre_order(v);
    }
}

template<typename T>
void structures::BinaryTree<T>::Node::in_order(structures::ArrayList<T>& v) const {
    if (left != nullptr) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right != nullptr) {
        right->in_order(v);
    }
}

template<typename T>
void structures::BinaryTree<T>::Node::post_order(structures::ArrayList<T>& v) const {
    if (left != nullptr) {
        left->post_order(v);
    }
    if (right != nullptr) {
        right->post_order(v);
    }
    v.push_back(data);
}

#endif
