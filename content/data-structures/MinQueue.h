struct MQueue {
    int tin, tout;
    deque<pair<int, int>> dq;
    MQueue() : tin(0), tout(0) {}
    void push(int val) {
        while (!dq.empty() && min(dq.back().first, val) == val) dq.pop_back();
        dq.push_back(pair(val, tin++));
    }
    void pop() {
        // assert(!dq.empty());
        if (dq.front().second == tout) dq.pop_front();
        tout++;
    }
    int front() {
        // assert(!dq.empty());
        return dq.front().first;
    }
};