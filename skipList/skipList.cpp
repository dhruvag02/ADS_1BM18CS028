#include<iostream>
#include<algorithm>
#include<time.h>
#include<cstring>


using namespace std;

class Node{
    public:
        int data;
        Node **forward;
        Node(int, int);
};

Node::Node(int data, int lvl){
    this->data=data;
    forward=new Node*[lvl+1];

    // FIll forward arry with 0
    // Array contain pointers to next nodes
    memset(forward, 0, sizeof(Node*) * (lvl+1));
};

class skipList{
    int MAXLVL;
    float P;
    int level;
    Node *head;
    public:
        skipList(int, float);
        int randomLvl();
        Node* createNode(int, int);
        void insertElement(int);
        void delElement(int);
        void searchElement(int);
        void display();
};

skipList::skipList(int MAXLVL, float P){
    this->MAXLVL=MAXLVL;
    this->P=P;
    level=0;
    // Create a header node and initialize to -1
    head=new Node(-1, MAXLVL);
};

int skipList::randomLvl(){
 float r=(float)rand()/RAND_MAX;
 int lvl=0;
 while (r<P && lvl<MAXLVL)
 {
     lvl=lvl+1;
     r=(float)rand()/RAND_MAX;
 }
    return lvl;
};

Node* skipList::createNode(int data, int level){
    Node* n=new Node(data, level);
    return n;
};

void skipList::insertElement(int data){
    Node *curr=head;
    Node **update=new Node*[MAXLVL+1];

    memset(update, 0, sizeof(Node*) * (MAXLVL+1));
    for(int i=level; i>=0; i--){
        while (curr->forward[i]!=NULL && curr->forward[i]->data<data)
        {
            curr=curr->forward[i];
        }
        update[i]=curr;
    }
    curr=curr->forward[0];

    if(curr==NULL || curr->data!=data){
        int rlvl=randomLvl();
        if(rlvl>level){
            for(int i=level+1; i<rlvl+1; i++)
                update[i]=head;
            level=rlvl;
        }
        Node* n=createNode(data,rlvl);
        for(int i=0; i<=rlvl; i++){
            n->forward[i]=update[i]->forward[i];
            update[i]->forward[i]=n;
        }
        cout<<"Successfully inserted data "<<data<<endl;
    }
};

void skipList::delElement(int data){
    Node* curr=head;
    Node **update=new Node*[MAXLVL+1];

    memset(update, 0, sizeof(Node*) * (MAXLVL+1));
    for(int i=level; i>=0; i--){
        while (curr->forward[i]!=NULL && curr->forward[i]->data<data)
        {
            curr=curr->forward[i];
        }
        update[i]=curr;
    }
    curr=curr->forward[0];
    if(curr!=NULL && curr->data==data){
        for(int i=0;i<=level; i++){
            if(update[i]->forward[i]!=curr)
                break;
            update[i]->forward[i]=curr->forward[i];
        }
        while (level>0 && head->forward[level]==0)
        {
            level--;
        }
        cout<<"Successfully deleted "<<data<<endl;
    }   
};

void skipList::searchElement(int data){
    Node *curr=head;
    for(int i=level; i>=0; i--){
        while(curr->forward[i]!=NULL && curr->forward[i]->data<data){
            curr=curr->forward[i];
        }
    }
    curr=curr->forward[0];
    if(curr && curr->data==data)
        cout<<"Found Data: "<<data<<"\n";
};

void skipList::display(){
    cout<<"Elements are displayed"<<endl;
    for(int i=0; i<=level; i++){
        Node *node=head->forward[i];
        cout<<"level"<<i<<": ";
        while (node != NULL)
        {
            cout<<node->data<<" ";
            node=node->forward[i];
        }
        cout<<"\n";
    }
};

int main(){

    // Seed Random number generator
    srand((unsigned)time(0));
    skipList lst(3, 0.5);
    int n,val,v,e;
    cout<<"Enter number of elements"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter element to be inserted"<<endl;
        cin>>val;
        lst.insertElement(val);
    }
    lst.display();
    cout<<"Enter element to be deleted"<<endl;
    cin>>v;
    lst.delElement(v);
    lst.display();
    cout<<"Enter element to be searched"<<endl;
    cin>>e;
    lst.searchElement(e);
    return 0;
}