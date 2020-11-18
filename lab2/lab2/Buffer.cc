#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer
Buffer::ListBuffer::ListBuffer() {
    head = new node;
    rear = new node;
    head->next = rear;
    rear->pre = head;
}

Buffer::ListBuffer::~ListBuffer(){
    deleteList();
}

//add after LinePos
void Buffer::ListBuffer::add(int Line,string s){
    node *N = new node;
    N->line = s;
    node *OriginNode = move(Line);
    N->pre = OriginNode;
    N->next = OriginNode->next;
    OriginNode->next->pre = N;
    OriginNode->next = N;
    ++NumofLine;
}

// "1"base
Buffer::node* Buffer::ListBuffer::move(int i){
    node *tar = head;
    int I = i;
    while(i > 0){
        tar = tar->next;
        --i;
    }
    return tar;
}

void Buffer::ListBuffer::deleteLine(int i){
    node *dtar = move(i);
    node *P,*N;
    P = dtar->pre;
    N = dtar->next;
    P->next = N;
    N->pre = P;
    delete dtar;
    --NumofLine;
}

void Buffer::ListBuffer::deleteList(){
    int totalLine = NumofLine;
    for(int i = 1;i <= totalLine; ++i){
        deleteLine(i);
    }
    delete head;
    delete rear;
}

void Buffer::ListBuffer::showLine(int i){
    node *N = move(i);
    std::cout << N->line << std::endl;
}

Buffer::Buffer() {
    currentLineNum = 0;
    Text = new ListBuffer;
}

Buffer::~Buffer() {
    Text->deleteList();
}

void Buffer::writeToFile(const string &filename) const {
    std::fstream file;
    int Bytes = 0;
    file.open(filename,std::ios::out);
    int end = this->Text->NumofLine;
    for(int i = 1;i <= end;++i){
        string contain = this->moveToLine(i);
        Bytes += contain.length();
        file << contain;
        file << '\n';
        Bytes += 1;
    }
    file.close();
    std::cout << Bytes << " byte(s) written" << std::endl;
    return;
}

void Buffer::showLines(int from, int to) const {
    for(int i = from; i <= to; ++i){
        Text->showLine(i);
    }
}

void Buffer::deleteLines(int from, int to){
    this->move(from);
    for(int i = from; i <= to; ++i){
        Text->deleteLine(from);
        if(Text->NumofLine < currentLineNum){
            currentLineNum =  Text->NumofLine;
        }
    }
}

void Buffer::insertLine(const string &text){
    if(currentLineNum == 0){
        this->Text->add(currentLineNum,text);
        ++currentLineNum;
    }
    else{
        --currentLineNum;
        this->Text->add(currentLineNum,text);
        ++currentLineNum;
    }
}

void Buffer::appendLine(const string &text){
     this->Text->add(currentLineNum,text);
     ++currentLineNum;

}

const string &Buffer::moveToLine(int idx) const {
    return this->Text->move(idx)->line;
}

void Buffer::move(int idx){
    currentLineNum = idx;
}
