#include<iostream>
#include<queue>

using namespace std;

int n = 0;
int vert = 0;

bool* is_passed;
bool** adj;
int* mark;

queue<int> que;

void bfs(int node) {
    is_passed[node] = true;
    vert++;
    mark[node] = vert;
    que.push(node);
    int vertex;
    while(!que.empty()) {
        vertex = que.front();
        que.pop();
        for(int i = 0; i < n; i++)
            if(adj[vertex][i] && !is_passed[i]) {
                is_passed[i] = true;
                vert++;
                mark[i] = vert;
                que.push(i);
            }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    bool it;

    is_passed = new bool[n]{false};
    mark = new int[n]{0};
    adj = new bool * [n];

    for (int i = 0; i < n; i++) {
        adj[i] = new bool[n]{false};
        for (int j = 0; j < n; j++) {
            cin >> it;
            adj[i][j] = it;
        }
    }
    for (int i = 0; i < n; ++i)
        if (!is_passed[i]) bfs(i);
    for (int i = 0; i < n; ++i)
        cout << mark[i] << ' ';
    return 0;
}
