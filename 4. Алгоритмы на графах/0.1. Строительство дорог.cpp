#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

class DisjointSetUnion
{
public:
    int* parent;
    int* size;
    int components;

    DisjointSetUnion(int n)
    {
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            size[i] = 1;
        }
        components = n;
    }

    int getComponents()
    {
        return components;
    }

    int findSet(int& x)
    {
        if (parent[x] == x)
            return x;
        parent[x] = findSet(parent[x]);
        return parent[x];
    }

    void unions(int x, int y)
    {
        x = findSet(x);
        y = findSet(y);
        if (x != y)
        {
            if (size[x] < size[y])
                swap(x, y);
            parent[x] = y;
            size[y] += size[x];
            components = components - 1;
        }
    }
};

int main()
{

    int n, m;
    in >> n;
    in >> m;

    int f, s;

    DisjointSetUnion setUnion(n);
    for (int i = 0; i < m; i++)
    {
        in >> f;
        in >> s;
        setUnion.unions(f - 1, s - 1);
        out << setUnion.getComponents() << "\n";
    }
    return 0;
}
