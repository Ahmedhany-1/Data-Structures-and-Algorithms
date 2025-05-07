#include <iostream>
#include <cassert>
#include <climits>
#include <vector>	
#include <algorithm>
#include <sstream>
using namespace std;

/* Node destructor
    in struct Node we can add destructor to follw the node when it be destroyed 
    ~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
*/

/* add/remove nodes in vector for debuging
    add vector in class linkedlist to add/remove nodes you use
    and add tow function for add/remove nodes in private section

    vector<Node*> debug_data;
    void debug_add_node(Node *node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node *node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

*/

/* print and visualize linkedlist 

    void debug_print_node(Node *node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}

    void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}
*/

/* convert linkedlist to string for comparing string or anything in strings

    string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node *cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}
*/

/* Verify data integrity Function to check the integrity of Linkedlist

    void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
			return;
		}

		assert(head != nullptr);
		assert(tail != nullptr);
		assert(tail->next == nullptr);

		if (length == 1)
			assert(head == tail);
		else {
			assert(head != tail);

			if (length == 2)
				assert(head->next == tail);
			else if (length == 3) {
				assert(head->next);
				assert(head->next->next == tail);
			}
		}
		int len = 0;
		Node *prev = nullptr;
		for (Node *cur = head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == tail);	// last node is tail
	}
*/

/* Below 2 deletes prevent copy and assign to avoid this mistake

	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList &another) = delete;

	void debug_print_address() {
		for (Node *cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}
 */


/* void test1() {
	cout << "\n\ntest1\n";
     LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	// some actions
	list.print();

	string expected = "1 2 3";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
				<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
} */

/* void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	// some actions
	list.print();

	string expected = "1 2 3 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
				<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
} */

