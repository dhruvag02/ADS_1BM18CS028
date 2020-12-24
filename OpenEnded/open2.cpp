#include<iostream>
#include<algorithm>

using namespace std;

void uniqNumber(int l, int r)
{
    for(int i=l; i<=r; i++)
    {
        int num=i;
        bool visited[10]={false};

        while(num)
        {
            if(visited[num%10])
                break;
            
            visited[num%10]=true;
            num=num/10;
        }
        if(num==0)
            cout<<i<<" ";
    }
}

int main()
{
    int l, r;
    cin>>l;
    cin>>r;

    uniqNumber(l, r);

    return 0;
}