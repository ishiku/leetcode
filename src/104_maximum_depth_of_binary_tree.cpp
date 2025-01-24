#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>

using namespace leetcode;

namespace {

int maxDepth(TreeNode *root) {
  if (!root)
    return 0;
  auto left = maxDepth(root->left);
  auto right = maxDepth(root->right);
  return std::max(left, right) + 1;
}

} // namespace

class MaxDepthOfBinaryTreeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {};

TEST_P(MaxDepthOfBinaryTreeTestFixture, shouldPass) {
  auto [tree_desc, max_depth] = GetParam();
  auto root = deserializeTree(tree_desc);

  EXPECT_EQ(maxDepth(root.get()), max_depth);
}

INSTANTIATE_TEST_SUITE_P(
    MaxDepthOfBinaryTreeTests, MaxDepthOfBinaryTreeTestFixture,
    ::testing::Values(std::make_tuple("", 0), std::make_tuple("1", 1),
                      std::make_tuple("1,null,2", 2), std::make_tuple("1,2", 2),
                      std::make_tuple("1,2,3", 2)));