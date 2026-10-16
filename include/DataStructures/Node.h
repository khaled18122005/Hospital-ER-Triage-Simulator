#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
private:
    T item;
    int priority;
    Node<T>* next;

public:
    Node(const T& newItem, int pri = 0) : item(newItem), priority(pri), next(nullptr) {}

    void setItem(const T& newItem) { item = newItem; }
    T getItem() const { return item; }

    void setPriority(int pri) { priority = pri; }
    int getPriority() const { return priority; }

    void setNext(Node<T>* nextNodePtr) { next = nextNodePtr; }
    Node<T>* getNext() const { return next; }
};

#endif // NODE_H