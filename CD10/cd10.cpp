#include<iostream>
#include<stack>
using namespace std;
void FIRST(char[],char );
void FOLLOW(char[],char[],char );
void ansadd(char[],char);
void parsertable();
int n,x,y;
string productions[10];
char ans_table[10][10];
int main()
{
    int i,j,k,error=0,m,c;
    stack<char> s;
    string input;
    cout<<"Enter the Number of Productions\n";
    cin>>n;
    cout<<"Enter the Productions\n";
    for(i=0;i<n;i++)
    {
        cout<<i+1<<". ";
        cin>>productions[i];
    }
    cout<<"Enter the number of terminals\n";
    cin>>x;
    cout<<"Enter the terminals\n";
    for(i=0;i<x;i++)
    cin>>ans_table[0][i+1];
    ans_table[0][i+1] = '$';
    cout<<"Enter the number of non - terminals\n";
    cin>>y;
    cout<<"Enter the non - terminals in order of productions\n";
    for(i=0;i<y;i++)
    cin>>ans_table[i+1][0];
    for(i=1;i<=y;i++)
    {
        for(j=1;j<=x+1;j++)
            ans_table[i][j] = '-';
    }
    parsertable();

    cout<<"Enter the input string to be parsed\n";
    cin>>input;

    s.push('$');
    s.push(productions[0][0]);
    for(k=0;k<input.size();)
    {
        if(s.top()==input[k])
        {
             k++;
             s.pop();
            if(k==input.size())
                break;
        }
        for(i=1;i<=y&&s.top()!=ans_table[i][0];i++);
        for(j=1;j<=x+1&&input[k]!=ans_table[0][j];j++);
        if(i>y||j>x+1)
        {
            cout<<"Error in locating the table values "<<k<<"\n";
            error = 1;
            break;
        }
        c = (int)(ans_table[i][j]-48);
        if(c>9||c<0)
        {
            cout<<"Error in the production to be used "<<k<<"\n";
            error = 1;
            break;
        }
        s.pop();
        m=productions[c].size()-1;
        while(productions[c][m]!='='&&productions[c][m]!='^')
        {
            s.push(productions[c][m]);
            m--;
        }
    }
    if(error == 0 && s.empty()==1)
        cout<<"Input String successfully parsed\n";
    else cout<<"String cant be parsed\n";

    return 0;
}

void parsertable()
{
    int i,j,z,error=0,k,q,epsilon=0;
    char ans[20],answer[20];
    z=1;
    for(i=0;i<n;i++)
    {
        ans[0]='\0';
        answer[0]='\0';
        if(productions[i][0]!=ans_table[z][0])
            z++;
        if(productions[i][2]=='^')
        {
            FOLLOW(answer,ans,productions[i][0]);
            for(j=0;answer[j]!='\0';j++)
            {
                for(k=1;ans_table[0][k]!=answer[j];k++);
                     if(ans_table[z][k]=='-')
                        ans_table[z][k] = (char)(i+48);
                     else
                     {
                        cout<<"Error";
                        error = 1;
                     }
            }
        }
        else
        {
                q=2;
                while(productions[i][q]!='\0')
                {
                    epsilon=0;
                    FIRST(ans,productions[i][q]);
                    for(j=0;ans[j]!='\0';j++)
                    {
                            if(ans[j]!='^')
                            {
                                for(k=1;ans_table[0][k]!=ans[j]&&ans[j]!='^';k++);
                                    if(ans_table[z][k]=='-')
                                        ans_table[z][k] = (char)(i+48);
                                    else {
                                        cout<<"Error";
                                        error = 1;
                                    }
                            }
                     }
                     for(j=0;ans[j]!='\0';j++)
                     {

                         if(ans[j]=='^')
                         {
                             if(productions[i][q+1]=='\0')
                             {
                                 FOLLOW(answer,ans,productions[i][0]);
                                 for(j=0;answer[j]!='\0';j++)
                                 {
                                    for(k=1;ans_table[0][k]!=answer[j];k++);
                                        if(ans_table[z][k]=='-')
                                            ans_table[z][k] = (char)(i+48);
                                        else {
                                            cout<<"Error";
                                            error = 1;
                                        }
                                 }
                             }
                             epsilon=1;
                             break;
                         }
                     }
                     if(!epsilon)
                         break;
                     q++;
                }

            }
    }

    cout<<"The parser table is\n";

    for(i=0;i<=y;i++)
    {
        for(j=0;j<=x+1;j++)
            if((int)(ans_table[i][j]-47)>=1&&(int)(ans_table[i][j]-47)<=10)
            cout<<(int)(ans_table[i][j]-47)<<" ";
            else cout<<ans_table[i][j]<<" ";
        cout<<"\n";
    }


}

void ansadd(char ans[],char val)
{
    int k,i;
    for(k=0 ;ans[k]!='\0';k++)
        if(ans[k]==val)
            return;
    ans[k]=val;
    ans[k+1]='\0';
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
                    for(k=0 ;ans[k]!='\0';k++)
                    {
                        if(ans[k]!='^')
                        ansadd(answer,ans[k]);
                    }
                    for(k=0 ;ans[k]!='\0';k++)
                        if(ans[k]=='^'&&j+2<productions[i].size())
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

void FIRST(char* ans,char c)
{
    int i,j,k;
    char subans[20];
    int epsilon;
    subans[0] = '\0';
    ans[0] = '\0';
    if(!(isupper(c))||c=='('||c==')'||c=='*'||c=='+')
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
