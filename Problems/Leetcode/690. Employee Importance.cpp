#include "bits/stdc++.h"
using namespace std;


// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};


class Solution {
    unordered_map<int, Employee*> id_to_emp;
public:

    int getImportance(vector<Employee*> employees, int id) {
        for (auto& emp : employees)
            id_to_emp[emp->id] = emp;

        return dfs(id);
    }

    int dfs(int id) {
        Employee* emp = id_to_emp[id];
        int res = emp->importance;
        for (auto& i : emp->subordinates) {
            res += dfs(i);
        }

        return res;
    }
};

// why we not use vis array ? No need for vis array in DAG, No cycels.