#pragma once
void floor_ranges(int n) {
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        // floor(n/y) has the same value for y in [l..r]
    }
}
void ceil_ranges(int n) {
    for (int l = 1, r; l <= n; l = r + 1) {
        int x = (n + l - 1) / l;
        if (x == 1) r = n;
        else r = (n - 1) / (x - 1);
        // ceil(n/y) has the same value for y in [l..r]
    }
}