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
    void delete_even_positions(){
        if(length < 2) return;
        int cnt = 1;
        for(auto cur = head ; cur ; cur = cur->next , cnt++){
            if(cnt % 2 == 0){
                cur = delete_and_link_utility(cur);
                if(!cur->next) tail = cur;
            }
        }
    }
    void delete_odd_positions() {
        insert_front(-1);	// dummy node
        delete_even_positions();
        delete_front();
    }
};

int main() {
    freopen("out.txt", "w", stdout);

    LinkedList list;

// Test case 1: Empty list
    list.delete_even_positions();
    list.delete_odd_positions();

// Test case 2: Single-node list
    list.insert_end(1);
    list.delete_even_positions();  // Should do nothing
    list.print_reversed();         // Output: 1
    list.delete_odd_positions();   // Should delete the single node
    list.print_reversed();         // Output: (empty)

// Test case 3: List with multiple nodes
    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.delete_even_positions();  // Should remove 2 and 4
    list.print_reversed();         // Output: 3 1
    list.insert_end(5);
    list.insert_end(6);
    list.delete_odd_positions();   // Should remove 1, 3, and 5
    list.print_reversed();         // Output: 6 3

    return 0;
}