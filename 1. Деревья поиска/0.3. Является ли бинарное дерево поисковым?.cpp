#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin;
ofstream fout;

struct Ttree
{
    long long value;
    long long leftBound;
    long long rightBound;
};

bool isBST(long long &length, long long &lineNumber, long long &node, long long &parentLine,
           string &nodeWay, Ttree *tree, bool &flag)
{
    for (; length > 0; length--)
    {
        lineNumber++;

        fin >> node >> parentLine >> nodeWay;

        if (nodeWay == "L")
        {
            if (node >= tree[parentLine].value || node < tree[parentLine].leftBound)
            {
                flag = false;
                break;
            }
            tree[lineNumber].rightBound = tree[parentLine].value;
            tree[lineNumber].leftBound = tree[parentLine].leftBound;
        }
        else if (nodeWay == "R")
        {
            if (node < tree[parentLine].value || node >= tree[parentLine].rightBound)
            {
                flag = false;
                break;
            }
            tree[lineNumber].leftBound = tree[parentLine].value;
            tree[lineNumber].rightBound = tree[parentLine].rightBound;
        }

        tree[lineNumber].value = node;
    }
    return flag;
}

int main()
{
    fin.open("bst.in");
    fout.open("bst.out");
    try
    {
        if (fin.is_open()&& fout.is_open())
        {
            long long length(0), root(0);

            fin >> length >> root;

            Ttree *tree = new Ttree[length+2];
            tree[1].value=root;
            tree[1].leftBound=LONG_LONG_MIN;
            tree[1].rightBound=LONG_LONG_MAX;

            long long node(0), parentLine(0), lineNumber(1);
            string nodeWay;
            bool flag = true;
            isBST(length, lineNumber, node, parentLine, nodeWay, tree, flag);
            fout << ((flag) ? "YES" : "NO");
        }
    }
    catch (const char* error)
    {
        cout << error << endl;
        fin.close();
        fout.close();
    }
    fin.close();
    fout.close();
    return 0;
}
