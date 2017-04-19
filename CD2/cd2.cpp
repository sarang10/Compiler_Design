#include<iostream>
using namespace std;
int main()
{
    string s;
    int cd[10][10],a,final_state[10],curr_state,n,m,i,j,fin;
    cout<<"Enter the string to check\n";
    cin>>s;
    cout<<"Enter the number of states\n";
    cin>>m;
    cout<<"Enter the number of input symbols\n";
    cin>>n;
    cout<<"Enter the transitions\n";
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<"Transition from "<<i<<" state with input symbol "<<j<<" : ";
            cin>>cd[i][j];
        }
    }
    cout<<"\nEnter the starting state\n";
    cin>>curr_state;
    cout<<"Enter the number of final states\n";
    cin>>fin;
    for(i=0;i<10;i++)
    final_state[i]=0;
    cout<<"Enter the final states\n";
    while(fin--)
    {
        cin>>a;
        final_state[a]=1;
    }
    for(i=0;i<s.size();i++)
    {
        curr_state = cd[curr_state][(int)(s[i]-48)];
    }
    if(final_state[curr_state]==1)
    cout<<"Accepted\n";
    else cout<<"Not Accepted\n";
    return 0;
}

