#include "CodeWriter.h"
ofstream ofile;
CodeWriter::CodeWriter()
{
}

CodeWriter::~CodeWriter()
{
    ofile.close();
}
void CodeWriter::setFileName(string filename)
{
    ofile.open(filename);

}
void CodeWriter::writeArithmetic(string command)
{
    if(command=="add") {ofile<<"@SP"<<endl<<"AM=M-1"<<endl<<"D=M"<<endl<<"A=A-1"<<endl<<"M=D+M"<<endl;return;}
    if(command=="sub") {ofile<<"@SP"<<endl<<"AM=M-1"<<endl<<"D=M"<<endl<<"A=A-1"<<endl<<"M=M-D"<<endl;return;}
    if(command=="neg") {ofile<<"@SP"<<endl<<"A=M"<<endl<<"A=A-1"<<endl<<"M=-M"<<endl;return;}
    if(command=="eq")
    {
        string labalname="Arithmetic"+to_string(counter);
        cout<<labalname<<endl;
        ofile<<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M\n"
        <<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M-D\n"
        <<"@"<<labalname<<endl
        <<"D;JEQ\n"
        <<"D=1\n"
        <<"("<<labalname<<")\n"
        <<"@SP\n"
        <<"A=M\n"
        <<"D=D-1\n"
        <<"M=D\n"
        <<"@SP\n"
        <<"M=M+1\n";
        counter++;
        return;
    }
    if(command=="gt")
    {
        string Tlabalname="Arithmetic"+to_string(counter)+"T";
        string Flabalname="Arithmetic"+to_string(counter)+"F";
        ofile<<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M\n"
        <<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M-D\n"
        <<"@"<<Tlabalname<<endl
        <<"D;JGT\n"
        <<"D=0\n"
        <<"@"<<Flabalname<<endl
        <<"0;JEQ\n"
        <<"("<<Tlabalname<<")\n"
        <<"D=-1\n"
        <<"("+Flabalname+")\n"
        <<"@SP\n"
        <<"A=M\n"
        <<"M=D\n"
        <<"@SP\n"
        <<"M=M+1\n";
        counter++;
        return;
    }
    if(command=="lt")
    {
        string Tlabalname="Arithmetic"+to_string(counter)+"T";
        string Flabalname="Arithmetic"+to_string(counter)+"F";
        ofile<<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M\n"
        <<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M-D\n"
        <<"@"<<Tlabalname<<endl
        <<"D;JLT\n"
        <<"D=0\n"
        <<"@"<<Flabalname<<endl
        <<"0;JEQ\n"
        <<"("<<Tlabalname<<")\n"
        <<"D=-1\n"
        <<"("+Flabalname+")\n"
        <<"@SP\n"
        <<"A=M\n"
        <<"M=D\n"
        <<"@SP\n"
        <<"M=M+1\n";
        counter++;
        return;
    }
    if(command=="and")
    {
        ofile<<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M\n"
        <<"A=A-1\n"
        <<"M=D&M\n";
        return;
    }
    if(command=="or")
    {
        ofile<<"@SP\n"
        <<"AM=M-1\n"
        <<"D=M\n"
        <<"A=A-1\n"
        <<"M=D|M\n";
        return;
    }
    if(command=="not")
    {
        ofile<<"@SP\n"
        <<"A=M\n"
        <<"A=A-1\n"
        <<"M=!M\n";
        return;
    }
}

void CodeWriter::writePushPop(Type type,string segment,int index)
{
    if(type==1){
        string num=to_string(index);
        if(segment=="constant")
        {
            ofile<<"@"<<num<<endl
            <<"D=A\n"
            <<"@SP\n"
            <<"A=M\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"M=M+1\n";
            return;
        }
        if(segment=="local"||segment=="argument"||segment=="this"||segment=="that")
        {
            string des;
            if(segment=="local") des="LCL";
            else if(segment=="argument") des="ARG";
            else if(segment=="this") des="THIS";
            else if(segment=="that") des="THAT";
            ofile<<"@"<<des<<endl
            <<"D=M\n"
            <<"@"<<num<<endl
            <<"A=D+A\n"
            <<"D=M\n"
            <<"@SP\n"
            <<"A=M\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"M=M+1\n";
            return;
        }
        if(segment=="static")
        {
            ofile<<"@"<<filen<<"."<<to_string(index)<<endl
            <<"D=M\n"
            <<"@SP\n"
            <<"A=M\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"M=M+1\n";
            return;
        }
        if(segment=="pointer")
        {
            num="R"+to_string(index+3);
            ofile<<"@"<<num<<endl
            <<"D=M\n"
            <<"@SP\n"
            <<"A=M\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"M=M+1\n";
            return;
        }
         if(segment=="temp")
        {
            num="R"+to_string(index+5);
            ofile<<"@"<<num<<endl
            <<"D=M\n"
            <<"@SP\n"
            <<"A=M\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"M=M+1\n";
            return;
        }
    }

    if(type==2) {
        string num=to_string(index);
        if(segment=="local"||segment=="argument"||segment=="this"||segment=="that")
        {
            string des;
            if(segment=="local") des="LCL";
            else if(segment=="argument") des="ARG";
            else if(segment=="this") des="THIS";
            else if(segment=="that") des="THAT";
            ofile<<"@"<<des<<endl
            <<"D=M\n"
            <<"@"<<num<<endl
            <<"D=D+A\n"
            <<"@R13\n"
            <<"M=D\n"
            <<"@SP\n"
            <<"AM=M-1\n"
            <<"D=M\n"
            <<"@R13\n"
            <<"A=M\n"
            <<"M=D\n";
            return;
        }
         if(segment=="static")
        {
            ofile<<"@SP\n"
            <<"AM=M-1\n"
            <<"D=M\n"

            <<"@"<<filen<<"."<<to_string(index)<<endl
            <<"M=D\n";
            return;
        }
        if(segment=="pointer")
        {
            num="R"+to_string(index+3);
            ofile<<"@SP\n"
            <<"AM=M-1\n"
            <<"D=M\n"
            <<"@"<<num<<endl
            <<"M=D\n";
            return;
        }
        if(segment=="temp")
        {
            num="R"+to_string(index+5);
            ofile<<"@SP\n"
            <<"AM=M-1\n"
            <<"D=M\n"
            <<"@"<<num<<endl
            <<"M=D\n";
            return;
        }
    }
}
