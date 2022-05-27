#include <iostream>
#include <vector>
using namespace std;

vector<long long> tree;

long long f_sor(long long node, long long node_low, long long node_high, long long query_low, long long query_high) {
    if(query_low <= node_low && node_high <= query_high) {
        return tree[node];
    }
    if(node_high < query_low || query_high < node_low) {
        return 0;
    }
    long long last_in_left = (node_low + node_high) / 2;
    long long sum =  f_sor(2 * node, node_low, last_in_left, query_low, query_high)
                     + f_sor(2 * node + 1, last_in_left + 1, node_high, query_low, query_high);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
    return sum;
}

void f_update(long long node, long long node_low, long long node_high, long long query_low, long long query_high, long long val) {
    if(query_low <= node_low && node_high <= query_high) {
        tree[node] += val;
        return;
    }
    if(node_high < query_low || query_high < node_low) {
        return;
    }
    long long last_in_left = (node_low + node_high) / 2;
    f_update(2 * node, node_low, last_in_left, query_low, query_high, val);
    f_update(2 * node + 1, last_in_left + 1, node_high, query_low, query_high, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

//long long super_f(long long node, long long node_low, long long node_high, long long query_low, long long query_high, long long value) {
//    if (query_low <= node_low && query_high >= node_high) {
//        if(value != -1) {
//            tree[node] += value;
//        }
//        return tree[node];
//    }
//    if (query_high < node_low || query_low > node_high) {
//        return 0;
//    }
//    long long last_in_left = (node_low + node_high) / 2;
//    long long sum = super_f(node * 2, node_low, last_in_left, query_low, query_high, value)
//                    + super_f(node * 2 + 1, last_in_left + 1, node_high, query_low, query_high, value);
//    tree[node] = tree[node * 2] + tree[node * 2 + 1];
//    return sum;
//}

int main() {
    long long n, q;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    while(n & (n - 1)) {
        a.push_back(0);
        n++;
    }
    cin >> q;
    tree.resize(n * 2);
    for (long long i = 0; i < n; i++) {
        tree[n + i] = a[i];
    }
    for (long long i = n - 1; i >= 1; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
    while (q != 0) {
        char type[100];
        cin >> type;
        if (type[0] == 'A') {
            long long index, value;
            cin >> index >> value;
            f_update(1, 0, n - 1, index, index, value);
        }
        else {
            long long low, high;
            cin >> low >> high;
            cout << f_sor(1, 0, n - 1, low, high - 1) << endl;
        }
        q--;
    }
    return 0;
}
