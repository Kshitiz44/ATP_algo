#include <iostream>
#include <memory>

template <typename T>
class Node {
public:
    T data;
    std::shared_ptr<Node<T>> prev;
    std::shared_ptr<Node<T>> next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void pushFront(const T& value) {
        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pushBack(const T& value) {
        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAt(const T& value, size_t index) {
        if (index == 0) {
            pushFront(value);
            return;
        } else if (index >= size) {
            pushBack(value);
            return;
        }

        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
        std::shared_ptr<Node<T>> current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }

    void popFront() {
        if (head == nullptr) {
            std::cout << "Error: List is empty." << std::endl;
            return;
        }

        std::shared_ptr<Node<T>> temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        temp->next = nullptr;
        size--;
    }

    void popBack() {
        if (tail == nullptr) {
            std::cout << "Error: List is empty." << std::endl;
            return;
        }

        std::shared_ptr<Node<T>> temp = tail;
        tail = tail->prev;
        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        temp->prev = nullptr;
        size--;
    }

    void printList() const {
        std::shared_ptr<Node<T>> current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    DoublyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushFront(5);
    list.pushFront(2);
    list.insertAt(15, 2);

    std::cout << "List: ";
    list.printList(); // Output: List: 2
    list.popBack();
    list.popFront();

    std::cout << "List after pop operations: ";
    list.printList(); // Output: List after pop operations: 5 15 10

    std::cout << "List size: " << list.getSize() << std::endl; // Output: List size: 3

    return 0;
}