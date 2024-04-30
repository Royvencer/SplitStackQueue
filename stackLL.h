#pragma once

class stackLL
{
private:
    class node
    {
    public:
        int data;
        node* next;

        // Constructor for node
        node(int value) : data(value), next(nullptr) {}
    };

    node* top;

public:
    // Constructor
    // O(1) because it only involves initializing the top pointer
    stackLL() : top(nullptr) {}

    // Destructor
    // O(n) where n is the number of elements in the stack, as it involves deleting all nodes
    ~stackLL()
    {
        while (!empty()) {
            pop();
        }
    }

    // Check if the stack is empty
    // O(1) because it only involves checking if the top pointer is null
    bool empty()
    {
        return top == nullptr;
    }

    // Add item to the top of the stack
    // O(1) because it only involves creating a new node and updating the top pointer
    void push(int x)
    {
        node* newNode = new node(x);
        newNode->next = top;
        top = newNode;
    }

    // Remove and return the top item from the stack
    // O(1) because it only involves updating the top pointer and deleting a node
    int pop()
    {
        if (empty()) {
            return 0;
        }

        int poppedValue = top->data;
        node* temp = top;
        top = top->next;
        delete temp;

        return poppedValue;
    }

    // Insert item x to stack after the current ith item from the top
    // O(i) where i is the index of insertion, as it may require traversing the stack to the (i-1)-th node
    void insertAt(int x, int i)
    {
        if (i < 0) {
            return;
        }

        node* newNode = new node(x);

        if (i == 0) {
            newNode->next = top;
            top = newNode;
            return;
        }

        node* current = top;
        for (int j = 0; j < i - 1 && current != nullptr; ++j) {
            current = current->next;
        }

        if (current == nullptr) {
            delete newNode;
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
};
