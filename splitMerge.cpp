#include <iostream>
#include <fstream>
#include <string>
#include "queueLL.h"
#include "stackLL.h"
#include <chrono>

using namespace std;

template <class T>
class linkedList {
private:
    class node {
    public:
        T data;
        node* next;

        node(T value) : data(value), next(nullptr) {}
    };

    node* head;
    node* tail;

public:
    linkedList() : head(nullptr), tail(nullptr) {}

    ~linkedList() {
        clear();
    }

    void push_back(T value) {
        node* newNode = new node(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void print() {
        node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void split(linkedList<T>& left, linkedList<T>& right) {
        node* slow = head;
        node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            left.push_back(slow->data);
            slow = slow->next;
            fast = fast->next->next;
        }

        while (slow != nullptr) {
            right.push_back(slow->data);
            slow = slow->next;
        }

        clear();
    }

    void merge(linkedList<T>& left, linkedList<T>& right) {
        node* leftCurrent = left.head;
        node* rightCurrent = right.head;

        while (leftCurrent != nullptr && rightCurrent != nullptr) {
            if (leftCurrent->data < rightCurrent->data) {
                push_back(leftCurrent->data);
                leftCurrent = leftCurrent->next;
            }
            else {
                push_back(rightCurrent->data);
                rightCurrent = rightCurrent->next;
            }
        }

        // Append the remaining elements from left, if any
        while (leftCurrent != nullptr) {
            push_back(leftCurrent->data);
            leftCurrent = leftCurrent->next;
        }

        // Append the remaining elements from right, if any
        while (rightCurrent != nullptr) {
            push_back(rightCurrent->data);
            rightCurrent = rightCurrent->next;
        }
    }

    void slowSort() {
        if (head == nullptr || head->next == nullptr) {
            return;  // Already sorted if empty or has only one element
        }

        bool swapped;
    

        do {
            swapped = false;
            node* current = head;
            node* nextNode = head->next;

            while (nextNode != nullptr) {
                if (current->data > nextNode->data) {
                    // Swap values
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;

                    swapped = true;
                }

                current = nextNode;
                nextNode = nextNode->next;

            }
        } while (swapped);
    }


    void mergeSort() {
        // Implement merge sort
        if (head == nullptr || head->next == nullptr) {
            return;  // Already sorted if empty or has only one element
        }

        linkedList<T> left, right;
        split(left, right);

        left.mergeSort();
        right.mergeSort();

        merge(left, right);
        cout << "Merge Sort completed." << endl;

    }

    void loadFromFile(const string& filename) {
        ifstream inputFile(filename);
        T value;
        int count = 0;

        cout << "Loading data from file " << filename << "..." << endl;

        while (inputFile >> value) {
            push_back(value);
            ++count;

            // Print progress every 100,000 words (adjust as needed)
            if (count % 100000 == 0) {
                cout << "Loaded " << count << " words..." << endl;
            }
        }

        cout << "Loading complete. Total words loaded: " << count << endl;

        inputFile.close();
    }

    void writeToFile(const string& filename) {
        ofstream outputFile(filename);

        if (!outputFile.is_open()) {
            cerr << "Error: Unable to open file " << filename << " for writing." << endl;
            return;
        }

        node* current = head;

        cout << "Writing data to file " << filename << "..." << endl;

        while (current != nullptr) {
            outputFile << current->data << " ";
            current = current->next;
        }

        cout << "Writing complete." << endl;

        outputFile.close();
    }

    void clear() {
        while (head != nullptr) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;  // Reset tail to nullptr after clearing the list
    }

    bool empty() const {
        return head == nullptr;
    }
};



int main()
{
    linkedList<double> A;

    // Implement a push_back method that adds a given item to the back of the list.
    // Must run in O(1) time.
    A.push_back(450);
    A.push_back(320);
    A.push_back(750);
    A.push_back(510);
    A.push_back(720);
    A.push_back(230);
    A.push_back(290);
    A.push_back(240);
    A.push_back(320);
    A.push_back(820);
    A.push_back(530);
    A.push_back(210);



    // Implement a simple print method to test your list.
    A.print(); //450 320 750 510 720 230 290 240 320 820 530 210
 
    linkedList<double> left;
    linkedList<double> right;

    // Split the contents of list A evenly into the two given (initially empty) lists.
    // If the number of items in the list is odd, put the extra item in the first list.
    // Must run in O(n) time, where n is the total number of items in the list.
    A.split(left, right);

    A.print(); //(empty)
    left.print(); //450 320 750 510 720 230
    right.print(); //290 240 320 820 530 210

    // Implement a sorting routine for your list
    // You may implement any elementary sorting algorithm.
auto startSlowSort = chrono::high_resolution_clock::now();
        left.slowSort();
        right.slowSort();
        auto stopSlowSort = chrono::high_resolution_clock::now();
        auto durationSlowSort = chrono::duration_cast<chrono::microseconds>(stopSlowSort - startSlowSort);

        cout << "Time taken by slowSort: " << durationSlowSort.count() << " microseconds" << endl;

        // Timing code for mergeSort
        auto startMergeSort = chrono::high_resolution_clock::now();
        left.mergeSort();
        right.mergeSort();
        auto stopMergeSort = chrono::high_resolution_clock::now();
        auto durationMergeSort = chrono::duration_cast<chrono::microseconds>(stopMergeSort - startMergeSort);

        cout << "Time taken by mergeSort: " << durationMergeSort.count() << " microseconds" << endl;
    left.print(); //230 320 450 510 720 750
    right.print(); //210 240 290 320 530 820

    // Implement a method that takes 2 sorted lists and merges them
    // into your (initially empty) list to create one sorted list.
    // Must run in O(n) time, where n is the total number of items in the two given lists.
    A.merge(left, right);

    left.print(); //(empty)
    right.print(); //(empty)
    A.print(); //210 230 240 290 320 320 450 510 530 720 750 820

    // Add a methods to load your list from a file, and write your list to a file
    linkedList<std::string> B;
    linkedList<std::string> C;

    // Timing code for loading from file for B
    auto startLoadFileB = chrono::high_resolution_clock::now();
    B.loadFromFile("whale.txt");
    auto stopLoadFileB = chrono::high_resolution_clock::now();
    auto durationLoadFileB = chrono::duration_cast<chrono::microseconds>(stopLoadFileB - startLoadFileB);

    cout << "Time taken to load file for B: " << durationLoadFileB.count() << " microseconds" << endl;

    // Timing code for slowSort
    auto startSlowSortB = chrono::high_resolution_clock::now();
    B.slowSort();
    auto stopSlowSortB = chrono::high_resolution_clock::now();
    auto durationSlowSortB = chrono::duration_cast<chrono::microseconds>(stopSlowSortB - startSlowSortB);

    cout << "Time taken by slowSort for B: " << durationSlowSortB.count() << " microseconds" << endl;

    // Timing code for writing to file for B
    auto startWriteFileB = chrono::high_resolution_clock::now();
    B.writeToFile("slowSortedWhale.txt");
    auto stopWriteFileB = chrono::high_resolution_clock::now();
    auto durationWriteFileB = chrono::duration_cast<chrono::microseconds>(stopWriteFileB - startWriteFileB);

    cout << "Time taken to write file for B: " << durationWriteFileB.count() << " microseconds" << endl;

    // Timing code for loading from file for C
    auto startLoadFileC = chrono::high_resolution_clock::now();
    C.loadFromFile("whale.txt");
    auto stopLoadFileC = chrono::high_resolution_clock::now();
    auto durationLoadFileC = chrono::duration_cast<chrono::microseconds>(stopLoadFileC - startLoadFileC);

    cout << "Time taken to load file for C: " << durationLoadFileC.count() << " microseconds" << endl;

    // Timing code for mergeSort
    auto startMergeSortC = chrono::high_resolution_clock::now();
    C.mergeSort();
    auto stopMergeSortC = chrono::high_resolution_clock::now();
    auto durationMergeSortC = chrono::duration_cast<chrono::microseconds>(stopMergeSortC - startMergeSortC);

    cout << "Time taken by mergeSort for C: " << durationMergeSortC.count() << " microseconds" << endl;

    // Timing code for writing to file for C
    auto startWriteFileC = chrono::high_resolution_clock::now();
    C.writeToFile("mergeSortedWhale.txt");
    auto stopWriteFileC = chrono::high_resolution_clock::now();
    auto durationWriteFileC = chrono::duration_cast<chrono::microseconds>(stopWriteFileC - startWriteFileC);

    cout << "Time taken to write file for C: " << durationWriteFileC.count() << " microseconds" << endl;

    return 0;
}