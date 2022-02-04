#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>

using namespace std;

enum Type{C_ARITHMETIC,C_PUSH,C_POP,C_LABEL,C_GOTO,C_IF,C_FUNCTION,C_RETURN,C_CALL};
class Parser
{
    public:
        Parser(string name);
        virtual ~Parser();
        bool hasMoreCommands();
        void advance();
        string arg1();
        int arg2();
        Type commandType();
    protected:

    private:
        string command;
        Type type;
};

#endif // PARSER_H
