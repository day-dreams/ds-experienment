#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef char value_type;

enum rightOrLeft { right, left };

class node {
public:
  node *parent = nullptr, *left = nullptr, *right = nullptr;
  value_type value;
};

/*
  return the root of the tree
  every layer of the recuresion build the left and right child,
    but not set the left/right filed of parent
*/
node *buildTree(vector<value_type> before, vector<value_type> mid,
                node *parent) {
  // for debug
  // cout << before.size() << "----" << mid.size() << endl;
  if (before.size() == 2) {
    auto tem_root = new node();
    tem_root->value = before.front();
    tem_root->parent = parent;
    if (mid.front() == before.front()) {
      // b is the right child of a
      auto right_child = new node();
      right_child->value = before.back();
      right_child->parent = tem_root;
      tem_root->right = right_child;
    } else {
      // b is the left child of a
      cout << "----" << endl;
      auto left_child = new node();
      cout << "----" << endl;
      left_child->value = before.back();
      left_child->parent = tem_root;
      tem_root->left = left_child;
    }
    return tem_root;
  } else {
    auto tem_root = new node();

    tem_root->value = before.front();
    if (!parent)
      tem_root->parent = parent;
    auto pos_of_root = find(mid.begin(), mid.end(), before.front());
    auto pos_of_last = find(before.begin(), before.end(), *(pos_of_root - 1));
    // cout << "----53" << endl;
    vector<value_type> left_tree_mid(mid.begin(), pos_of_root);
    // cout << "----55" << endl;
    vector<value_type> right_tree_mid(pos_of_root + 1, mid.end());
    // cout << "----57" << endl;
    vector<value_type> left_tree_before(before.begin() + 1, pos_of_last + 1);
    // cout << "----59" << endl;
    vector<value_type> right_tree_before(pos_of_last + 1, before.end());
    // cout << "----61" << endl;
    if (left_tree_before.size() >= 2 && right_tree_before.size() >= 2) {
      tem_root->left = buildTree(left_tree_before, left_tree_mid, tem_root);
      tem_root->right = buildTree(right_tree_before, right_tree_mid, tem_root);
      return tem_root;
    } else if (left_tree_before.size() == 1 && right_tree_before.size() == 1) {
      auto left_child = new node();
      left_child->value = left_tree_before.front();
      auto right_child = new node();
      right_child->value = right_tree_before.front();
      tem_root->left = left_child;
      tem_root->right = right_child;
      return tem_root;
    } else if (left_tree_before.size() == 1) {
      tem_root->right = buildTree(right_tree_before, right_tree_mid, tem_root);
      auto left_child = new node();
      left_child->value = left_tree_before.front();
      tem_root->left = left_child;
      left_child->parent = tem_root;
      return tem_root;
    } else {
      tem_root->left = buildTree(left_tree_before, left_tree_mid, tem_root);
      auto right_child = new node();
      right_child->value = right_tree_before.front();
      tem_root->right = right_child;
      right_child->parent = tem_root;
      return tem_root;
    }
  }
}

void show_after(node *root) {
  if (root != nullptr) {
    show_after(root->left);
    show_after(root->right);
    cout << root->value << ' ';
  }
}
