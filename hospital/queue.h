#ifndef QUEUE_H
#define QUEUE_H
//written with chatGPT with ideal structure format
#include "patient.h"
#include <string>

class Queue {
public: // Change access level of Node to public
    struct Node {
        Patient data;
        Node* next;
        Node(Patient p) : data(p), next(nullptr) {}
    };

private:
    Node* front;
    Node* rear;
    int size;
    static const int MAX_SIZE = 10;

public:
    Queue();
    ~Queue();

    bool enqueueRegular(const Patient& p);
    bool enqueueCritical(const Patient& p);
    bool dequeue(Patient& p);
    bool cancelBySSN(const std::string& ssn, Patient& p);
    void list() const;
    bool isFull() const;
    bool isEmpty() const;
    void clear();

    // Add a getter for the front node
    Node* getFront() const { return front; }
};

#endif // QUEUE_H