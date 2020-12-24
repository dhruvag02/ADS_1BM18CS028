#include<iostream>
#include<algorithm>

using namespace std;

void lessThanSecond(int *arr, int n)
{
    sort(arr, arr+n);
    for(int i=0; i<n-2; i++)
        cout<<arr[i]<<" ";
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