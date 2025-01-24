#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <tuple>
#include <vector>

using namespace leetcode;

namespace {

void inorderTraversalRecursiveImpl(TreeNode *root, std::vector<int> &vec) {
  if (root == nullptr)
    return;
  inorderTraversalRecursiveImpl(root->left, vec);
  vec.push_back(root->val);
  inorderTraversalRecursiveImpl(root->right, vec);
}

// TC=O(N), SC=O(LogN)..O(N)
std::vector<int> inorderTraversalRecursive(TreeNode *root) {
  std::vector<int> vec;
  inorderTraversalRecursiveImpl(root, vec);
  return vec;
}

// TC=O(N), SC=O(LogN)..O(N)
std::vector<int> inorderTraversalIterative(TreeNode *node) {
  std::vector<int> vec;
  std::stack<TreeNode *> st;
  while (!st.empty() || node)
    if (node) {
      st.push(node);
      node = node->left;
    } else {
      node = st.top();
      st.pop();
      vec.push_back(node->val);
      node = node->right;
    }

  return vec;
}

} // namespace

class BinaryTreeInorderTraversalTestFixture
    : public ::testing::TestWithParam<
          std::tuple<std::string, std::vector<int>>> {
protected:
  ::testing::AssertionResult testTravers(std::vector<int> (*fn)(TreeNode *)) {
    auto [tree_description, expected_output] = GetParam();

    auto root = deserializeTree(tree_description);
    auto output = fn(root.get());

    if (output.size() != expected_output.size() ||
        !std::equal(output.begin(), output.end(), expected_output.begin()))
      return ::testing::AssertionFailure() << "output != expected_output\n";

    return ::testing::AssertionSuccess();
  }
};

TEST_P(BinaryTreeInorderTraversalTestFixture, shouldPassIterative) {
  EXPECT_TRUE(testTravers(inorderTraversalIterative));
}

TEST_P(BinaryTreeInorderTraversalTestFixture, shouldPassRecursive) {
  EXPECT_TRUE(testTravers(inorderTraversalRecursive));
}

INSTANTIATE_TEST_SUITE_P(
    BinaryTreeInorderTraversalTests, BinaryTreeInorderTraversalTestFixture,
    ::testing::Values(std::make_tuple("", std::vector<int>{}),
                      std::make_tuple("1", std::vector<int>{1}),
                      std::make_tuple("1,2,3", std::vector<int>{2, 1, 3}),
                      std::make_tuple("1,null,2,3",
                                      std::vector<int>{1, 3, 2})));