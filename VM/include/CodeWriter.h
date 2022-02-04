#ifndef CODEWRITER_H
#define CODEWRITER_H
#include <iostream>
#include <fstream>
#include "Parser.h"
using namespace std;
class CodeWriter
{
    public:
        CodeWriter();
        virtual ~CodeWriter();
        void setFileName(string filename);
        void writeArithmetic(string command);
        void writePushPop(Type,string , int);
        string filen;
    protected:

    private:
        int counter=0;

};

#endif // CODEWRITER_H
