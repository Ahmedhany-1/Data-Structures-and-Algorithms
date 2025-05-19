#include<iostream>
#include<cassert>
using namespace std;

struct Node{
    int data{};
    Node *next{};

    Node(int data): data(data){}

    ~Node(){
        cout << "Destroy value: " << data << "\n";
    }

};
class Linkedlist{
    Node* head{};
    Node* tail{};
    int length{};

    Node* get_nth(int n) {
        int cnt = 0;
        for (Node* cur = head; cur ; cur = cur->next){
            if(++cnt == n){
                return cur;
            }
        }
        return nullptr;
    }
   
    void print_reverse(Node *head){
        // base case;
        if(head == nullptr) return;

        print_reverse(head->next);
        cout << head->data << ' ';
    }

public:
    Linkedlist(){
        head = tail = nullptr;
    }
    void print(){
        Node* tmp = head;
       /*  while(tmp != NULL){
            cout << tmp->data << ' ';
            tmp = tmp->next;
        }
        cout << '\n'; */
        if(length == 0) {
            cout << "List is empty..!\n";
            return;
        }
        for(Node* cur = head; cur ;  cur = cur->next) cout <<  cur ->data << ' ';
        cout << '\n';
    }
 
    void print_reverse(){
         if(length == 0) {
            cout << "List is empty..!\n";
            return;
        }
    
        print_reverse(head);
        cout << '\n';
    }

    void insert_end(int val){
        Node* newnode = new Node(val);
        if(!head) tail = head = newnode;
        else{
            tail->next = newnode;
            tail = newnode;
        } 
        ++length;            
    }
   
    int search(int val){
        int idx = 0;
         for (Node* cur = head; cur ; cur = cur->next , idx++){
            if(cur->data == val){
                return idx;
            }
        }
        return -1;
    }
    
    int improve_search(int val){
        int idx = 0;
        for (Node* cur = head, *prev = nullptr; cur; prev = cur , cur = cur->next , idx++){
            if(cur->data == val){   
                if(!prev)
                    return idx;
                swap(cur->data , prev->data);
                return idx - 1;
            }
        }
        return -1;
        
    }

    void delete_first(){
        assert(length > 0);
        Node *cur = head;
        head = head->next;
        delete cur;
        if(!head) tail = head;
        length--;

    }
    
    void delete_last(){
        assert(length > 0);
        if(length == 1) {
            delete_first();
            return; 
        }

        Node* prev = get_nth(length - 1);
        delete tail;
        tail = prev;
        tail->next = nullptr;
        length--;
    }
    
    void delete_nth(int n){
        if (n < 1 || n > length)
			cout << "Error. No such nth node\n";
		else if (n == 1)
			delete_first();
		else {
			// Connect the node before nth with node after nth
			Node* before_nth = get_nth(n - 1);
			Node* nth = before_nth->next;
			bool is_tail = nth == tail;
			// connect before node with after
			before_nth->next = nth->next;
			if (is_tail)
				tail = before_nth;
            delete nth; 
            length--;
		}
	}

    ~Linkedlist(){ // time: o(1) - memory: o(n) 
        while (head){
            Node* cur = head;
            head = head-> next;
            delete cur;
        }
    }

   ////////////////////////////// HomeWork Function /////////////////////////////////

    void insert_front(int val){ // time: o(1) - memory: o(1)
        Node* newnode = new Node(val);
        newnode->next = head;
        head = newnode;
        if(!tail) head = tail = newnode;
        length++;
    }
};

int main(){
    Linkedlist list;
	list.insert_front(6);
    list.print();
	list.insert_front(10);
    list.print();
	list.insert_front(8);
    list.print();
	list.insert_front(15);
    list.print();
    
    return 0;
}
