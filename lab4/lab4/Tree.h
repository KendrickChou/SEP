//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  TreeNode *lnode = nullptr,*rnode = nullptr;

public:
  /* methods */
  TreeNode();
  TreeNode(int x,int y);
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  vector<TreeNode> node_vec;

public:
  /* methods */
  BinaryDimonTree();     /* DO NOT CHANGE */
  ~BinaryDimonTree();
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void recur_search(TreeNode *cur, TreeNode *test, double &min_distance, TreeNode **guess,bool digit);
  void buildTree(TreeNode *root,int left,int right,bool digital,bool flag);
  double distance(TreeNode &node1, TreeNode &node2);
};

#endif //C_BINARYDIMEN_TREE_H
