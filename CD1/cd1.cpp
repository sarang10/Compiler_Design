#include <iostream>
#include<set>
#include<queue>
#define MAX 100001

using namespace std;

set<int> adj[MAX][27];
int ans[MAX][27];
bool visited[MAX], is_initial[MAX], is_final[MAX], isUsed[26];
int n, m;

void print(int x)
{
    cout<<"[";
    bool fi=1;
    for(int j=0;j<n;j++)
    {
        if((1<<j)&x)
        {
            if(!fi)
                cout<<", ";
            cout<<j;
            fi=0;
        }
    }
    cout<<"]";
}
int main()
{
    cout<<"Enter number of states(max 16): ";
    cin>>n;
    cout<<"Enter number of transitions: ";
    cin>>m;
    cout<<"Enter Transitions(states are denoted by 0, 1, 2...,15) in th form state1 input_symbol state2\n";
    cout<<"Note: Denote symbols from a-z. \n";
    int i, x, y, j;
    char sym;
    for(i=0; i<m; i++)
    {
        cin>>x;
        cin>>sym;
        while(sym==' '||sym=='\n')
            cin>>sym;
        cin>>y;
            adj[x][sym-96].insert(y);
            isUsed[sym-97]=1;
    }
    cout<<"Enter initial state: ";
    cin>>x;
    is_initial[1<<x]=1;
    cout<<"Enter number of final states: ";
    int f;
    cin>>f;
    cout<<"Enter final states: ";
    for(i=0;i<f;i++)
    {
        cin>>x;
        is_final[1<<x]=1;
    }
    queue<int> Q;
    vector<int> v;
    set<int>::iterator it;
    for(i=0;i<n;i++)
    {
        v.push_back(1<<i);
        visited[1<<i]=1;
        for(j=1;j<27;j++)
        {
            set<int> S=adj[i][j];
            ans[1<<i][j]=0;
            for(it=S.begin();it!=S.end();it++)
            {
                ans[1<<i][j]|=1<<(*it);
            }
            if(S.size()>1&&!visited[ans[1<<i][j]])
                Q.push(ans[1<<i][j]);
            visited[ans[1<<i][j]]=1;
        }
    }
    while(!Q.empty())
    {
        int k=Q.front();
        v.push_back(k);
        Q.pop();
        for(i=1;i<27;i++)
        {
            for(j=0;j<n;j++)
            {
                if((1<<j)&k)
                {
                    ans[k][i]|=ans[1<<j][i];
                    is_initial[ans[k][i]]|=is_initial[ans[1<<j][i]];
                    is_final[ans[k][i]]|=is_final[ans[1<<j][i]];
                }
            }
            if(!visited[ans[k][i]])
                Q.push(ans[k][i]);
            visited[ans[k][i]]=1;
        }
    }
    //Print DFA transition table
    //'-' denotes invalid transition
    cout<<"Initial states: ";
    for(i=1;i<(1<<n);i++)
    {
        if(is_initial[i])
        {
            print(i);
            cout<<" ";
        }
    }
    cout<<"\nFinal states: ";
    for(i=1;i<(1<<n);i++)
    {
        if(is_final[i])
        {
            print(i);
            cout<<" ";
        }
    }
    cout<<"\nTransition Table";
    cout<<"\n------------------------------------------------------------------------\nState\t\t|";
    for(i=0;i<26;i++)
    {
        if(isUsed[i]==1)
        {
            cout<<(char)(i+97)<<"\t\t|";
        }
    }
    cout<<"\n";
    for(i=0;i<v.size();i++)
    {
        x=v[i];
        print(x);
        cout<<"\t\t|";
        for(j=1;j<27;j++)
        {
            if(!isUsed[j-1])
                continue;
            if(ans[x][j]==0)
                cout<<"-\t\t|";
            else
            {
                print(ans[x][j]);
                cout<<"\t\t|";
            }
        }
        cout<<endl;
    }
}
