
#pragma once
int trie[ms][sigma], fail[ms], terminal[ms], superfail[ms];
bool present[ms];
int z = 1;

int val(char c) { return c - 'a'; }

void add(string& p) {
    int cur = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        int& nxt = trie[cur][val(p[i])];
        if (nxt == 0) nxt = z++;
        cur = nxt;
    }
    present[cur] = true;
    terminal[cur]++;
}

void build() {
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
        int on = q.front();
        for (int i = 0; i < sigma; i++) {
            int& to = trie[on][i];
            int f = (on == 0 ? 0 : trie[fail[on]][i]);
            int sf = (present[f] ? f : superfail[f]);
            if (!to) {
                to = f;
            }
            else {
                fail[to] = f;
                superfail[to] = sf;
                // merge infos (ex: terminal[to] += terminal[f])
                q.push(to);
            }
        }
    }
}

void search(string& s) {
    int cur = 0;
    for (char c : s) {
        cur = trie[cur][val(c)];
        // process infos on current node (ex: ocurrences += terminal[cur])
    }
}