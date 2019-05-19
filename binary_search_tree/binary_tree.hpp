#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "../linear_strucutures/array_list.hpp"

namespace structures {

//! Classe Arvore binaria
template<typename T>
class BinaryTree {
 public:
    ~BinaryTree() {
        delete root;
        size_ = 0u;
    }

    //! Insere na arvore
    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    //! Remove da arvore
    void remove(const T& data) {
        if (!empty()) {
            if (root->remove(data)) --size_;
        }
    }

    //! Contém
    bool contains(const T& data) const {
        if (empty()) {
            return false;
        }
        return root->contains(data);
    }

    //! Verifica se a arvore está vazia
    bool empty() const {
        return size_ == 0;
    }

    //! Tamanho da arvore
    std::size_t size() const {
        return size_;
    }

    //! pre-order
    ArrayList<T> pre_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->pre_order(v);
        }
        return v;
    }

    //! em-ordem
    ArrayList<T> in_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->in_order(v);
        }
        return v;
    }

    //! pos-ordem
    ArrayList<T> post_order() const {
        structures::ArrayList<T> v{};
        if (!empty()) {
            root->post_order(v);
        }
        return v;
    }

 private:
    struct Node {
        explicit Node(const T& value) {
            data = value;
        }

        void insert(const T& value) {
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
        bool remove(const T& value) {
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

        bool contains(const T& value) const {
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

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        T data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures

#endif
