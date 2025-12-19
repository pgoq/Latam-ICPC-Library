/**
 * Description: $ go[i][j] $ = length of the longest prefix of $s$ that is a suffix of $s[0..i]$ followed by the letter $j$ 
 * (i.e., the next matched prefix length if, at state $i$, we read letter $j$).
 */
#pragma once
int go[ms][sigma];
int val(char c) { return c - 'a'; }
void automaton(string& s) {
    for (int i = 0; i < sigma; i++) 
        go[0][i] = (i == val(s[0]));

    for (int i = 1, bdr = 0; i <= (int)s.size(); i++) {
        for (int j = 0; j < sigma; j++) {
            go[i][j] = go[bdr][j];
        }
        if (i < (int)s.size()) {
            go[i][val(s[i])] = i + 1;
            bdr = go[bdr][val(s[i])];
        }
    }
}