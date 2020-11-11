#include<iostream>
#include<algorithm>

using namespace std;

class BTreeNode
{
    int *keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;

    public:
        BTreeNode(int _t, int _leaf);
        void insertNonFull(int data);
        void splitChild(int i, BTreeNode* y);
        void traverse();
        BTreeNode* search(int data);
    
    friend class BTree;
};

class BTree
{
    BTreeNode* root;
    int t;
    public:
        BTree(int _t)
        {
            root=NULL;
            t=_t;
        }

        void traverse()
        {
            if(root!=NULL)
                root->traverse();           
        }

        BTreeNode* search(int data)
        {
            return (root == NULL)? NULL : root->search(data);
        }
        void insert(int data);
};

BTreeNode::BTreeNode(int t1, int leaf1)
{
    t=t1;
    leaf=leaf1;
    keys=new int[2*t-1];
    C=new BTreeNode* [2*t];
    n=0;
}

void BTreeNode::traverse()
{
    int i;
    for(i=0; i<n; i++)
    {
        if(leaf == false)
            C[i]->traverse();
        cout<<" "<<keys[i];
    }

    if(leaf==false)
        C[i]->traverse();
}

BTreeNode* BTreeNode::search(int data)
{
    int i=0;
    while(i<n && data>keys[i])
        i++;
    if(keys[i] == data)
        return this;
    if(leaf ==  true)
        return NULL;
    return C[i]->search(data);
}

void BTree::insert(int data)
{
    if(root==NULL)
    {
        root=new BTreeNode(t, true);
        root->keys[0]=data;
        root->n=1;
    }

    else{
        if(root->n == 2*t-1)
        {
            BTreeNode* s=new BTreeNode(t, false);
            s->C[0]=root;
            s->splitChild(0,root);
            int i=0;
            if(s->keys[0]<data)
            {
                i++;
            }
            s->C[i]->insertNonFull(data);
            root=s;
        }
        else
            root->insertNonFull(data);
    }
}

void BTreeNode::insertNonFull(int data)
{
    int i=n-1;
    if(leaf == true)
    {
        while (i>=0 && keys[i]>data)
        {
            keys[i+1]=keys[i];
            i--;
        }

        keys[i+1]=data;
        n=n+1;
    }
    else
    {
        while(i>=0 && keys[i]>data)
        {
            i--;
        }
        if(C[i+1]->n == 2*t-1)
        {
            splitChild(i+1, C[i+1]);
            if(keys[i+1]<data)
                i++;
        }
        C[i+1]->insertNonFull(data);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z= new BTreeNode(y->t, y->leaf);
    z->n=t-1;

    for(int j=0; j<t-1; j++)
        z->keys[j]=y->keys[j+t];
    
    if(y->leaf == false)
    {
        for(int j=0; j<t; j++)
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

int main()
{
    int t;
    cout<<"Enter the order of tree"<<endl;
    cin>>t;

    BTree T(t);
    int n,data;
    cout<<"Enter number of elements"<<endl;
    cin>>n;
    cout<<"Enter Key values"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>data;
        T.insert(data);
    }

    cout<<"TRaversal of the constructed tree ";
    T.traverse();

    int val;
    cout<<"\nEnter avlue to be searched"<<endl;
    cin>>val;
    (T.search(val) != NULL)? cout<<"\nPresent" : cout <<"\nNot Present";

    return 0;
}