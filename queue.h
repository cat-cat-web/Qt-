#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>

 // 使用链队列进行排队操作（数量不固定）
template <typename T>

class Node {
public:
    T data;
    Node *next;
    Node(const T &data) : data(data), next(nullptr) {}
}; //节点类

template <typename T>
class queue {
private:


public:
    Node<T> *front;
    Node<T> *rear;
    int size;

    queue() : front(nullptr), rear(nullptr), size(0) {} //初始构造

    ~queue() {
        while (!isEmpty()) {
            deQueue();
        }
    }

    // 入队
    void enQueue(const T &car) {
        Node<T> *newNode = new Node<T>(car);
        if (rear == nullptr) {
            // 队列为空，则front和rear都指向新节点
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // 出队
    bool deQueue() {
        if (isEmpty()) {
            throw std::logic_error("队列为空");
        }
        Node<T> *temp = front;
        front = front->next;
        if (front == nullptr) {
            // 如果出队后队列为空，rear 也设置为 nullptr
            rear = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    // 获取队首车辆
    T getFront() const {
        if (!isEmpty()) {
            return front->data;
        }
        throw std::out_of_range("Queue is empty");
    }


    // 队列是否为空
    bool isEmpty() const {
        return size == 0;
    }

    // 获取当前队列大小
    int getSize() const {
        return size;
    }
};

#endif // QUEUE_H
