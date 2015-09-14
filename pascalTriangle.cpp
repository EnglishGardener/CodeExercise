// Pascal Trangle Using byy arrray
#include<iostream>
#include<iomanip>
#define max 16
using namespace std;
int main()
{ 
    int a[max][max];
    int n;
    cout <<"Display Pascal Tringle shao:\n";
    cout<<"Enter the value (<=15):";
    cin>>n;
    if (n>=16)
    { 
        cout <<"Thge value is so big\n";
        return 0;
    }
    if (n<0)
    {
        cout <<" Inlvalid value!";
        return 0;
    }
    for ( int i=0;i<=n;i++)
        a[i][0]=a[i][i]=1;
    for (int i=2;i<=n;i++)
        for (int j=1;j<i;j++)
            a[i][j]=a[i-1][j-1]+a[i-1][j];
    for (int i=0;i<=n;i++)
     { 
        cout<<" \n" ;
        for ( int j=0;j<=i;j++)
        cout<<setw(5)<<a[i][j];
     }
     return 0;
    
}