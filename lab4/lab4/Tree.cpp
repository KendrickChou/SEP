#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
TreeNode::TreeNode(int x,int y){
    data[0] = x;
    data[1] = y;
}

TreeNode::TreeNode(){

}

int TreeNode::getX(){
    return this->data[0];
}

int TreeNode::getY(){
    return this->data[1];
}

TreeNode::~TreeNode(){
}

/* ************************************ */

BinaryDimonTree::BinaryDimonTree(){
    root = nullptr;
}

TreeNode* BinaryDimonTree::find_nearest_node(int x,int y){
    TreeNode *cur = root;
    TreeNode *guess = nullptr;
    double min_distance = 9000000000;
    TreeNode *test = new TreeNode(x,y);
    recur_search(cur,test,min_distance,&guess,0);
    return guess;
}

double BinaryDimonTree::distance(TreeNode &node1, TreeNode &node2){
    double dis;
    long long int x = (node1.getX() - node2.getX()) * (node1.getX() - node2.getX());
    long long int y = (node1.getY() - node2.getY()) * (node1.getY() - node2.getY());
    dis = (double)sqrt(x + y);
    return dis;
}

void BinaryDimonTree::recur_search(TreeNode *cur, TreeNode *test, double &min_distance, TreeNode **guess,bool digit){
    if(cur == nullptr) return;
    double cur_dis = distance(*cur,*test);
   if(cur_dis < min_distance){
       min_distance = cur_dis;
       *guess = cur;
   }
   else if(cur_dis - min_distance <= 0.00000000001){
       if(cur->data[0] < (*guess)->data[0]){
           *guess = cur;
       }
       else if(cur->data[0] == (*guess)->data[0] && cur->data[1] < (*guess)->data[1]){
           *guess = cur;
       }
   }
   if(cur->data[digit] > test->data[digit]){
       recur_search(cur->lnode,test,min_distance,guess,!digit);
       if(min_distance >= (double)(cur->data[digit] - test->data[digit])){
           recur_search(cur->rnode,test,min_distance,guess,!digit);
       }
   }
   else{
       recur_search(cur->rnode,test,min_distance,guess,!digit);
       if(min_distance >= (double)(test->data[digit] - cur->data[digit])){
           recur_search(cur->lnode,test,min_distance,guess,!digit);
       }
   }
}

static bool compX(TreeNode &n1,TreeNode &n2){
    return (n1.getX() < n2.getX());
}
static bool compY(TreeNode &n1,TreeNode &n2){
    return (n1.getY() < n2.getY());
}

istream &operator>>(istream &in, BinaryDimonTree &tree){
    int num_node,x,y;
    in >> num_node;
    for(int i = 0;i < num_node; ++i){
        in >> x;
        in >> y;
        TreeNode temp(x,y);
        tree.node_vec.push_back(temp);
    }
    bool digital = false;
    int mid = (num_node - 1) / 2;
    nth_element(tree.node_vec.begin(),tree.node_vec.begin() + mid,tree.node_vec.begin() + num_node,compX);
    tree.root = &tree.node_vec[mid];
    if(mid - 1 >= 0){
        tree.buildTree(tree.root,0,mid - 1,!digital,false);
    }
    if(mid + 1 <= num_node - 1){
        tree.buildTree(tree.root,mid + 1,num_node - 1,!digital,true);
    }
}

void BinaryDimonTree::buildTree( TreeNode *root, int left, int right,bool digital,bool flag){
        int mid = (left + right) / 2;
        if(!digital)
            nth_element(node_vec.begin() + left,node_vec.begin() + mid,node_vec.begin() + right + 1,compX);
        else
            nth_element(node_vec.begin() + left,node_vec.begin() + mid,node_vec.begin() + right + 1,compY);
        if(!flag){
            root->lnode = &node_vec[mid];
        }
        else
            root->rnode = &node_vec[mid];
        if(mid - 1 >= left){
            buildTree(&node_vec[mid],left,mid - 1,!digital,false);
        }
        if(mid + 1 <= right){
            buildTree(&node_vec[mid],mid + 1,right,!digital,true);
        }
}

BinaryDimonTree::~BinaryDimonTree(){
}


