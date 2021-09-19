/*
9/18/2021
n = 5
index       0     1     2     3     4     5
requests [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
take req[0]
balance
0 : -1
1 : 1

take req[1]
balance
1 : 0
0 : 0
...
Backtracking
dfs(start, handled req count)
if start == n
    if balance are all 0
        update ans with count
for each i, req from [start, last]
    [from, to] = req
    handle: balance[from]--, balance[to]++
    dfs(i+1, count+1)
    backtrack
    not handle: dfs(i+1, count)
*/
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int ans = 0;
        vector<int> balance(n);
        function<void(int, int)> dfs = [&](int i, int count) {
            if (i == requests.size()) {
                for (auto b : balance)
                    if (b != 0) return;
                ans = max(ans, count);
                return;
            }
            int from = requests[i][0], to = requests[i][1];
            if (from != to) dfs(i + 1, count);
            balance[from]--; balance[to]++;
            dfs(i + 1, count + 1);
            balance[from]++; balance[to]--;
        };
        dfs(0, 0);
        return ans;
    }
};
