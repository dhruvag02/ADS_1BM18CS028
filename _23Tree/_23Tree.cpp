// Implementing 2-3 Tree using Btree, where t=2, order = (2*t-1)

#include<iostream>
#include<algorithm>

using namespace std;

// A Btree node
class TreeNode
{
    int *keys;    //Array of keys
    int t;
    TreeNode **C; //Array of child pointers
    int n;        //current number of keys, max=2, when 3, split
    bool leaf;    //True when node is leaf

    public:
        TreeNode(int _t, bool _leaf);    //Constructor 
        void insertNonFull(int data);    //The Node must be non-full when this is called
        void splitChild(int i, TreeNode *y);   //Split child y, y must be full when this is called
        void traverse();   //Traverse Nodes in tree
        TreeNode* search(int data);
        int findKey(int data);
        void remove(int data);
        void removeFromLeaf(int idx);
        void removeFromNonLeaf(int idx);
        int getPred(int idx);
        int getSucc(int idx);
        void fill(int idx);
        void borrowFromPrev(int idx);
        void borrowFromNext(int idx);
        void merge(int idx);
    
    //Access private members of this class in Tree functions
    friend class Tree;
};

class Tree
{
    TreeNode* root;
    int t;
    public:
        Tree(int _t)
        {
            root=NULL;
            t=_t;
        }

        void traverse()
        {
            if(root!=NULL)
                root->traverse();
        }

        TreeNode* search(int data)
        {
            return (root==NULL)? NULL : root->search(data);
        }

        void insert(int data);    //Main function to insert a new node in tree

        void remove(int data);
};

TreeNode::TreeNode(int t1, bool leaf1){
    t=t1;
    leaf=leaf1;

    keys=new int[2*t-1];
    C=new TreeNode *[2*t]; 
    n=0;
}

int TreeNode::findKey(int data)
{
    int idx=0;
    while(idx<n && keys[idx]<data)
        ++idx;
    return idx;
}

void TreeNode::remove(int data)
{
    int idx=findKey(data);
    if(idx<n && keys[idx] == data)
    {
        if(leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        if(leaf)
        {
            cout<<"The Key "<< data <<"is does not exist in the tree\n";
            return;
        }
        bool flag=( (idx==n)? true : false );

        if(C[idx]->n<t)
            fill(idx);

        if(flag && idx>n)
            C[idx-1]->remove(data);
        else
            C[idx]->remove(data);
    }
    return;
}

void TreeNode::removeFromLeaf(int idx)
{
    for(int i=idx+1; i<n; ++i)
    {
        keys[i-1]=keys[i];
    }
    n--;
    return;
}

void TreeNode::removeFromNonLeaf(int idx)
{
    int k=keys[idx];
    if(C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx]=pred;
        C[idx]->remove(pred);
    }

    else if(C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx]=succ;
        C[idx+1]->remove(succ);
    }

    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

int TreeNode::getPred(int idx)
{
    TreeNode *cur=C[idx];
    while(!cur->leaf)
    {
        cur=cur->C[cur->n];
    }
    return cur->keys[cur->n-1];
}

int TreeNode::getSucc(int idx)
{
    TreeNode* cur=C[idx+1];
    while(!cur->leaf)
        cur=cur->C[0];
    return cur->keys[0];
}

void TreeNode::fill(int idx)
{
    if(idx!=0 && C[idx-1]->n >= t)
    {
        borrowFromPrev(idx);
    }

    else if(idx!=n && C[idx+1]->n >= t)
    {
        borrowFromNext(idx);
    }

    else
    {
        if(idx!=n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

void TreeNode::borrowFromPrev(int idx)
{
    TreeNode* child=C[idx];
    TreeNode* sibling=C[idx-1];

    for(int i=child->n-1; i>=0; --i)
    {
        child->keys[i+1]=child->keys[i];
    }

    if(!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1]=child->C[i];
    }

    child->keys[0]=keys[idx-1];

    if(!child->leaf)
        child->C[0]=sibling->C[sibling->n];

    keys[idx-1]=sibling->keys[sibling->n-1];
    child->n += 1;
    sibling->n += 1;

    return;
}

void TreeNode::borrowFromNext(int idx)
{
    TreeNode* child=C[idx];
    TreeNode* sibling=C[idx+1];

    child->keys[(child->n)] = keys[idx];

    if(!(child->leaf))
    {
        child->C[(child->n)+1]=sibling->C[0];
    }

    keys[idx]=sibling->keys[0];

    for(int i=1; i<sibling->n; ++i)
    {
        sibling->keys[i-1]=sibling->keys[i];
    }

    if(!sibling->leaf)
    {
        for(int i=1; i<=sibling->n;  ++i)
            sibling->C[i-1]=sibling->C[i];
    }

    child->n += 1;
    sibling->n += 1;

    return;
}

void TreeNode::merge(int idx)
{
    TreeNode* child=C[idx];
    TreeNode* sibling=C[idx+1];

    child->keys[t-1]=keys[idx];

    for(int i=0; i<sibling->n; ++i)
        child->keys[i+t]=sibling->keys[i];
    
    if(!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t]=sibling->C[i];
    }

    for(int i=idx+2; i<=n; ++i)
        C[i-1]=C[i];

    child->n += sibling->n+1;
    n--;

    delete(sibling);
    return;
}

void TreeNode::traverse()
{
    int i;
    for(i=0; i<n; i++)
    {
        if(leaf==false)
            C[i]->traverse();
        cout<<" "<<keys[i];
    }

    if(leaf==false)
        C[i]->traverse();
}

TreeNode *TreeNode::search(int data)
{
    int i=0;
    while(i<n && data>keys[i])
        i++;

    if(keys[i] == data)
        return this;

    if(leaf==true)
        return NULL;

    return C[i]->search(data);
}

void Tree::insert(int data)
{
    if(root==NULL)
    {
        root = new TreeNode(t, true);
        root->keys[0]=data;
        root->n=1;
    }

    else
    {
        if(root->n==2*t-1)
        {
            TreeNode *s=new TreeNode(t, false);
            s->C[0]=root;
            s->splitChild(0, root);

            int i=0;
            if(s->keys[0] < data)
                i++;
            s->C[i]->insertNonFull(data);

            root=s;
        }
        else
        {
            root->insertNonFull(data);
        }
    }
}

void TreeNode::insertNonFull(int data)
{
    int i=n-1;
    if(leaf==true)
    {
        while(i>=0 && keys[i] > data)
        {
            keys[i+1]=keys[i];
            i--;
        }
        keys[i+1]=data;
        n=n+1;
    }
    else
    {
        while(i>=0 && keys[i] > data)
            i--;
        if(C[i+1]->n==2*t-1)
        {
            splitChild(i+1, C[i+1]);
            if (keys[i+1] < data)
                i++;
        }
        C[i+1]->insertNonFull(data);
    }
}

void TreeNode::splitChild(int i, TreeNode *y)
{
    TreeNode *z=new TreeNode(y->t, y->leaf);
    z->n = t-1;
    for(int j=0; j < t-1; j++)
    {
        z->keys[j]=y->keys[j+t];
    }

    if(y->leaf==false)
    {
        for(int j=0; j < t; j++)
            z->C[j]=y->C[j+t];
    }

    y->n=t-1;
    for(int j=n; j>=i+1; j--)
        C[j+1]=C[j];

    C[i+1]=z;

    for(int j=n-1; j>=i; j--)
        keys[j+1]=keys[j];

    keys[i]=y->keys[t-1];
    n=n+1;  
}

void Tree::remove(int data)
{
    if(!root)
    {
        cout<<"The Tree is empty"<<endl;
        return;
    }

    root->remove(data);

    if(root->n == 0)
    {
        TreeNode* tmp=root;
        if(root->leaf)
            root=NULL;
        else
            root=root->C[0];

        delete tmp;
    }
    return;
}

int main()
{
    Tree t(2);
    int n,data;
    cout<<"Enter number of elements"<<endl;
    cin>>n;
    cout<<"Enter keys"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>data;
        t.insert(data);
    }

/*    t.insert(12);
    t.insert(67);
    t.insert(32);
    t.insert(45);
    t.insert(98);
    t.insert(73);
    t.insert(9);
    t.insert(31);
*/
    cout<<"TRaversal of the constructed tree ";
    t.traverse();

    int val;
    cout<<"\nEnter avlue to be searched"<<endl;
    cin>>val;
    (t.search(val) != NULL)? cout<<"\nPresent" : cout <<"\nNot Present";

    int e;
    cout<<"\nEnter avlue to be deleted"<<endl;
    cin>>e;
    t.remove(e);   

    cout<<"TRaversal after deletion ";
    t.traverse(); 

    return 0;
}
