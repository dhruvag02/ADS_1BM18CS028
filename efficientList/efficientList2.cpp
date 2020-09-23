#include<iostream>
#include<algorithm>
#include<functional>
#include<iterator>
#include<inttypes.h>
using namespace std;
struct node
{
    int data;
    struct node *npx;
};
typedef struct node *NODE;

NODE getnode(){
    NODE p;
    p=(NODE) malloc(sizeof(struct node));
    if(p!=NULL)
        return p;
    else{
        cout<<"Memory coukd not be allocated"<<endl;
        return NULL;
    }
}

NODE XOR(NODE a, NODE b){
    return (NODE) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

NODE insert_end(int item,NODE head){
    NODE p=getnode();
    p->data=item;
    if(head==NULL){
        p->npx=head;
        head=p;
    }
    else{
    NODE curr=head, prev=NULL, next;
    while (next!=NULL)
    {
        next=XOR(curr->npx,prev);
        prev=curr;
        curr=next;
    }
    NODE tail=prev;
    p->npx=XOR(NULL,tail);
    tail->npx=XOR(XOR(tail->npx, NULL),p);
    }
    return head;
}

void display(NODE head){
    NODE curr=head, prev=NULL, next;
    if(head==NULL){
        cout<<"List is empty"<<endl;
    }
    while(curr!=NULL){
        cout<<curr->data<<" ";
        next=XOR(prev, curr->npx);
        prev=curr;
        curr=next;
    }
}

int main(){
    NODE head=NULL;
    int n,e;
    cout<<"Enter number of elements to be inserted"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter element to be inserted"<<endl;
        cin>>e;
        head=insert_end(e,head);
    }
    cout<<"Elements are displayed"<<endl;
    display(head);
    return 0;
}