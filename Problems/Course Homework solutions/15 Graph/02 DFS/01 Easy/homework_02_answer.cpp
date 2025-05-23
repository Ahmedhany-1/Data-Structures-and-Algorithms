#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;

    Employee(int id, int importance, vector<int> subordinates) : 
        id(id), importance(importance), subordinates(subordinates) {}
};


class Solution {
    unordered_map<int, Employee*> id_to_emp;

    // return sum of all the nodes uder this node
	// Why no visited array? No need for visited array in DAG, as no cycles :)

	int dfs(int id) {
		Employee *emp = id_to_emp[id];

		int result = emp->importance;
		for (auto &subEmp : emp->subordinates)
			result += dfs(subEmp);

		return result;
	}

public:
    int getImportance(vector<Employee*> employees, int id) {
        for (auto &emp : employees)
			id_to_emp[emp->id] = emp;

		return dfs(id);
    }
};


int main() {
    get_shit_done
    
    // Employee e1(1,5,{2,3}), e2(2,3,{}), e3(3,3,{});
    // vector<Employee*> employees = {&e1, &e2, &e3};
    // Solution s1;
    // int ans = s1.getImportance(employees, 1);
    // cout << ans;

    Employee e1(1,2,{5}), e2(5,-3,{});
    vector<Employee*> employees = {&e1, &e2};
    Solution s1;
    int ans = s1.getImportance(employees, 5);
    cout << ans;

}

/*
Input: employees = [[1,5,[2,3]],[2,3,[]],[3,3,[]]], id = 1
Output: 11
Explanation: Employee 1 has an importance value of 5 and has two direct subordinates: employee 2 and employee 3.
They both have an importance value of 3.
Thus, the total importance value of employee 1 is 5 + 3 + 3 = 11.

Input: employees = [[1,2,[5]],[5,-3,[]]], id = 5
Output: -3
Explanation: Employee 5 has an importance value of -3 and has no direct subordinates.
Thus, the total importance value of employee 5 is -3.
*/