#pragma once

template <class T, class Priority = int>
class priorityQueueLL
{
private:
    class node
    {
    public:
        T data;
        Priority priority;
        node* next;

        // Constructor for node
        node(T value, Priority prio) : data(value), priority(prio), next(nullptr) {}
    };

    node* head;  // Head of the priority queue

public:
    // Constructor
    priorityQueueLL() : head(nullptr) {}

    // Destructor
    ~priorityQueueLL()
    {
        // Take care of memory leaks by deleting all nodes
        while (!empty()) {
            extractMin();  // O(1) because it only involves removing the head
        }
    }

    // Check if the priority queue is empty
    bool empty()
    {
        return head == nullptr;
    }

    // Add item with priority to the priority queue
    // O(n) in the worst case, where n is the number of elements in the priority queue.
    void insert(T x, Priority priority)
    {
        node* newNode = new node(x, priority);

        // Special case: insert at the beginning
        if (empty() || priority < head->priority) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // General case: insert in the middle or at the end
        node* current = head;
        while (current->next != nullptr && current->next->priority <= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Remove and return the item with the smallest priority
    // O(1) because it only involves removing the head
    T extractMin()
    {
        if (empty()) {
            // Handle underflow (priority queue is empty)
            
            return T();
        }

        T minValue = head->data;
        node* temp = head;

        head = head->next;
        delete temp;

        return minValue;
    }
};
