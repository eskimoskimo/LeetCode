/*
base    [1, 7]
topping [3, 4]
target  10

base 1: = 1
base 1: +3 +4 = 8
base 1: +3x2 +4 = 11
base 7: = 7
base 7: +3 = 10 return
For each base, run dfs backtracking
*/
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int best = INT_MAX;
        int n = toppingCosts.size();
        auto isBetter = [&](int a, int b) {
            if (abs(a - target) == abs(b - target)) return a < b;
            return abs(a - target) < abs(b - target);
        };
        function<void(int,int)> dfs = [&](int cost, int i) {
            if (cost == target) best = target;
            if (best == target) return;
            if (isBetter(cost, best)) best = cost;
            if (i == n) return;
            if (cost > target) return;
            dfs(cost, i+1);
            dfs(cost + toppingCosts[i], i+1);
            dfs(cost + toppingCosts[i] * 2, i+1);
        };
        for (int cost : baseCosts) {
            dfs(cost, 0);
        }
        return best;
    }
};
