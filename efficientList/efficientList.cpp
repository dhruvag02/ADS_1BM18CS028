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

NODE insert_front(int data, NODE head){
    NODE p=getnode();
    p->data=data;
    p->npx=head;
    if(head!=NULL){
        (head)->npx=XOR(p,(head)->npx);
    }
    head=p;
    return head;
}

NODE insert_end(int data, NODE head){
    NODE p=getnode(), q=head, prev=NULL, next;
    p->data=data;
    if (head==NULL)
    {
        p->npx=head;
        head=p;
    }
    else{
    while (q->npx!=NULL)
        {
            next=XOR(prev,q->npx);
            prev=q;
            q=next;
        }
    p=XOR(q->npx,p->npx);
    q->npx=XOR(prev,q->npx);
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
    int e,val,n,j=1,ch;
    cout<<"Enter number of elements to be inserted"<<endl;
    cin>>n;
    while (j!=0)
    {
        cout<<"Enter Choice"<<endl;
        cout<<"1. Insert Front\t 2. Insert End\t 3. Display"<<endl;
        cin>>ch;
        switch (ch)
        {
        case 1:
            for(int i=0;i<n;i++){
            cout<<"Enter element to be inserted"<<endl;
            cin>>e;
            head=insert_front(e,head);
            }
            break;
        case 2:
            for(int j=0;j<n;j++){
            cout<<"Enter element to be inserted"<<endl;
            cin>>val;
            head=insert_end(val,head);
            }
            break;
        case 3:
            cout<<"Elements are displayed"<<endl;
            display(head);        
            break;
        default:
            break;
        }
        cout<<"Enter other than '0' to continue"<<endl;
        cin>>j;
    }
    
    //for(int i=0;i<n;i++){
    //    cout<<"Enter element to be inserted"<<endl;
    //    cin>>e;
    //    head=insert_front(e,head);
    //    head=insert_end(e,head);
    //}
    //cout<<"Elements are displayed"<<endl;
    //display(head);
    return 0;
}