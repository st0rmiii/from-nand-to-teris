#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main()
{
    extern ofstream ofile;
    string a,oname,iname;
    CodeWriter pro2;
    cin>>a;
    pro2.filen=a;
    a="E:\\"+a;
    oname=a+".vm";
    iname=a+".asm";
    Parser pro1(oname);
    pro2.setFileName(iname);
    while(pro1.hasMoreCommands())
    {
        pro1.advance();
        Type type=pro1.commandType();
        string arg1=pro1.arg1();
        int arg2=0;
        if(type==1||type==2||type==6||type==8)
            arg2=pro1.arg2();
        if(type==0)
            pro2.writeArithmetic(arg1);
        if(type==1||type==2)
            pro2.writePushPop(type,arg1,arg2);

        ofile<<endl;
    }

    return 0;
}
