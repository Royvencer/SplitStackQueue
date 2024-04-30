template <typename T>
class queueLL {
private:
    class node {
    public:
        T data;
        node* next;

        // Constructor for node
        node(T value) : data(value), next(nullptr) {}
    };

    node* front;  // Front of the queue
    node* rear;   // Rear of the queue

public:
    // Constructor

    queueLL() : front(nullptr), rear(nullptr) {}

    // Destructor
    // O(n) where n is the number of elements in the queue, as it involves deleting all nodes
    ~queueLL() {
        while (!empty()) {
            dequeue();
        }
    }

    // Add item to the back of the queue
    // O(1) because it only involves updating the rear pointer and creating a new node
    void enqueue(T x) {
        node* newNode = new node(x);

        if (empty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Remove and return the first item from the queue
    // O(1) because it only involves updating the front pointer and deleting a node
    T dequeue() {
        if (empty()) {
            return T();
        }

        T dequeuedValue = front->data;
        node* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
        }

        delete temp;

        return dequeuedValue;
    }

    // Check if the queue is empty
    // O(1) because it only involves checking if the front pointer is null
    bool empty() {
        return front == nullptr;
    }

    // Function to decimate the queue by removing every 10th element
    // O(n) where n is the number of elements in the queue, as it involves traversing the entire queue
    void decimate() {
        if (front == nullptr || front->next == nullptr) {
            return;
        }

        int count = 1;
        node* current = front;
        node* prev = nullptr;

        while (current != nullptr) {
            if (count % 10 == 0) {
                if (prev != nullptr) {
                    prev->next = current->next;
                }
                else {
                    front = current->next;
                }

                delete current;
                current = (prev != nullptr) ? prev->next : front;
            }
            else {
                prev = current;
                current = current->next;
                count++;
            }
        }

        rear = prev;

        if (rear != nullptr) {
            rear->next = nullptr;
        }
        else {
            front = nullptr;
        }
    }
};
