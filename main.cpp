#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        const int m = s.length();
        const int n = p.length();
        // dp[i][j] := true if s[0..i) matches p[0..j)
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true;

        auto isMatch = [&](int i, int j) -> bool {
            return j >= 0 && p[j] == '.' || s[i] == p[j];
        };

        for (int j = 0; j < p.length(); ++j)
            if (p[j] == '*' && dp[0][j - 1])
                dp[0][j + 1] = true;

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (p[j] == '*') {
                    const bool noRepeat = dp[i + 1][j - 1];  // Min index of '*' is 1
                    const bool doRepeat = isMatch(i, j - 1) && dp[i][j + 1];
                    dp[i + 1][j + 1] = noRepeat || doRepeat;
                } else if (isMatch(i, j)) {
                    dp[i + 1][j + 1] = dp[i][j];
                }

        return dp[m][n];
    }
};

void testRegexMatching(const string& s, const string& p, bool expected) {
    Solution solution;
    bool result = solution.isMatch(s, p);
    cout << "String: \"" << s << "\", Pattern: \"" << p << "\"" << endl;
    cout << "Expected: " << (expected ? "true" : "false") 
         << ", Got: " << (result ? "true" : "false") << endl;
    cout << (result == expected ? "PASSED" : "FAILED") << endl << endl;
}

int main() {
    // Test Case 1
    testRegexMatching("aa", "a", false);

    // Test Case 2
    testRegexMatching("aa", "a*", true);

    // Test Case 3
    testRegexMatching("ab", ".*", true);

    // Additional Test Cases
    testRegexMatching("mississippi", "mis*is*p*.", false);
    testRegexMatching("aab", "c*a*b", true);
    testRegexMatching("", ".*", true);

    return 0;
}
