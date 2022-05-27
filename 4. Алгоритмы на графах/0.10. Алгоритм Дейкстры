#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main()
{
    long long n, m;
    in >> n >> m;

    vector<vector<pair<long long, long long>>> sides(n);

    long long u, v, w;
    for (long long i = 0; i < m; ++i) {
        in >> u >> v >> w;
        sides[u - 1].push_back(make_pair(v - 1, w));
        sides[v - 1].push_back(make_pair(u - 1, w));
    }

    long long* action_course = new long long[n];
    for (long long i = 0; i < n; ++i)
        action_course[i] = INT64_MAX;

    priority_queue<pair<long long, long long>,
            vector<pair<long long, long long>>,
            greater<pair<long long, long long>>> q;

    q.push(make_pair(0l, 0l));
    action_course[0] = 0l;

    while (!q.empty())
    {
        pair<long long, long long> curr = q.top();
        q.pop();
        long long first = curr.first;
        long long second = curr.second;

        if (action_course[second] < first) continue;
        for (pair<long long, long long> side : sides[second])
        {
            long long f = side.first;
            long long s = side.second;

            long long dst = first + s;
            if (dst < action_course[f])
            {
                action_course[f] = dst;
                q.push(make_pair(dst, f));
            }
        }
    }
    out << action_course[n - 1];
    out.close();
}
