#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
using namespace std;
#define ll long long
#define el '\n'
// simple trick to avoid re-changing the class
typedef int type;

class Stack {
private:
    int size { };
    int top { };
    type* array { };

    void rec(int i) {
        if (i < 0) return;
        array[i + 1] = array[i];
        rec(i - 1);
    }
public:
    Stack(int size) :
            size(size), top(-1) {
        array = new type[size];
    }

    ~Stack() {
        delete[] array;
    }

    void push(type x) {
        assert(!isFull());
        array[++top] = x;
    }

    type pop() {
        assert(!isEmpty());
        return array[top--];
    }

    type peek() {
        assert(!isEmpty());
        return array[top];
    }

    int isFull() {
        return top == size - 1;
    }

    int isEmpty() {
        return top == -1;
    }

    void display() {
        for (int i = top; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";
    }

    void insert_at_bottom(int x) {
        assert(!isFull());
        for (int i = top; i >= 0; i--) {
            array[i + 1] = array[i];
        }
        array[0] = x;
        top++;
    }
    void insert_at_bottom_2(int x) {
        rec(top); // shift_right
        array[0] = x;
        top++;
    }
    void reverse() {
        // base case
        if (isEmpty())return;
        int var = pop();
        reverse();
        insert_at_bottom(var);
    }

};

vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> s;
        vector<int> ans(n);
        s.push(n - 1) , ans[n-1] = -1;
        for (int i = n - 2; i >= 0; i--) {
            while (!s.empty() && temperatures[s.top()] <= temperatures[i]) s.pop();
            ans[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }
        return ans;
};

vector<int> dailyTemperatures_v2(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> s;
        vector<int> ans(n);
        s.push(temperatures[n - 1]) , ans[n-1] = -1;
        for (int i = n - 2; i >= 0; i--) {
            while (!s.empty() && s.top() <= temperatures[i]) s.pop();
            ans[i] = s.empty() ? -1 : s.top();
            s.push(temperatures[i]);
        }
};

int main() {


    return 0;
}

