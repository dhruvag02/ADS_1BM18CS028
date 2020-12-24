#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

void lessThanSecond(int* arr, int n)
{
    int first=INT_MIN;
    int second=INT_MIN;

    for(int i=0; i<n; i++)
    {
        if(arr[i] > first)
        {
            second=first;
            first=arr[i];
        }
        else if(arr[i] > second)
            second=arr[i];
    }

    for(int i=0; i<n; i++)
    {
        if(arr[i]<second)
            cout<<arr[i]<<" ";
    }
}

int main()
{
    int t;
    cout<<"Enter number of test cases"<<endl;
    cin>>t;
    while(t > 0)
    {
        int n;
        cout<<"\nEnter number of elements"<<endl;
        cin>>n;
        int *arr=new int[n];
        cout<<"Enter elements"<<endl;
        for(int i=0; i<n; i++)
        cin>>arr[i];
    
        lessThanSecond(arr, n);
        t--;
    }
    return 0;
}