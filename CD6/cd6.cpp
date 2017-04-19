#include<iostream>
#include<string.h>
using namespace std;
int findMinLength(char arr[10][10], int n)
{
    int min = strlen(arr[0]);

    for (int i=1; i<n; i++)
        if (strlen(arr[i]) < min)
            min = strlen(arr[i]);

    return(min);
}

string commonPrefix(char arr[10][10], int n)
{
    int minlen = findMinLength(arr, n);

    string result;
    char current;

    for (int i=0; i<minlen; i++)
    {
        current = arr[0][i];

        for (int j=1 ; j<n; j++)
            if (arr[j][i] != current)
                return result;

        result.push_back(current);
    }

    return (result);
}
int main()
{
    int i,j,m,n,k,x;
    char output[10][10],productions[10][10];
    string ans,ans1;
    cout<<"Enter the number of Productions\n";
    cin>>n;
    cout<<"Enter the Productions\n";
    for(i=0;i<n;i++)
    cin>>productions[i];
    ans = commonPrefix (productions, n);
    m =ans.size();
    for(j=0;j<m;j++)
       output[0][j] = productions[0][j];
    output[0][m] = productions[0][0];
    output[0][m+1] = '\'';
    output[0][m+2] = '\0';
    j=1;
    for(i=0;i<n;i++)
    {
        if(strlen(productions[i])<=m)
        {
            output[j][0] = productions[i][0];
            output[j][1] = '\'';
            output[j][2] = '=';
            output[j][3] = '$';
            output[j][4] = '\0';
        }
        else{
            output[j][0] = productions[i][0];
            output[j][1] = '\'';
            output[j][2] = '=';
            x=3;
            for(k=m;k<strlen(productions[i]);x++,k++)
                output[j][x] = productions[i][k];
            output[j][x] = '\0';
        }
        j++;
    }
    cout<<"The final productions are\n";
    for(i=0;i<j;i++)
        cout<<output[i]<<"\n";
    return 0;
}
