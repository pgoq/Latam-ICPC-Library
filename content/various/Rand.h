#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// _64

int uniform(int l, int r) { // [l, r]
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}