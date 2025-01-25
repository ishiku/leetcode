// https://leetcode.com/problems/balanced-binary-tree/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <tuple>

using namespace leetcode;

namespace {

int balancedDepth(TreeNode *root) {
  if (root == nullptr)
    return 0;

  int left = balancedDepth(root->left);
  int right = balancedDepth(root->right);

  if (left < 0 || right < 0 || std::abs(left - right) > 1)
    return -1;
  return std::max(left, right) + 1;
}

// TC=O(N), SC=O(LogN)
bool isBalanced(TreeNode *root) { return (balancedDepth(root) >= 0); }

} // namespace

class IsBalancedBinaryTreeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, bool>> {};

TEST_P(IsBalancedBinaryTreeTestFixture, shouldPass) {
  auto [tree_desc, balanced] = GetParam();
  auto tree = deserializeTree(tree_desc);

  EXPECT_EQ(isBalanced(tree.get()), balanced);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    IsBalancedBinaryTreeTests,
    IsBalancedBinaryTreeTestFixture,
    ::testing::Values(
        std::make_tuple("", true),
        std::make_tuple("1", true),
        std::make_tuple("1,2", true),
        std::make_tuple("1,null,3", true),
        std::make_tuple("1,2,null,4", false),
        std::make_tuple("3,9,20,null,null,15,7", true),
        std::make_tuple("1,2,2,3,3,null,null,4,4", false)
    )
);
// clang-format on