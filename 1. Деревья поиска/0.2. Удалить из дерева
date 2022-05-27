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
    void findKey(int, TNode **, TNode **);
    void deleteNode(int);
    void f1(TNode *, TNode *);
    void f2(TNode *, TNode *);
    void f3(TNode *, TNode *);
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

void TTree::findKey(int key, TNode **parent, TNode **equal)
{
    TNode *ptr, *ptrNode;
    if (root == NULL)
    {
        *equal = NULL;
        *parent = NULL;
        return;
    }
    if (key == root->value)
    {
        *equal = root;
        *parent = NULL;
        return;
    }
    if (key < root->value)
        ptr = root->left;
    else
        ptr = root->right;
    ptrNode = root;
    while (ptr != NULL)
    {
        if (key == ptr->value)
        {
            *equal = ptr;
            *parent = ptrNode;
            return;
        }
        ptrNode = ptr;
        if (key < ptr->value)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    *equal = NULL;
    *parent = ptrNode;
}

void TTree::deleteNode(int key)
{
    TNode *parent, *equal;

    if (root == NULL) return;

    findKey(key, &parent, &equal);
    if (equal == NULL) return;

    if (equal->left == NULL && equal->right == NULL)
        f1(parent, equal);
    if ((equal->left != NULL && equal->right == NULL) ||
        (equal->left == NULL && equal->right != NULL))
        f2(parent, equal);
    if (equal->left != NULL && equal->right != NULL)
        f3(parent, equal);
    //delete(equal);
    free(equal);
}

void TTree::f1(TNode *parent, TNode *forDelete)
{
    if (parent == NULL)
        root = NULL;
    else
    {
        if (forDelete == parent->left)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
}

void TTree::f2(TNode *parent, TNode *forDelete)
{
    TNode *child;
    if (forDelete->left != NULL)
        child = forDelete->left;
    else
        child = forDelete->right;
    if (parent == NULL)
        root = child;
    else
    {
        if (forDelete == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
}

void TTree::f3(TNode *parent, TNode *forDelete)
{
    TNode *ptr, *ptrNode, *fDel, *parentfDel;
    ptrNode = forDelete;
    ptr = forDelete->right;
    while (ptr->left != NULL)
    {
        ptrNode = ptr;
        ptr = ptr->left;
    }
    fDel = ptr;
    parentfDel = ptrNode;

    if (fDel->left == NULL && fDel->right == NULL)
        f1(parentfDel, fDel);
    else
        f2(parentfDel, fDel);

    if (parent == NULL)
        root = fDel;
    else
    {
        if (forDelete == parent->left)
            parent->left = fDel;
        else
            parent->right = fDel;
    }
    fDel->left = forDelete->left;
    fDel->right = forDelete->right;
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
            int s, key;
            fin >> key;
            fin.ignore();
            while (!fin.eof())
            {
                tmp = new TNode;
                fin >> s;
                tmp->value = s;
                tTree.insert(root, tmp);
            }
            tTree.deleteNode(key);
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
