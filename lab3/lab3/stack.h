#ifndef STACK_H
#define STACK_H

#endif // STACK_H

#include <iostream>

template <class T>
class stack{
private:
    struct node{
        T value = 0;
        node *next;
        node(T val){
            value = val;
            next = nullptr;
        };
        node(){};
    };
    node *head = new node;
public:
    int size = 0;
    void push(T val){
        node *inNode;
        inNode = new node(val);
        if(head->next == nullptr){
            head->next = inNode;
        }
        else{
            inNode->next = head->next;
            head->next = inNode;
        }
        ++size;
        return;
    }
    T pop(){
        node *temp = head->next;
        if(temp != nullptr){
            head->next = temp->next;
            T val = temp->value;
            delete temp;
            --size;
            return val;
        }
        else{
            return -1;
        }
    }
    T visit(int i){
        node *tar = head;
        while(i > 0){
            tar = tar->next;
            --i;
        }
        return tar->value;
    }
    void clear(){
        node *dNode;
      while(size > 0){
          dNode = head->next;
          head->next = dNode->next;
          delete dNode;
          --size;
      }
    }
    ~stack(){
        node *dNode;
      for(int i = 0; i < size; ++i){
          dNode = head->next;
          head->next = dNode->next;
          delete dNode;
      }
      delete head;
    }
};
