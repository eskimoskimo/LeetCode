/*
9/17/2021
- binar
- at most 3 x 3
Flatten, use bit mask
0 0
0 1

state= 0001
update (1,0) -> flip (1,0) (0,0) (-1,0) (1,1) (1,-1)
bit 1*n + 0 xor
mask = 1011
~mask= 0100
1010
update (0,1)
0111
update (1,1)
0000

0001

0000

Bidirectional BFS

seen {0001, 0000}
s1 {0001}
s2 {0000}

while (true)
    for each state in s1
        for i0 in [1,m]
            for j0 in [1,n]
                mask = 0
                for di, dj in dirs
                    i = i0 + di
                    j = j0 + dj
                    if out of bound, skip
                    int k = i * n + j + 1;
                    mask |= 1 << k;
                next = state ^ mask
                if next is seen continue
                if next is 0, return level + 1
                seen[next] = true
                insert next into s
    level++

*/
class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        auto getMasks = [&]() {
            vector<int> masks;
            vector<pair<int, int>> dirs {{0,0}, {0,1}, {1,0}, {0,-1}, {-1,0}};
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    int mask = 0;
                    for (auto& [dx, dy] : dirs) {
                        int x = i + dx, y = j + dy;
                        if (x < 0 || x == m || y < 0 || y == n) continue;
                        int k = x * n + y;
                        mask |= (1 << k);
                    }
                    //cout << bitset<4>(mask).to_string() << " ";
                    masks.push_back(mask);
                }
            }
            return masks;
        };
        auto masks = getMasks();
        auto toMask = [&]() {
            int mask = 0;
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    if (mat[i][j])
                        mask |= (1 << (i * n + j));
            return mask;
        };
        int state = toMask();
        if (state == 0) return 0;
        queue<int> q;
        q.push(state);
        vector<bool> seen(1 << (m*n));
        seen[state] = true;
        int steps = 0;
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                auto state = q.front(); q.pop();
                for (int mask : masks) {
                    auto next = state ^ mask;
                    if (next == 0) return steps + 1;
                    if (seen[next]) continue;
                    seen[next] = true;
                    q.push(next);
                }
            }
            steps++;
        }
        return -1;
    }
};
