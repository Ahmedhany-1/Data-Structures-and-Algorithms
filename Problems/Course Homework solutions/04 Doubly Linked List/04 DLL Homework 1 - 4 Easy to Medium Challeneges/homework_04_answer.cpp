#include <iostream>
using namespace std;

struct Node{
    int data{};
    Node *next{};
    Node *prev{};

    Node(int data) : data(data){}
};

class LinkedList{
private:
    Node *head{};
    Node *tail{};
    int length = 0;
public:
    LinkedList(){}

    void print_reversed() {
        for (auto cur = tail; cur; cur = cur->prev)
            cout << cur->data << ' ';
        cout << endl;
    }

    void link(Node *first , Node *second){
        if(first)
            first->next = second;
        if(second)
            second->prev = first;
    }

    void insert_end(int data){
        length++;
        Node *item = new Node(data);
        if(!head) head = tail = item;
        else{
            link(tail , item);
            tail = item;
        }
    }

    void insert_front(int data){
        length++;
        Node *item = new Node(data);
        if(!head) head = tail = item;
        else{
            link(item , head);
            head = item;
        }
    }

    void embed_after(Node* before , int value){
        length++;
        Node* middle = new Node(value);
        Node* after = before->next;
        link(before , middle);
        link(middle , after);
    }

    void insert_sorted(int value){
        if(!length || head->data >= value){
            insert_front(value);
            return ;
        }
        if(tail->data <= value){
            insert_end(value);
            return ;
        }
        for(auto cur = head ; cur ; cur = cur->next){
            if(cur->data >= value){
                embed_after(cur->prev , value);
                break;
            }
        }
    }

    void delete_front(){
        if(!head) return;
        if(length == 1){
            delete head;
            head = tail = nullptr;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        length--;
    }

    void delete_end(){
        if(length < 2){
            delete_front();
        }
        else{
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }

    }

    Node* delete_and_link_utility(Node *cur){
        link(cur->prev , cur->next);
        Node *ret = cur -> prev;
        delete cur;
        length--;
        return ret;
    }

    void delete_node_with_key(int value){
        if(!length) return;
        if(head-> data == value) delete_front();
        else{
            for(auto cur = head; cur ; cur = cur -> next){
                if(cur->data == value){
                    cur = delete_and_link_utility(cur);
                    if(cur->next == nullptr) tail = cur;
                    break;
                }
            }
        }
    }
    int get_length(){
        return length;
    }

    ~LinkedList() {
        while (head) {
            delete_front();
        }
    }
// =============================== HW ====================================================
    bool is_palindrome(){
        if(length < 2) return 1;
        for(auto front = head , last = tail; front ; front = front-> next , tail = tail->prev){
            if(front->data != last->data)
                return 0;
            if(front->next == last->prev)
                break;
        }
        return 1;
    }

};

int main() {
    freopen("out.txt", "w", stdout);

    LinkedList list;

// Test case 1: Empty list
    cout << list.is_palindrome() << endl; // 1

// Test case 2: Single-node list
    list.insert_end(1);
    cout << list.is_palindrome() << endl; // 1

// Test case 3: Odd-length palindrome
    list.insert_end(2);
    list.insert_end(1);
    cout << list.is_palindrome() << endl; // 1

// Test case 4: Even-length palindrome
    list.insert_end(2);
    cout << list.is_palindrome() << endl; // 0

// Test case 5: Non-palindrome
    list.insert_end(3);
    cout << list.is_palindrome() << endl; // 0

    return 0;
}