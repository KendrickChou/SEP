#pragma once

#include <string>

using std::string;

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    struct node{
        string line;
        node *pre = nullptr,*next = nullptr;
    };
    class ListBuffer{
    private:
        node *head;
        node *rear;
    public:
        int NumofLine = 0;
        ListBuffer();
        ~ListBuffer();
        void add(int Line,string s);
        node* move(int i);
        void deleteLine(int i);
        void deleteList();
        void showLine(int i);
        void insertText(const string &s,int &pos);
    };

public:
    ListBuffer *Text;
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) const;

    void move(int idx);

    void showLines(int from, int to) const;

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
