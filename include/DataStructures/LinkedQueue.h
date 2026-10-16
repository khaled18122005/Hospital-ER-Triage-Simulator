#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Node.h"

template <typename T>
class LinkedQueue {
private:
    Node<T>* frontPtr;
    Node<T>* backPtr;
    int count;

public:
    LinkedQueue() : frontPtr(nullptr), backPtr(nullptr), count(0) {}

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    // إضافة عنصر جديد في نهاية الطابور (FIFO)
    bool enqueue(const T& newEntry) {
        Node<T>* newNodePtr = new Node<T>(newEntry);
        if (isEmpty()) {
            frontPtr = newNodePtr;
        } else {
            backPtr->setNext(newNodePtr);
        }
        backPtr = newNodePtr;
        count++;
        return true;
    }

    // إزالة العنصر الموجود في مقدمة الطابور
    bool dequeue(T& frontEntry) {
        if (isEmpty()) return false;

        Node<T>* nodeToDeletePtr = frontPtr;
        frontEntry = frontPtr->getItem();
        frontPtr = frontPtr->getNext();

        if (nodeToDeletePtr == backPtr) {
            backPtr = nullptr;
        }

        delete nodeToDeletePtr;
        count--;
        return true;
    }

    // معاينة العنصر الموجود في المقدمة بدون حذفه
    bool peek(T& frontEntry) const {
        if (isEmpty()) return false;
        frontEntry = frontPtr->getItem();
        return true;
    }

    int getCount() const {
        return count;
    }

    // Destructor لتفريغ الذاكرة ومنع Memory Leaks
    ~LinkedQueue() {
        T temp;
        while (dequeue(temp));
    }
};

#endif // LINKED_QUEUE_H
