#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char* s, char* p) 
{
    int m = strlen(s);
    int n = strlen(p);
    bool dp[m + 1][n + 1];
    
    // Initialize the dp table with false values
    memset(dp, 0, sizeof(dp));
    
    // An empty pattern matches an empty string
    dp[0][0] = true;
    
    // Handle patterns like a*, a*b*, a*b*c* that can match an empty string
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }
    
    // Fill the dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2]; // Case where '*' represents zero occurrence of the preceding element
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] |= dp[i - 1][j];
                }
            }
        }
    }
    
    // The result is in the cell dp[m][n]
    return dp[m][n];
}

void testRegexMatching(const char* s, const char* p, bool expected) {
    bool result = isMatch((char*)s, (char*)p);
    printf("String: \"%s\", Pattern: \"%s\"\n", s, p);
    printf("Expected: %s, Got: %s\n", 
           expected ? "true" : "false", 
           result ? "true" : "false");
    printf("%s\n\n", result == expected ? "PASSED" : "FAILED");
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
