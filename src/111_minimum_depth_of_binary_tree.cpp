// https://leetcode.com/problems/minimum-depth-of-binary-tree/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <tuple>

using namespace leetcode;

namespace {

// TC=O(N), SC=O(N)..O(LogN)
int minDepth(TreeNode *root) {
  if (root == nullptr)
    return 0;

  return std::min(minDepth(root->left), minDepth(root->right)) + 1;
}

} // namespace

class MinimumDepthOfBinaryTreeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {};

TEST_P(MinimumDepthOfBinaryTreeTestFixture, shouldPass) {
  auto [tree_desc, depth] = GetParam();
  auto tree = deserializeTree(tree_desc);

  EXPECT_EQ(minDepth(tree.get()), depth);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
  MinimumDepthOfBinaryTreeTests,
  MinimumDepthOfBinaryTreeTestFixture,
  ::testing::Values(
    std::make_tuple("", 0),
    std::make_tuple("1", 1),
    std::make_tuple("1,2", 1),
    std::make_tuple("1,null,2", 1),
    std::make_tuple("1,2,3", 2),
    std::make_tuple("1,2,3,null,null,15,7", 2)
  )  
);
// clang-format on