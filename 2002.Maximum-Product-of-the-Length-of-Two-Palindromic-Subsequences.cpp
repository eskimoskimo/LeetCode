/*
leetcodecom
s1: "l"
s2: "e"
aaaaa
*/
class Solution {
public:
    int maxProduct(string s) {
        int ans = 0;
        string s1, s2;
        dfs(s1, s2, s, 0, ans);
        return ans;
    }
    
    void dfs(string& s1, string& s2, string& s, int i, int& best) {
        if (i == s.size()) {
            if (isPalin(s1) && isPalin(s2)) {
                best = max(best, (int)s1.size() * (int)s2.size());
            }
            return;
        }
        s1.push_back(s[i]);
        dfs(s1, s2, s, i+1, best);
        s1.pop_back();

        s2.push_back(s[i]);
        dfs(s1, s2, s, i+1, best);
        s2.pop_back();

        dfs(s1, s2, s, i+1, best);
    }
    
    bool isPalin(string& s) {
        for (int i=0, j=s.size()-1; i < j; i++, j--) {
            if (s[i] != s[j]) return false;
        }
        return true;
    }
};
