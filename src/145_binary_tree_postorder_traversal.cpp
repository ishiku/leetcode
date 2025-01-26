// https://leetcode.com/problems/binary-tree-postorder-traversal/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

using namespace leetcode;

namespace {

std::vector<int> postorderTraversal(TreeNode *node) {
  std::vector<int> vec;

  std::stack<TreeNode *> st;
  TreeNode *last_visited = nullptr;
  while (node || !st.empty()) {
    if (node) {
      st.push(node);
      node = node->left;
    } else {
      auto peek = st.top();
      if (peek->right && (peek->right != last_visited)) {
        node = peek->right;
      } else {
        vec.push_back(peek->val);
        st.pop();
        last_visited = peek;
      }
    }
  }
  return vec;
}

} // namespace

class BinaryTreePostOrderTraversalTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

TEST_P(BinaryTreePostOrderTraversalTestFixture, shouldPass) {
  auto [tree_desc, vec_desc] = GetParam();
  auto tree = deserializeTree(tree_desc);
  auto vec = deserializeVector(vec_desc);

  auto result = postorderTraversal(tree.get());
  EXPECT_EQ(vec.size(), result.size());
  EXPECT_TRUE(std::equal(vec.begin(), vec.end(), result.begin()));
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    BinaryTreePostOrderTraversalTests,
    BinaryTreePostOrderTraversalTestFixture,
    ::testing::Values(
        std::make_tuple("", ""),        
        std::make_tuple("1,null,2,3", "3,2,1"),
        std::make_tuple("1,2,3,4,5,null,8,null,null,6,7,9", "4,6,7,5,2,9,8,3,1")

    )
);
// clang-format on