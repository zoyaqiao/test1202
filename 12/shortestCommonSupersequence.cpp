#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();
    str1 = " " + str1;
    str2 = " " + str2;
    vector<vector<int>> f(n + 10, vector<int>(m + 10));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i] == str2[j]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        }
    }
    string sb;
    int i = n; 
    int j = m;
    while (i > 0 || j > 0) {
        if (i == 0) sb.append(1, str2[j--]);
        else if (j == 0) sb.append(1, str1[i--]);
        else {
            if (str1[i] == str2[j]) {
                sb.append(1, str1[i]);
                i--;
                j--;
            } else if (f[i][j] ==f[i - 1][j] ){
                sb.append(1, str1[i--]);
            } else {
                sb.append(1, str2[j--]);
            }
        }
    }
    reverse(sb.begin(), sb.end());
    return  sb;
}

int main() {
    string s1 = "abac";
    string s2 = "cab";
    cout << shortestCommonSupersequence(s1, s2) << endl;
    return 0;
}
