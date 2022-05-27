#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct tree_node {
    int node_low, node_high;
    long long sum;
    long long add;
    long long min;
    long long max;
};

tree_node tree[1000000];

void initialise_tree(int, int, int);
void f_update(int);
void f_rupdate(int, int, int, long long);
int f_sor(int, int, int);
void f_add(int, int, int, long long);
int f_min(int, int, int);
int f_max(int, int, int);

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;
    initialise_tree(1, 1, n);
    int type;
    in >> type;
    while (type != 0) {
        if (type == 1) {
                long long index, value;
                in >> index >> value;
                f_rupdate(1, index + 1, index + 1, value);
        } else if (type == 2) {
                long long start, end, value;
                in >> start >> end >> value;
                f_add(1, start + 1, end + 1, value);
        } else if (type == 3) {
                long long start, end;
                in >> start >> end;
                out << f_sor(1, start + 1, end + 1) << endl;
        } else if (type == 4) {
                long long start, end;
                in >> start >> end;
                out << f_min(1, start + 1, end + 1) << endl;
        } else if (type == 5) {
                long long start, end;
                in >> start >> end;
                out << f_max(1, start + 1, end + 1) << endl;
        }
        in >> type;
    }
    return 0;
}

void initialise_tree(int node, int node_low, int node_high) {
    tree[node].node_low = node_low;
    tree[node].node_high = node_high;
    tree[node].max = 0;
    tree[node].min = 0;
    tree[node].sum = 0;
    tree[node].add = 0;
    if (node_low == node_high)
        return;
    long long last_in_left = (node_low + node_high) / 2;
    initialise_tree(2 * node, node_low, last_in_left);
    initialise_tree(2 * node + 1, last_in_left + 1, node_high);
}


void f_update(int node) {
    tree[2 * node].add += tree[node].add;
    tree[2 * node].sum += (tree[2 * node].node_high - tree[2 * node].node_low + 1) * tree[node].add;
    tree[2 * node].min += tree[node].add;
    tree[2 * node].max += tree[node].add;
    tree[2 * node + 1].add += tree[node].add;
    tree[2 * node + 1].sum += (tree[2 * node + 1].node_high - tree[2 * node + 1].node_low + 1) * tree[node].add;
    tree[2 * node + 1].min += tree[node].add;
    tree[2 * node + 1].max += tree[node].add;
    tree[node].add = 0;
}

void f_rupdate(int node, int node_low, int node_high, long long value) {
    if (node_low > node_high)
        return;
    if (tree[node].add != 0)
        f_update(node);
    if (tree[node].node_low == node_low && tree[node].node_high == node_high) {
        tree[node].add = 0;
        tree[node].sum = (tree[node].node_high - tree[node].node_low + 1) * value;
        tree[node].min = value;
        tree[node].max = value;
        return;
    }
    f_rupdate(2 * node, max(tree[2 * node].node_low, node_low), min(tree[2 * node].node_high, node_high), value);
    f_rupdate(2 * node + 1, max(tree[2 * node + 1].node_low, node_low), min(tree[2 * node + 1].node_high, node_high), value);
    tree[node].min = min(tree[2 * node].min, tree[2 * node + 1].min);
    tree[node].max = max(tree[2 * node].max, tree[2 * node + 1].max);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].add = 0;
}

int f_sor(int node, int node_low, int node_high) {
    if (node_low > node_high)
        return 0;
    if (tree[node].add != 0) f_update(node);
    if (tree[node].node_low == node_low && tree[node].node_high == node_high) {
        return tree[node].sum;
    }
    return f_sor(2 * node, max(tree[2 * node].node_low, node_low), min(tree[2 * node].node_high, node_high)) +
           f_sor(2 * node + 1, max(tree[2 * node + 1].node_low, node_low), min(tree[2 * node + 1].node_high, node_high));
}

void f_add(int node, int node_low, int node_high, long long value) {
    if (node_low > node_high)
        return;
    if (tree[node].add != 0)
        f_update(node);
    if (tree[node].node_low == node_low && tree[node].node_high == node_high) {
        tree[node].add = value;
        tree[node].sum += (tree[node].node_high - tree[node].node_low + 1) * value;
        tree[node].min += value;
        tree[node].max += value;
        return;
    }
    f_add(2 * node, max(tree[2 * node].node_low, node_low), min(tree[2 * node].node_high, node_high), value);
    f_add(2 * node + 1, max(tree[2 * node + 1].node_low, node_low), min(tree[2 * node + 1].node_high, node_high), value);
    tree[node].min = min(tree[2 * node].min, tree[2 * node + 1].min);
    tree[node].max = max(tree[2 * node].max, tree[2 * node + 1].max);
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

int f_min(int node, int node_low, int node_high) {
    if (node_low > node_high)
        return 1000000;
    if (tree[node].add != 0)
        f_update(node);
    if (tree[node].node_low == node_low && tree[node].node_high == node_high)
        return tree[node].min;
    return min(f_min(2 * node, max(tree[2 * node].node_low, node_low), min(tree[2 * node].node_high, node_high)),
               f_min(2 * node + 1, max(tree[2 * node + 1].node_low, node_low), min(tree[2 * node + 1].node_high, node_high)));
}

int f_max(int node, int node_low, int node_high) {
    if (node_low > node_high)
        return -1000000;
    if (tree[node].add != 0)
        f_update(node);
    if (tree[node].node_low == node_low && tree[node].node_high == node_high)
        return tree[node].max;
    return max(f_max(2 * node, max(tree[2 * node].node_low, node_low), min(tree[2 * node].node_high, node_high)),
               f_max(2 * node + 1, max(tree[2 * node + 1].node_low, node_low), min(tree[2 * node + 1].node_high, node_high)));
}
