#include<iostream>
#include<string.h>
#include<ctype.h>
using namespace std;
string s;
int i=0;
int E();
int T();
int Edash();
int Tdash();
int F();
int E()
{
    T();
    Edash();
    return 0;
}
int T()
{
    F();
    Tdash();
    return 0;
}
int Edash()
{
    if(s[i]=='+')
    {
        i++;
        T();
        Edash();
    }
    return 0;
}
int Tdash()
{
    if(s[i]=='*')
    {
        i++;
        F();
        Tdash();
    }
    return 0;
}
int F()
{

    if(s[i]=='(')
    {
        i++;
        E();
        if(s[i]==')')
        i++;
        else return 0;
    }
    else if(isalnum(s[i]))
    i++;
    return 0;
}

int main()
{

    int n;
    cout<<"The Grammar is\n1. E=TE'\n2. T=FT'\n3. E'=+TE'\n4. T'=*FT'\n5. F=(E)\n6. F=i\n7. E'=^\n8. T'=^\n";
    cout<<"Enter the string to parse\n";
    cin>>s;
    n=s.size();
    int m = E();
    if(i==n)
        cout<<"Accepted\n";
    else cout<<"Not Accepted\n";
    return 0;
}
