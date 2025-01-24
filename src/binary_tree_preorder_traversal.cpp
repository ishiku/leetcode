#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <stack>
#include <tuple>
#include <vector>

using namespace leetcode;

namespace {

void preorderTraversalRecursiveImpl(TreeNode *root, std::vector<int> &vec) {
  if (root == nullptr)
    return;
  vec.push_back(root->val);
  preorderTraversalRecursiveImpl(root->left, vec);
  preorderTraversalRecursiveImpl(root->right, vec);
}

// TC=O(N), SC=O(logN)..O(N)
std::vector<int> preorderTraversalRecursive(TreeNode *root) {
  std::vector<int> vec;
  preorderTraversalRecursiveImpl(root, vec);
  return vec;
}

// TC=O(N), SC=O(logN)..O(N)
std::vector<int> preorderTraversalIterative(TreeNode *root) {
  if (root == nullptr)
    return {};

  std::vector<int> vec;
  std::stack<TreeNode *> st;
  st.push(root);
  while (!st.empty()) {
    auto node = st.top();
    st.pop();
    vec.push_back(node->val);
    if (node->right)
      st.push(node->right);
    if (node->left)
      st.push(node->left);
  }

  return vec;
}

} // namespace

class BinaryTreePreorderTraversalTestFixture
    : public ::testing::TestWithParam<
          std::tuple<std::string, std::vector<int>>> {
protected:
  ::testing::AssertionResult
  testTravers(std::function<std::vector<int>(TreeNode *)> fn) {
    auto [tree_description, expected_output] = GetParam();

    auto root = deserializeTree(tree_description);
    auto output = fn(root.get());

    if (output.size() != expected_output.size() ||
        !std::equal(output.begin(), output.end(), expected_output.begin()))
      return ::testing::AssertionFailure() << "output != expected_output\n";

    return ::testing::AssertionSuccess();
  }
};

TEST_P(BinaryTreePreorderTraversalTestFixture, shouldPassIterative) {
  EXPECT_TRUE(testTravers(preorderTraversalIterative));
}

TEST_P(BinaryTreePreorderTraversalTestFixture, shouldPassRecursive) {
  EXPECT_TRUE(testTravers(preorderTraversalRecursive));
}

INSTANTIATE_TEST_SUITE_P(
    BinaryTreePreorderTraversalTests, BinaryTreePreorderTraversalTestFixture,
    ::testing::Values(std::make_tuple("", std::vector<int>{}),
                      std::make_tuple("1", std::vector<int>{1}),
                      std::make_tuple("1,2,3", std::vector<int>{1, 2, 3}),
                      std::make_tuple("1,null,2,3",
                                      std::vector<int>{1, 2, 3})));