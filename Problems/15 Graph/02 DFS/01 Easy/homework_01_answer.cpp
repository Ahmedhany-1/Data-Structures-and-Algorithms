#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define get_shit_done freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout); 

class Solution {
    void dfs(int node, unordered_map<int, vector<int>>& mp, vector<int>& vis) {
        vis.emplace_back(node);

        for (auto& i : mp[node]) {
            dfs(i, mp, vis);
        }
    }
public:

    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < (int)pid.size(); ++i) {
            if (ppid[i] == 0) continue;
            mp[ppid[i]].emplace_back(pid[i]);
        }

        vector<int> ans;
        dfs(kill, mp, ans);
        
        return ans;
    }

};


int main() {
    get_shit_done
        vector<int> PID{1, 3, 10, 5}, PPID{3, 0, 5, 3};
    int killID = 1;

    Solution s1;
    vector<int> ans = s1.killProcess(PID, PPID, killID);
    for (auto& i : ans) cout << i << ' ';

}

/*

Input: PID = [1, 3, 10, 5], PPID = [3, 0, 5, 3], killID = 5
Output: [5, 10]
Explanation: Kill 5 will also kill 10.
     3
   /   \
  1     5
       /
      10


Input: PID = [1, 2, 3], PPID = [0, 1, 1], killID = 2
Output: [2]



*/