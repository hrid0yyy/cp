// Optimized Mex for Small Values
int mex(const vector<int>& arr, int max_val) {
    vector<bool> present(max_val + 1, false);
    for (int x : arr) {
        if (x >= 0 && x <= max_val) {
            present[x] = true;
        }
    }
    for (int i = 0; i <= max_val; i++) {
        if (!present[i]) {
            return i;
        }
    }
    return max_val + 1;
}


// Mex in Dynamic Scenarios
int main() {
    set<int> s;
    vector<int> queries = {0, 1, 2, 4}; // Example: insert these numbers
    int mex = 0;
    for (int x : queries) {
        s.insert(x);
        while (s.count(mex)) {
            mex++;
        }
        cout << "Mex after inserting " << x << ": " << mex << "\n";
    }
    return 0;
}
