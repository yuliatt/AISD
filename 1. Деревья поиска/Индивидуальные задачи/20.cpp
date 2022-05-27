#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class TTree
{
    struct TNode
    {
        int value;
        TNode* left;
        TNode* right;
        TNode* parent;
        long long height;
        long long maxSemipath;
        int minDeepestValue1;
        int minDeepestValue2;

        TNode(int vValue, TNode* pParent) : value(vValue), left(nullptr), right(nullptr), parent(pParent),
                                            height(NULL), maxSemipath(NULL), minDeepestValue1(NULL),minDeepestValue2(NULL) {}
    };

    TNode* root;
    vector<TNode*> nodes;
    long long maxSemipathLength;
    long long minSum;

    void insert(TNode*& root, int value, TNode* parent);
    void leftTraversal(TNode* root, vector<long long>& vNodes)const;
    void postorder(TNode* root);
    vector<TNode*> maxPath(TNode* root);
    vector<TNode*> maxOtherPath(TNode* root);
    TNode* findCentralNode(TNode* root);
    TNode* findNewRoot();
    void rightRotation(TNode*& node);
    void leftRotation(TNode*& node);

public:

    TTree() : root(nullptr), maxSemipathLength(0) {}
    void insert(int value);
    vector<long long> printTraversal();
    vector<long long> result();

    ~TTree(){}

};

void TTree::insert(TNode*& root, int value, TNode* parent)
{
    if (root == nullptr)
    {
        root = new TNode(value, parent);
    }

    else if (value < root->value)
    {
        insert(root->left, value, root);
    }
    else if (value > root->value)
    {
        insert(root->right, value, root);
    }
}

void TTree::leftTraversal(TNode* root, vector<long long>& vNodes)const
{
    if (root == nullptr)
        return;
    vNodes.push_back(root->value);
    leftTraversal(root->left, vNodes);
    leftTraversal(root->right, vNodes);
}

void TTree::postorder(TNode* root)
{
    if (root == nullptr) return;

    postorder(root->left);
    postorder(root->right);

    if (root->left == nullptr && root->right == nullptr)
    {
        root->height = 0;
        root->maxSemipath = 0;
        root->minDeepestValue1 = root->value;
    }
    else if (root->left && root->right)
    {
        root->height = max(root->left->height, root->right->height) + 1;
        root->maxSemipath = root->left->height + root->right->height + 2;
        if (root->left->height == root->right->height)
        {
            root->minDeepestValue1 = min(root->left->minDeepestValue1,
                                         root->right->minDeepestValue1);
        }
        else if (root->left->height > root->right->height)
        {
            root->minDeepestValue1 = root->left->minDeepestValue1;
        }
        else
        {
            root->minDeepestValue1 = root->right->minDeepestValue1;
        }


        if (root->left->height > root->right->height)
        {
            if (root->left->height == root->right->height + 1)
            {
                root->minDeepestValue2 = min(root->left->minDeepestValue2,
                                             root->right->minDeepestValue1);
            }
            else
            {
                root->minDeepestValue2 = root->left->minDeepestValue2;
            }
        }
        else if (root->left->height < root->right->height)
        {
            if (root->left->height + 1 == root->right->height)
            {
                root->minDeepestValue2 = min(root->left->minDeepestValue1,
                                             root->right->minDeepestValue2);
            }
            else
            {
                root->minDeepestValue2 = root->right->minDeepestValue2;
            }
        }
        else
        {
            int leftMin, rightMin;
            if (root->left->left == nullptr && root->left->right == nullptr)
            {
                leftMin = root->value;
            }
            else
            {
                leftMin = root->left->minDeepestValue2;
            }

            if (root->right->left == nullptr && root->right->right == nullptr)
            {
                rightMin = root->value;
            }
            else
            {
                rightMin = root->right->minDeepestValue2;
            }
            root->minDeepestValue2 = min(leftMin, rightMin);
        }
    }
    else if (root->left)
    {
        root->height = root->left->height + 1;
        root->maxSemipath = root->height;
        root->minDeepestValue1 = root->left->minDeepestValue1;

        if (root->left->left == nullptr && root->left->right == nullptr)
        {
            root->minDeepestValue2 = root->value;
        }
        else
        {
            root->minDeepestValue2 = root->left->minDeepestValue2;
        }
    }
    else if (root->right)
    {
        root->height = root->right->height + 1;
        root->maxSemipath = root->height;
        root->minDeepestValue1 = root->right->minDeepestValue1;

        if (root->right->left == nullptr && root->right->right == nullptr)
        {
            root->minDeepestValue2 = root->value;
        }
        else
        {
            root->minDeepestValue2 = root->right->minDeepestValue2;
        }
    }

    if (root->maxSemipath >= maxSemipathLength - 1)
    {
        if (root->maxSemipath > maxSemipathLength)
        {
            nodes.clear();
            maxSemipathLength = root->maxSemipath;
        }
        nodes.push_back(root);

    }
}

vector<TTree::TNode*> TTree::maxPath(TNode* root)
{
    vector<TNode*> path;

    if (root == nullptr) return path;

    while (root->left || root->right)
    {
        path.push_back(root);
        if (root->left && root->right)
        {
            if (root->left->height < root->right->height)
            {
                root = root->right;
            }
            else
            {
                root = root->left;
            }
        }
        else if (root->left)
        {
            root = root->left;
        }
        else if (root->right)
        {
            root = root->right;
        }
    }
    path.push_back(root);
    return path;
}

vector<TTree::TNode*> TTree::maxOtherPath(TNode* root)
{
    vector<TNode*> path;
    if (root == nullptr || root->left == nullptr && root->right == nullptr)
    {
        return path;
    }

    long long h = root->height - 1;

    while (h)
    {
        path.push_back(root);
        h--;

        if (root->left && root->right)
        {
            if (root->left->height < root->right->height && root->left->height != h) root = root->right;
            else root = root->left;
        }
        else if (root->left) root = root->left;
        else if (root->right) root = root->right;
    }
    path.push_back(root);

    return path;
}

TTree::TNode* TTree::findCentralNode(TNode* root)
{
    vector<TNode*> leftPath;
    vector<TNode*> rightPath;

    if (root->left && root->right)
    {
        if (root->left->height == root->right->height)
        {
            if (root->left->minDeepestValue1 + root->right->minDeepestValue2 <
                root->left->minDeepestValue2 + root->right->minDeepestValue1)
            {
                leftPath = maxPath(root->left);
                rightPath = maxOtherPath(root->right);
            }
            else
            {
                leftPath = maxOtherPath(root->left);
                rightPath = maxPath(root->right);
            }
        }
        else
        {
            leftPath = maxPath(root->left);
            rightPath = maxPath(root->right);
        }
    }
    else if (root->left)
    {
        leftPath = maxPath(root->left);
    }
    else if (root->right)
    {
        rightPath = maxPath(root->right);
    }

    vector<TNode*> path;
    path.insert(path.end(), leftPath.rbegin(), leftPath.rend());
    path.push_back(root);
    path.insert(path.end(), rightPath.begin(), rightPath.end());

    minSum = path[0]->value + path[path.size() - 1]->value;
    if (path.size() % 2)
    {
        return path[path.size() / 2];
    }
    return nullptr;
}

TTree::TNode* TTree::findNewRoot()
{
    TNode* newRoot = nullptr;
    long long minSum(INT64_MAX);

    if (find_if(nodes.begin(), nodes.end(), [&](TNode* root)
    {
        if (root->left && root->right)
            return root->maxSemipath == maxSemipathLength && root->left->height != root->right->height;
        return root->maxSemipath == maxSemipathLength;
    }) != nodes.end())
    {
        nodes.erase(remove_if(nodes.begin(), nodes.end(), [&](TNode* root)
        {
            if (root->left && root->right)
                return root->maxSemipath != maxSemipathLength || root->left->height == root->right->height;
            return root->maxSemipath != maxSemipathLength;
        }), nodes.end());

        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            long long sum;
            if ((*i)->left && (*i)->right)
            {
                sum = (*i)->left->minDeepestValue1 + (*i)->right->minDeepestValue1;
            }
            else 
                if ((*i)->left)
                {
                    sum = (*i)->left->minDeepestValue1 + (*i)->value;
                }
            else 
                if ((*i)->right)
                {
                    sum = (*i)->right->minDeepestValue1 + (*i)->value;
                }

            if (sum < minSum)
            {
                newRoot = *i;
                minSum = sum;
            }
        }
    }
    else
    {
        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            long long sum;
            if ((*i)->left && (*i)->right)
            {
                if ((*i)->left->height == (*i)->right->height)
                    sum = min((*i)->left->minDeepestValue1 + (*i)->right->minDeepestValue2,
                              (*i)->left->minDeepestValue2 + (*i)->right->minDeepestValue1);
                else
                {
                    sum = (*i)->left->minDeepestValue1 + (*i)->right->minDeepestValue1;
                }
            }
            else 
                if ((*i)->left)
                {
                    sum = (*i)->left->minDeepestValue1 + (*i)->value;
                }
            else 
                if ((*i)->right)
                {
                    sum = (*i)->right->minDeepestValue1 + (*i)->value;
                }

            if (sum < minSum)
            {
                newRoot = *i;
                minSum = sum;
            }
        }
    }
    return newRoot;
}

void TTree::rightRotation(TNode*& node)
{
    node->parent->left = node->right;
    node->right = node->parent;
    TNode* tmp = node->parent->parent;
    if (root == node->parent)
        root = node;
    else if (tmp->right == node->parent)
        tmp->right = node;
    else
        tmp->left = node;
    node->parent->parent = node;
    node->parent = tmp;
}

void TTree::leftRotation(TNode*& node)
{
    node->parent->right = node->left;
    node->left = node->parent;
    TNode* tmp = node->parent->parent;
    if (root == node->parent)
        root = node;
    else if (tmp->right == node->parent)
        tmp->right = node;
    else
        tmp->left = node;
    node->parent->parent = node;
    node->parent = tmp;
}

void TTree::insert(int value)
{
    insert(root, value, nullptr);
}

vector<long long> TTree::printTraversal()
{
    vector<long long> vNodes;
    leftTraversal(root, vNodes);
    return vNodes;
}

vector<long long> TTree::result()
{
    postorder(root);
    TNode* newRoot = findNewRoot();
    TNode* centralNode = findCentralNode(newRoot);

    if (centralNode)
        while (this->root != centralNode)
        {
            if (centralNode->parent->right == centralNode)
            {
                leftRotation(centralNode);
            }
            else if (centralNode->parent->left == centralNode)
            {
                rightRotation(centralNode);
            }
        }

    vector<long long> vResult;
    vResult.push_back(minSum);
    vector<long long> traversal = printTraversal();
    vResult.insert(vResult.begin() + 1, traversal.begin(), traversal.end());
    return vResult;
}

int main()
{
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    try
    {
        if (fin.is_open() && fout.is_open())
        {
            TTree tTree;
            int node(0);
            while (!fin.eof())
            {
                fin >> node;
                tTree.insert(node);
            }

            vector<long long> vResult = tTree.result();
            for (long long item: vResult)
            {
                fout << item << '\n';
            }
        }
    }
    catch (const char* error)
    {
        fout << error << endl;
        fin.close();
        fout.close();
    }
    fin.close();
    fout.close();
    return 0;
}
