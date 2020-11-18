#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    currentLine = 0;
    buffer = new Buffer();
}
Editor::~Editor()
{
    this->buffer->~Buffer();
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    while(true){
        string text;
        getline(cin,text);
        if(text == ".") break;
        else{
            buffer->appendLine(text);
        }
    }
    // TODO: finish cmdAppend.
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }  else {
            buffer->appendLine(text);
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    if(start > end) throw "Delete range error";
    if(start <= 0 || start > this->buffer->Text->NumofLine || end > this->buffer->Text->NumofLine){
        throw "Line number out of range";
    }
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    if(line > this->buffer->Text->NumofLine)
        throw "Line number out of range";
    this->buffer->move(line);
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    if(start > end) throw "Number range error";
    if(start <= 0 || end > this->buffer->Text->NumofLine){
        throw "Line number out of range";
    }
    for(int i = start;i <= end; ++i){
        cout << i << '\t';
        cout << this->buffer->moveToLine(i) << endl;
    }
    this->buffer->move(end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if(cmd == "w"){
        throw "Filename not specified";
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        string s;
        if(cmd.size() == 2) throw "Filename not specified";
        for(int i = 2;i < cmd.size(); ++i){
            s += cmd[i];
        }
        this->buffer->writeToFile(s);
        return;
    }
    if(cmd == "1,$n"){
        cmdNumber(1,this->buffer->Text->NumofLine);
    }
    else{
        int start, end;
        char comma, type = ' ';
        stringstream ss(cmd);
        ss >> start;
        if (ss.eof()) {
            cmdNull(start);
            return;
        }
        ss >> comma >> end >> type;
        if (ss.good()) {
            if (type == 'n') {
                cmdNumber(start, end);
                return;
            } else if (type == 'd') {
                cmdDelete(start, end);
                return;
            }
        }
    throw "Bad/Unknown command";
    }
}
