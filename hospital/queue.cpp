#include "Header.h"
//written with chatGPT with ideal structure format
Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

Queue::~Queue() {
    clear();
}

bool Queue::enqueueRegular(const Patient& p) {
    if (isFull()) return false;
    Node* newNode = new Node(p);
    if (!rear) front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
    ++size;
    return true;
}

bool Queue::enqueueCritical(const Patient& p) {
    if (isFull()) return false;
    Node* newNode = new Node(p);
    newNode->data.status = CRITICAL;

    if (!front || front->data.status == REGULAR) {
        newNode->next = front;
        front = newNode;
        if (!rear) rear = newNode;
    }
    else {
        Node* current = front;
        while (current->next && current->next->data.status == CRITICAL) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) rear = newNode;
    }
    ++size;
    return true;
}

bool Queue::dequeue(Patient& p) {
    if (isEmpty()) return false;
    Node* temp = front;
    p = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    --size;
    return true;
}

bool Queue::cancelBySSN(const std::string& ssn, Patient& p) {
    Node* current = front;
    Node* prev = nullptr;
    while (current) {
        if (current->data.ssn == ssn) {
            p = current->data;
            if (prev) prev->next = current->next;
            else front = current->next;
            if (current == rear) rear = prev;
            delete current;
            --size;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void Queue::list() const {
    Node* current = front;
    while (current) {
        const Patient& p = current->data;

        cout << p.firstName;
        if (!p.lastName.empty()) {
            cout << " " << p.lastName;
        }
        cout << " (SSN: " << p.ssn << ") "
            << (p.status == CRITICAL ? "Critical" : "Regular") << endl;

        current = current->next;
    }
}

bool Queue::isFull() const {
    return size >= MAX_SIZE;
}

bool Queue::isEmpty() const {
    return size == 0;
}

void Queue::clear() {
    Patient dummy;
    while (!isEmpty()) dequeue(dummy);
}

