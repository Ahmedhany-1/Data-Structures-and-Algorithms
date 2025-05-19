#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;

/*
 * This is also a reachability problem. A rooted tree and we should get all its children
 *
 * Instead of building a corresponding map, we will work on the given structure
 * We need to map from id to its employee
 */


// Definition for Employee.
class Employee {
public:
	int id;
	int importance;
	vector<int> subordinates;
};

class Solution {
private:
	unordered_map<int, Employee*> id_to_emp;
public:

	int getImportance(vector<Employee*> employees, int id) {
		for (auto &emp : employees)
			id_to_emp[emp->id] = emp;

		return dfs(id);
	}
	// return sum of all the nodes uder this node
	// Why no visited array? No need for visited array in DAG, as no cycles :)
	int dfs(int id) {
		Employee *emp = id_to_emp[id];

		int result = emp->importance;
		for (auto &subEmp : emp->subordinates)
			result += dfs(subEmp);

		return result;
	}
};

int main() {

	return 0;
}
