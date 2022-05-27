#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

struct TNode
{
    int value;
    struct TNode *left;
    struct TNode *right;
}*root;

class TTree
{
public:
    TTree()
    {
        root = NULL;
    }
    void insert(TNode *, TNode *);
    void leftTraversal(TNode *);
};

void TTree::insert(TNode *tree, TNode *newValue)
{
    if (root == NULL)
    {
        root = new TNode;
        root->value = newValue->value;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if (tree->value == newValue->value)
    {
        return;
    }
    if (tree->value > newValue->value)
    {
        if (tree->left != NULL)
        {
            insert(tree->left, newValue);
        }
        else
        {
            tree->left = newValue;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            return;
        }
    }
    else
    {
        if (tree->right != NULL)
        {
            insert(tree->right, newValue);
        }
        else
        {
            tree->right = newValue;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            return;
        }
    }
}

void TTree::leftTraversal(TNode *ptr)
{
    if (root == NULL)
    {
        return;
    }
    if (ptr != NULL)
    {
        fout << ptr->value << "\n";
        leftTraversal(ptr->left);
        leftTraversal(ptr->right);
    }
}

int main() {
    fin.open("input.txt");
    fout.open("output.txt");
    try
    {
        if (fin.is_open()&& fout.is_open())
        {
            TTree tTree;
            TNode *tmp;
            int s;
            while (!fin.eof())
            {
                tmp = new TNode;
                fin >> s;
                tmp->value = s;
                tTree.insert(root, tmp);
            }
            tTree.leftTraversal(root);
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
