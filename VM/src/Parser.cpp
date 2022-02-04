#include "Parser.h"
#include <cstring>
using namespace std;
ifstream ifile;

void deleteAllMark(string &s, const string &mark)
{
	size_t nSize = mark.size();
	while(1)
	{
		size_t pos = s.find(mark);
		if(pos == string::npos)
		{
			return;
		}

		s.erase(pos, nSize);
	}
}
Parser::Parser(string name)
{

    ifile.open(name,ios::in);
    if(!ifile) cout<<"can not find"<<endl;
}
bool Parser::hasMoreCommands()
{
    return !(ifile.peek()==EOF);
}

void Parser::advance()
{

    char a[100];
    ifile.getline(a,100);
    for(int i=0;a[i]!='\0';i++)
    {
        if(a[i]=='/') {a[i]='\0';break;}
    }
    int i=0,j=0;
    while(a[j]!='\0')
    {
        if(a[j]!=' ')
        {
            a[i++]=a[j++];
        }
        else
        {
            a[i++]=a[j++];
            while(a[j]==' ')
            {
                j++;
            }
        }
    }
    a[i]='\0';
    //deleteAllMark(command," ");
    command = a;
    type=commandType();
    return;
}

Type Parser::commandType()
{
    if(command.find("push")!=-1) return (Type)1;
    if(command.find("pop")!=-1) return (Type)2;
    if(command.find("label")!=-1) return (Type)3;
    if(command.find("if")!=-1) return (Type)5;
    if(command.find("goto")!=-1) return (Type)4;
    if(command.find("function")!=-1) return (Type)6;
    if(command.find("return")!=-1) return (Type)7;
    if(command.find("call")!=-1) return (Type)8;
    return (Type)0;
}
Parser::~Parser()
{
    ifile.close();
}
string Parser::arg1()
{
    if(type==0) return command;
    else
    {
        string arg=command.substr(command.find(" ")+1,command.find_last_of(" ")-command.find(" ")-1);
        return arg;
    }

}
int Parser::arg2()
{
    string arg=command.substr(command.find_last_of(" "));
    char a[17];
    strcpy(a,arg.data());
    int arg1=atoi(a);
    return arg1;
}
