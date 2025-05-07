#include <iostream>
#include <cassert>

using namespace std;

class Vector {
private:
    int *arr{nullptr};
    int size{0};            // user size
    int capacity{};        // actual size

    void expand_capacity() {
        // Double the actual array size
        capacity *= 2;
        cout << "Expand capacity to "
             << capacity << "\n";
        int *arr2 = new int[capacity]{};
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i];    // copy data

        swap(arr, arr2);
        delete[] arr2;
    }

public:
    Vector(int size) :
            size(size) {
        if (size < 0)
            size = 1;
        capacity = size + 10;
        // The actual size array will
        // be bigger than needed
        arr = new int[capacity]{};
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    int get_size() {
        return size;
    }

    int get(int idx) {
        assert(0 <= idx && idx < size);
        return arr[idx];
    }

    void set(int idx, int val) {
        assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

    void print() {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    int find(int value) {
        for (int i = 0; i < size; ++i)
            if (arr[i] == value)
                return i;
        return -1;    // -1 for NOT found
    }

    int get_front() {
        return arr[0];
    }

    int get_back() {
        return arr[size - 1];
    }

    void push_back(int value) {
        // we can't add any more
        if (size == capacity)
            expand_capacity();
        arr[size++] = value;
    }

    void right_rotate() {
        if(size <= 1)
            return;
        for (int i = size - 2; i >= 0; --i) {
            swap(arr[i], arr[i + 1]);
        }
    } //homework_01_answer
    void right_rotate_v2() {
        if(size <= 1)
            return ;
        int val = arr[size - 1];
        for (int i = size - 2; i >= 0; --i)
            arr[i + 1] = arr[i];
        arr[0] = val;
    } //homework_01_answer

    void left_rotate() {
        for (int i = 0; i < size - 1; i++)
            swap(arr[i + 1], arr[i]);
    } //homework_02_answer
    void left_rotate_v2() {
       int val = arr[0];
       for(int i = 0 ; i < size-1 ; ++i)
           arr[i] = arr[i+1];
       arr[size - 1] = val;
    } //homework_02_answer

    void right_rotate(int times) {
        times %= size;
        while (times--)
            right_rotate();
    }//homework_03_answer

    int pop(int idx) {
        assert(idx >= 0 && idx < size);
        int val = arr[idx];
        for (int i = idx; i < size - 1; ++i)
            swap(arr[i], arr[i + 1]);
        size--;
        return val;
    } //homework_04_answer
    int pop_v2(int idx) {
        assert(idx >= 0 && idx < size);
        int val = arr[idx];
        for (int i = idx; i < size - 1; ++i)
            arr[i] = arr[i+1];
        size--;
        return val;
    } //homework_04_answer

    int find_transposition(int value) {
        if(arr[0] == value)
            return 0;
        for(int i = 1 ; i < size ;++i) {
            if (arr[i] == value) {
                swap(arr[i], arr[i - 1]);
                return i -1;
            }
        }
        return -1;
    } //homework_05_answer

};

int main() {
    int n = 1;
    Vector v(n);
    v.set(0, 0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    cout << "Vector befor any changes: \n";
    v.print();

    cout << "Vector after right rotate: \n";
    v.right_rotate();
    v.print();

    cout << "Vector after left rotate: \n";
    v.left_rotate();
    v.print();

    cout << "Vector after right rotate for times: \n";
    v.right_rotate(6);
    v.print();

    cout << "Vector after delete element: \n";
    cout << v.pop(2) << '\n';
    v.print();

    cout << "Vector after transport element if we find it: \n";
    cout << v.find_transposition(3) << '\n';
    v.print();

    return 0;
}
