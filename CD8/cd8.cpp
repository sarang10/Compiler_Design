#include<stdio.h>
#include<ctype.h>
#include<iostream>
using namespace std;
int n;
string productions[10];
void ansadd(char ans[],char val)
{
    int k,i;
    for(k=0 ;ans[k]!='\0';k++)
        if(ans[k]==val)
            return;
    ans[k]=val;
    ans[k+1]='\0';
}
void FIRST(char* ans,char c)
{
    int i,j,k;
    char subans[20];
    int epsilon=0;
    subans[0] = '\0';
    ans[0] = '\0';
    if(islower(c)||c=='('||c==')'||c=='*'||c=='+')
    {
        ansadd(ans,c);
        return ;
    }
    else for(i=0;i<n;i++)
    {
        if(productions[i][0]==c)
        {
            if(productions[i][2]=='^')
                ansadd(ans,'^');
            else
            {
                j=2;
                while(productions[i][j]!='\0')
                {
                    epsilon=0;
                    FIRST(subans,productions[i][j]);
                    for(k=0;subans[k]!='\0';k++)
                    {
                        if(subans[k]!='^')
                            ansadd(ans,subans[k]);
                    }
                    for(k=0;subans[k]!='\0';k++)
                    {
                         if(subans[k]=='^')
                         {
                             if(productions[i][j+1]=='\0')
                                 ansadd(ans,'^');
                             epsilon=1;
                             break;
                         }
                     }
                     if(!epsilon)
                         break;
                     j++;
                }
            }
        }
    }
    return ;
}
void FOLLOW(char* answer,char* ans,char c)
{
	int i,j,k;
    ans[0] = '\0';
    if(productions[0][0]==c)
        ansadd(answer,'$');
    for(i=0;i<n;i++)
    {
        for(j=2;j<productions[i].size();j++)
        {
            if(productions[i][j]==c)
            {
                if(productions[i][j+1]!='\0')
                {
                    FIRST(ans,productions[i][j+1]);
                    for(k=0;ans[k]!='\0';k++)
                    {
                        if(ans[k]!='^')
                        ansadd(answer,ans[k]);
                    }
                    for(k=0 ;ans[k]!='\0';k++)
                        if(ans[k]=='^'&&j+2<productions[i].size()&&productions[i][j+2]!=productions[i][0])
                            FOLLOW(answer,ans,productions[i][j+2]);
                        else if(ans[k]=='^'&&productions[i][j]!=productions[i][0])
                            FOLLOW(answer,ans,productions[i][0]);
                }
                if(productions[i][j+1]=='\0'&&c!=productions[i][0])
                    FOLLOW(answer,ans,productions[i][0]);
            }
        }
    }
    return ;
}
int main()
{
    int i;
    char choice,c,answer[20],ans[20];
    cout<<"Enter the Number of Productions\n";
    cin>>n;
    cout<<"Enter the Productions\n";
    for(i=0;i<n;i++)
        cin>>productions[i];
    do
    {
        answer[0] = '\0';
        cout<<"Find the FIRST and FOLLOW of  : ";
        cin>>c;
        FIRST(ans,c);
        cout<<"FIRST = { ";
        for(i=0;ans[i]!='\0';i++)
        cout<<ans[i]<<" , ";
        cout<<"}\n";
        FOLLOW(answer,ans,c);
        cout<<"FOLLOW = { ";
        for(i=0;answer[i]!='\0';i++)
        cout<<answer[i]<<" , ";
        cout<<"}\n\n";
        cout<<"Press 'y' to continue : ";
        cin>>choice;
    }
    while(choice=='y'||choice =='Y');
    return 0;
}

