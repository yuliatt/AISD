#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const int M = 100500, I = 1e9, E = 1e-9;
pair <int, int> houses[M];
vector <pair <int, double>> graph[M];
int parent[M];
double result[M];
int counterStart = -1, counterEnd = -1;
set <pair <double, int>> dijkstra;

void algDijkstra();
pair <int, int> coordinates(int);
double getLength(pair <int, int>, pair <int, int>);
int inCoordinates (pair <int, int>, pair <int, int>, pair <int, int>);
bool isLine(pair <int, int>, pair <int, int>, pair <int, int>);
bool secW (int, int, int, int);
bool sec (pair <int, int>, pair <int, int> , pair <int, int>, pair <int, int>);
bool s(pair <int, int>, pair <int, int>, pair <int, int>, pair <int, int>);
void adding(int, int, int);
void answerForm(vector <pair <int, int>>&);
void edges(int);
void solution(int);

ifstream fin("input.in");
ofstream fout("output.out");

int main()
{

    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> houses[i].first >> houses[i].second;
        if (houses[i] == make_pair(0, 0)) counterStart = i;
        if (houses[i] == make_pair(95, 95)) counterEnd = i;
    }
    edges(n);
    solution(n);
    return 0;
}

void algDijkstra()
{
    for (double & i : result)
        i = I;
    result[0] = 0;
    dijkstra.insert(make_pair(0, 0));
    while (!dijkstra.empty())
    {
        pair<double, int> currentV = *dijkstra.begin();
        int v = currentV.second;
        dijkstra.erase(dijkstra.begin());

        for (auto x : graph[currentV.second])
        {
            int next = x.first;
            double add = x.second;
            if (result[v] + add + E >= result[next])
                continue;
            dijkstra.erase(make_pair(result[next], next));
            result[next] = result[v] + add;
            dijkstra.insert(make_pair(result[next], next));
            parent[next] = v;
        }
    }
}

pair <int, int> coordinates(int coord)
{
    if (coord == 0) return make_pair(0, 0);
    if (coord == 1) return make_pair(100, 100);
    int index = (coord - 2) % 4;
    pair <int, int> res = houses[(coord - 2) / 4];
    if (!index) return res;
    if (index == 1) return make_pair(res.first, res.second + 5);
    if (index == 2) return make_pair(res.first + 5, res.second + 5);
    if (index == 3) return make_pair(res.first + 5, res.second);
    return make_pair(0, 0);
}

double getLength(pair <int, int> x, pair <int, int> y)
{
    return sqrt((x.first - y.first) * (x.first - y.first) +
                (x.second - y.second) * (x.second - y.second));
}

int inCoordinates (pair <int, int> a, pair <int, int> b, pair <int, int> c)
{
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

bool isLine(pair <int, int> a, pair <int, int> b, pair <int, int> c)
{
    return !inCoordinates(a, b, c);
}

bool secW (int a, int b, int c, int d)
{
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    if (max(a,c) <= min(b,d)) return true;
    return false;
}

bool sec (pair <int, int> a, pair <int, int> b, pair <int, int> c, pair <int, int> d)
{
    if (secW(a.first, b.first, c.first, d.first)
        && secW(a.second, b.second, c.second, d.second)
        && inCoordinates(a, b, c) * inCoordinates(a, b, d) <= 0
        && inCoordinates(c, d, a) * inCoordinates(c, d, b) <= 0)
        return true;
    return false;
}

bool s(pair <int, int> a, pair <int, int> b, pair <int, int> c, pair <int, int> d)
{
    if (a == c) return false;
    if (b == c) return false;
    if (a == d) return false;
    if (b == d) return false;
    return sec(a, b, c, d);
}

void adding(int x, int y, int n)
{
    pair <int, int> _x = coordinates(x);
    pair <int, int> _y = coordinates(y);
    for (int i = 2; i < n; i += 4)
    {
        if (s(_x, _y, coordinates(i), coordinates(i + 1)) ||
            s(_x, _y, coordinates(i + 1), coordinates(i + 2)) ||
            s(_x, _y, coordinates(i + 2), coordinates(i + 3)) ||
            s(_x, _y, coordinates(i + 3), coordinates(i)))
            return;
    }
    graph[x].emplace_back(y, getLength(_x, _y));
    graph[y].emplace_back(x, getLength(_x, _y));
}

void answerForm(vector <pair <int, int>>& way)
{
    vector <pair <int, int>> newPath;
    newPath.push_back(way[0]);
    int length = way.size();
    int i = 0, j = 1;
    while (length > i + 1)
    {
        while (j < length && isLine(way[i], way[i + 1], way[j]))
            j++;
        i = j - 1;
        newPath.push_back(way[j - 1]);
    }
    way = newPath;
}

void edges(int n)
{
    for (int i = 0; i < n; i++)
    {
        graph[2 + 4 * i].emplace_back(3 + 4 * i, 5);
        graph[3 + 4 * i].emplace_back(2 + 4 * i, 5);
        graph[3 + 4 * i].emplace_back(4 + 4 * i, 5);
        graph[4 + 4 * i].emplace_back(3 + 4 * i, 5);
        graph[4 + 4 * i].emplace_back(5 + 4 * i, 5);
        graph[5 + 4 * i].emplace_back(4 + 4 * i, 5);
        graph[5 + 4 * i].emplace_back(2 + 4 * i, 5);
        graph[2 + 4 * i].emplace_back(5 + 4 * i, 5);
    }

    if (counterStart != -1)
    {
        graph[0].emplace_back(3 + 4 * counterStart, 5);
        graph[3 + 4 * counterStart].emplace_back(0, 5);
        graph[0].emplace_back(5 + 4 * counterStart, 5);
        graph[5 + 4 * counterStart].emplace_back(0, 5);
    }

    if (counterEnd != -1)
    {
        graph[1].emplace_back(3 + 4 * counterEnd, 5);
        graph[3 + 4 * counterEnd].emplace_back(1, 5);
        graph[1].emplace_back(5 + 4 * counterEnd, 5);
        graph[5 + 4 * counterEnd].emplace_back(1, 5);
    }
}

void solution(int n)
{
    int tmpV = 1, amountV = 2 + 4 * n;
    for (int i = 1; i < amountV; i++)
        if (houses[(i - 2) / 4] != make_pair(0, 0))
            adding(0, i, amountV);

    for (int i = 2; i < amountV; i++)
        if (houses[(i - 2) / 4] != make_pair(95, 95))
            adding(1, i, amountV);

    for (int i = 2; i < amountV; i++)
        for (int j = i + 1; j < amountV; ++j)
            if ((i - 2) / 4 != (j - 2) / 4)
                adding(i, j, amountV);

    algDijkstra();
    fout << fixed << setprecision(1) << result[1] << endl;
    vector <pair <int, int>> way;
    while (tmpV)
    {
        way.emplace_back(coordinates(tmpV));
        tmpV = parent[tmpV];
    }
    way.emplace_back(coordinates(0));
    answerForm(way);
    for (int i = way.size() - 1; i >= 0; i--)
    {
        pair <int, int> tmp = way[i];
        fout << '(' << tmp.first << ';' << tmp.second << ')' << ' ';
    }
}
