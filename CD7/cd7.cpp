#include<iostream>
using namespace std;
int main()
{
    int n,i,j;
    cout<<"Enter the number of productions\n";
    cin>>n;
    string s[n];
    cout<<"Input the grammar\n";
    for(i=0;i<n;i++)
    {
        cin>>s[i];
    }
    cout<<"The output Grammar is:\n\n\n";
    for(i=0;i<n;i++)
    {
        if(s[i][0]==s[i][2])
        {
           cout<<s[i][0]<<"'=";
           j=3;
           while(j<s[i].size())
           {
                cout<<s[i][j];
                j++;
           }
           cout<<s[i][0]<<"'";
           cout<<"\n";
        }
        else{
            cout<<s[i][0]<<"=";
            j=2;
           while(j<s[i].size())
           {
                cout<<s[i][j];
                j++;
           }
           cout<<s[i][0]<<"'";
           cout<<"\n";
        }
    }
    for(i=0;i<n;i++)
    {
        if(s[i][0]==s[i][2])
            cout<<s[i][0]<<"'=^\n";
    }
    return 0;
}
