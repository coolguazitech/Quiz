/*
    Problem:
        Given a full binary tree (that can hence be) expressed as a vecter, design a function
        to find the number of universal trees embedded in it.
*/

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

class BTree
{
    private:
        int root;
        BTree* lTree = NULL;
        BTree* rTree = NULL;
        int univTreeCount = 0;

    public:
        int getRoot(){return root;}
        BTree* getLTree(){return lTree;}
        BTree* getRTree(){return rTree;}
        int getUnivTreeCount(){return univTreeCount;}
        void setUnivTreeCount(int numUnivTreeCount){univTreeCount = numUnivTreeCount;}
        void setRoot(int root){this->root = root;}

        BTree(int root, BTree* lTree, BTree* rTree)
        {
            this->root = root;
            this->lTree = lTree;
            this->rTree = rTree;
        }
};

vector<int>* fBTVectorGenerator(int depth) // generates a vector-like full BT with given depth
{
    vector<int>* res = new vector<int>;
    srand((unsigned)time(0));
    int numNodes = pow(2, (depth + 1)) - 1;

    for(int i = 0; i < numNodes; i++)
    {
        int randNum = rand() % 3 / 2  + 1;
        res->push_back(randNum);
    }

    return res; 
}

BTree* fBTGenerator(int depth) // generates a full BT with given depth
{
    vector<int>* fBTVector = fBTVectorGenerator(depth);
    auto iter = fBTVector->cend();
    int numLeaves = pow(2, depth);
    queue<BTree*> trees;

    for(int i = 0; i < numLeaves; i++)
    {
        trees.push(NULL);
        trees.push(NULL);
    }

    while(numLeaves != 0)
    {
        for(int i = 0; i < numLeaves; i++)
            {
                int root = *(--iter);
                BTree* rTree = trees.front();
                trees.pop();
                BTree* lTree = trees.front();
                trees.pop();
                BTree* tree = new BTree(root, lTree, rTree);
                trees.push(tree);
            }
        numLeaves /= 2;
    }
    return trees.front();
}

void solve(BTree* tree) // problem solver to which is applied by recursive function
{
    if(tree->getLTree() == NULL && tree->getRTree() == NULL)
    {
        tree->setUnivTreeCount(1);
    }
    else if(tree->getLTree() == NULL && tree->getRTree() != NULL)
    {
        solve(tree->getRTree());
        if(tree->getRoot() == tree->getRTree()->getRoot())
        {
            tree->setUnivTreeCount(tree->getRTree()->getUnivTreeCount() + 1);
        }
        else
        {
            tree->setRoot(0);
            tree->setUnivTreeCount(tree->getRTree()->getUnivTreeCount());
        }
    }
    else if(tree->getLTree() != NULL && tree->getRTree() == NULL)
    {
        solve(tree->getLTree());
        if(tree->getRoot() == tree->getLTree()->getRoot())
        {
            tree->setUnivTreeCount(tree->getLTree()->getUnivTreeCount() + 1);
        }
        else
        {
            tree->setRoot(0);
            tree->setUnivTreeCount(tree->getLTree()->getUnivTreeCount());
        }
    }
    else
    { 
        solve(tree->getLTree());
        solve(tree->getRTree());
        if(tree->getRoot() == tree->getLTree()->getRoot() && tree->getRoot() == tree->getRTree()->getRoot())
        {
            tree->setUnivTreeCount(tree->getLTree()->getUnivTreeCount() + tree->getRTree()->getUnivTreeCount() + 1);
        }
        else
        {
            tree->setRoot(0);
            tree->setUnivTreeCount(tree->getLTree()->getUnivTreeCount() + tree->getRTree()->getUnivTreeCount());
        }
    }
}

void visualize(BTree* tree, int depth) // depict the graph of the tree
{ 
    queue<BTree*> trees;
    trees.push(tree);
    int count = depth;

    while(count >= 0)
    { 
        for(int j = 0; j < pow(2, count + 1) - 2; j++)
        {
            cout << ' ';
        }
        for(int i = 0; i < pow(2, depth - count); i++)
        {
            BTree* tree = trees.front();
            trees.push(tree->getLTree());
            trees.push(tree->getRTree());
            trees.pop();
            cout << tree->getRoot();
            for(int j = 0; j < pow(2, count + 2) - 1; j++)
            {
                cout << ' ';
            }
        }
        count--;
        cout << endl << endl;
    }
}

int main()
{
    int depth = 5;
    BTree* tree = fBTGenerator(depth);
    visualize(tree, depth);
    
    solve(tree);
    cout << "\nThere are " << tree->getUnivTreeCount() << " universal trees inside the graph." << endl;

    cin.get();
}