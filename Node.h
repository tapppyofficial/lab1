#pragma once

#include <tuple>

template<typename T>
class Node {
public:

    Node *pNext;
    Node *pPrev;

    T data;

    Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
        this->data = data;
        this->pPrev = pPrev;
        this->pNext = pNext;
    }

    T &operator*() {
        return data;
    }
};

template<typename T>
bool operator!=(Node<T> &lhs, Node<T> &rhs) {
    return std::make_tuple(lhs.pNext, lhs.pPrev, lhs.data) != std::make_tuple(nullptr, nullptr, 0);
}

template<typename T>
std::ostream &operator<<(std::ostream &output, const Node<T> &node) {
    return output << node.data;
}

template<typename T>
bool operator<=(Node<T> &lhs, Node<T> &rhs) {
    return lhs.data <= rhs.data;
}
