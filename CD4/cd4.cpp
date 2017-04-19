#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
int isdigit(string str)
{
    if(str=="")
        return 0;
    int n,i;
    n = str.size();
    for(i=0;i<n;i++)
    {
        if(str[i]>=48&&str[i]<=57)
            continue;
        else return 0;
    }
    return 1;
}
int isidentifier(string str)
{
    if(str=="")
        return 0;
    int i;
	if(str[0]>=97&&str[0]<=122||(str[0]>=65&&str[0]<=90))
	{
		for(i=1;i<str.size();i++)
		{
			if(str[i]>=97&&str[i]<=122||(str[i]>=65&&str[i]<=90)||str[i]=='_')
                continue;
            else return 0;
		}
	}
	return true;
}
int isoperator(string str)
{
    if(str=="")
        return 0;
	if(str.compare("+")==0||str.compare("-")==0||str.compare("*")==0||str.compare("/")==0||str.compare(")")==0
    ||str.compare("(")==0||str.compare(";")==0||str.compare("==")==0||str.compare("=")==0||str.compare("{")==0
    ||str.compare("}")==0||str.compare(">>")==0||str.compare("<")==0||str.compare(">")==0||str.compare("->")==0
    ||str.compare("<<")==0||str.compare("#")==0)
	return 1;
	else return 0;
}
int iskeyword(string str)
{
    if(str=="")
        return 0;
	if(str.compare("char")==0||str.compare("for")==0||str.compare("while")==0||str.compare("int")==0||str.compare("float")==0
    ||str.compare("include")==0||str.compare("using")==0||str.compare("namespace")==0||str.compare("std")==0||
    str.compare("cout")==0||str.compare("cin")==0||str.compare("string")==0||str.compare("if")==0||
    str.compare("else")==0||str.compare("return")==0||str.compare("double")==0||str.compare("switch")==0)
	return 1;
	else return 0;
}
int main()
{
    char ch,ch2='a';
    string str="",s="",s2="";
    vector<string> keywords,identifiers,digit,operators;
    int dig=0,key=0,op=0,ident=0,i;
    fstream fin("source.txt", fstream::in);
    while (fin >> noskipws >> ch)
    {
        s="";
        s2="";
        s=s+ch;
        s2=s2+ch2;
        if(ch!=' '&&ch!='\n'&&ch!='\t'&&!isoperator(s))
            str = str + ch ;
        else
        {
            if(isdigit(str))
            {
                dig++;
                if(find(digit.begin(),digit.end(),str)==digit.end())
                digit.push_back(str) ;
            }
            else if(iskeyword(str))
            {
                key++;
                if(find(keywords.begin(),keywords.end(),str)==keywords.end())
                keywords.push_back(str) ;
            }
            else if(isidentifier(str))
            {
                ident++;
                if(find(identifiers.begin(),identifiers.end(),str)==identifiers.end())
                identifiers.push_back(str) ;
            }
            else ;
            if(s.compare("")!=0&&isoperator(s))
            {
                op++;
                if(isoperator(s2))
                {
                    if(find(operators.begin(),operators.end(),s2)!=operators.end())
                    {
                        s = s2+s;
                        op--;
                    }
                }
                if(find(operators.begin(),operators.end(),s)==operators.end())
                operators.push_back(s) ;
            }
            str="";
        }
        ch2=ch;
    }

    cout<<"Total Number of Tokens: "<<key+op+ident+dig<<"\n\n";

    cout<<"No. of Keywords = "<<keywords.size()<<"\n";
    cout<<"Keywords are: ";
    for(i=0;i<keywords.size();i++)
    cout<<keywords[i]<<" , ";
    cout<<"\n\n";
    cout<<"No. of Identifier = "<<identifiers.size()<<"\n";
    cout<<"Identifiers are: ";
    for(i=0;i<identifiers.size();i++)
    cout<<identifiers[i]<<" , ";
    cout<<"\n\n";
    cout<<"No. of Operators = "<<operators.size()<<"\n";
    cout<<"Operators are: ";
    for(i=0;i<operators.size();i++)
    cout<<operators[i]<<" , ";
    cout<<"\n\n";
    cout<<"No. of digits(Numbers/Constants) = "<<digit.size()<<"\n";
    cout<<"Number/Constants are: ";
    for(i=0;i<digit.size();i++)
    cout<<digit[i]<<" , ";
    cout<<"\n\n";

    return 0;
}

