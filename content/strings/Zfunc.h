/**
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 */
#pragma once
vector<int> ZFunc(const string& s) {
    int n = sz(s), a = 0, b = 0;
    vector<int> z(n, 0);
    if (!z.empty()) z[0] = 0;
    for (int i = 1; i < n; i++) {
        int end = i;
        if (i < b) end = min(i + z[i - a], b);
        while (end < n && s[end] == s[end - i]) ++end;
        z[i] = end - i; if (end > b) a = i, b = end;
    }
    return z;
}