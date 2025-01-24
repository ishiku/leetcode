#pragma once

#include <memory>
#include <queue>
#include <sstream>
#include <string>

namespace leetcode {

struct TreeNode {
  using Ptr = std::unique_ptr<TreeNode, void (*)(TreeNode *)>;
  int val{};
  TreeNode *left{};
  TreeNode *right{};
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

inline void destroyTree(TreeNode *root) {
  if (root == nullptr)
    return;
  destroyTree(root->left);
  destroyTree(root->right);
  delete root;
}

inline TreeNode::Ptr deserializeTree(std::string const &input) {
  if (input.empty())
    return {nullptr, destroyTree};

  TreeNode *root{};
  std::queue<TreeNode *> parents;

  constexpr char DELIM = ',';
  std::istringstream is(input);
  std::string tmp;
  bool left_child = true;
  while (std::getline(is, tmp, DELIM)) {
    TreeNode *node{};
    if (tmp != "null")
      node = new TreeNode(std::stoi(tmp));

    if (parents.empty())
      root = node;
    else {

      if (left_child)
        parents.front()->left = node;
      else
        parents.front()->right = node;

      if (!left_child)
        parents.pop();

      left_child = !left_child;
    }

    if (node)
      parents.push(node);
  }

  return {root, destroyTree};
}
} // namespace leetcode
