#include <fstream>
#include <vector>
#include <iostream>

std::ifstream in("input.txt");
std::ofstream out("output.txt");

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
            if (size[x] > size[y])
                std::swap(x, y);
            parent[x] = y;
            size[y] += size[x];
            components = components - 1;
        }
    }
};

int main()
{
    int n, m, q;
    in >> n >> m >> q;
    std::vector<std::pair<int, int>> verges;
    verges.reserve(m);


    int f, s;
    DisjointSetUnion setUnion(n);
    for (int i = 0; i < m; i++)
    {
        in >> f >> s;
        verges.emplace_back(f - 1, s - 1);
    }
    int k, flag = 0;
    bool* ic = new bool[m];
    for (int i = 0; i < m; i++)
    {
        ic[i] = false;
    }
    int* c = new int[q];
    for (int i = 0; i < q; i++)
    {
        in >> k;
        c[i] = k - 1;
        ic[k - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        if (ic[i] == false)
        {
            setUnion.unions(verges[i].first, verges[i].second);
        }
    }
    for (int i = q - 1; i >= 0 ; i--)
    {
        if (setUnion.getComponents() == 1)
            break;
        flag++;
        setUnion.unions(verges[c[i]].first, verges[c[i]].second);
    }

    for (int i = 0; i < q - flag; i++)
        out << 1;
    for (int i = 0; i < flag; i++)
        out << 0;
    return 0;
}
