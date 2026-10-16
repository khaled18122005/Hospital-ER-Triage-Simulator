#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Node.h"

template <typename T>
class PriorityQueue {
private:
    Node<T>* head;
    int count;

public:
    PriorityQueue() : head(nullptr), count(0) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    // إدخال عنصر بناءً على درجة الأولوية (Priority) تنازلياً (الأعلى أولوية في المقدمة)
    bool enqueue(const T& newEntry, int priority) {
        Node<T>* newNodePtr = new Node<T>(newEntry, priority);

        if (isEmpty() || priority > head->getPriority()) {
            newNodePtr->setNext(head);
            head = newNodePtr;
        } else {
            Node<T>* current = head;
            while (current->getNext() != nullptr && current->getNext()->getPriority() >= priority) {
                current = current->getNext();
            }
            newNodePtr->setNext(current->getNext());
            current->setNext(newNodePtr);
        }
        count++;
        return true;
    }

    bool dequeue(T& frontEntry, int& frontPriority) {
        if (isEmpty()) return false;

        Node<T>* nodeToDeletePtr = head;
        frontEntry = head->getItem();
        frontPriority = head->getPriority();
        head = head->getNext();

        delete nodeToDeletePtr;
        count--;
        return true;
    }

    bool peek(T& frontEntry, int& frontPriority) const {
        if (isEmpty()) return false;
        frontEntry = head->getItem();
        frontPriority = head->getPriority();
        return true;
    }

    int getCount() const {
        return count;
    }

    ~PriorityQueue() {
        T tempVal;
        int tempPri;
        while (dequeue(tempVal, tempPri));
    }
};

#endif // PRIORITY_QUEUE_H
