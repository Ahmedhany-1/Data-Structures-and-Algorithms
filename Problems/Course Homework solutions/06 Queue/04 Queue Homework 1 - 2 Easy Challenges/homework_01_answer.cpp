#include <iostream>
#include <cassert>
using namespace std;

class Deque {
    int size { };
    int front { 0 };
    int rear { 0 };
    int added_elements { };
    int *array { };

public:
    Deque(int size) :
            size(size) {
        array = new int[size];
    }

    ~Deque() {
        delete[] array;
    }

    int next(int pos) {
        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
        //return (pos + 1) % size;	//  Or shorter way
    }

    int back(int pos) {
        --pos;
        if (pos < 0) pos = size - 1;
        return pos;
    }

    void enqueue_back(int value) {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }
    int dequeue_front() {
        assert(!isEmpty());
        int value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }

    void enqueue_front(int value) {
        assert(!isFull());
        front = back(front);
        array[front] = value;
        added_elements++;
    }
    int dequeue_back() {
        assert(!isEmpty());
        rear = back(rear);
        int val = array[rear];
        -- added_elements;
        return val;
    }

    void display() {
        if (isFull())
            cout << "full";
        else if (isEmpty()) {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";

        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n\n";
    }

    int isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};

int main() {
    Deque q(6);
    q.enqueue_front(3);
    q.enqueue_front(2);
    q.enqueue_back(4);
    q.enqueue_front(1);
    q.display();
    cout << q.dequeue_back() << endl;
    q.display();
    cout << q.dequeue_front() << endl;
    q.display();
    cout << q.dequeue_back() << endl;
    cout << q.dequeue_front() << endl;
    q.enqueue_back(7);
    q.display();


    return 0;
}

