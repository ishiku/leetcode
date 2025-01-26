// https://leetcode.com/problems/path-sum/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <string>
#include <tuple>

using namespace leetcode;

namespace {

// TC=O(N), SC=O(LogN)..O(N)
bool hasPathSum(TreeNode *root, int targetSum) {
  if (root == nullptr)
    return false;

  targetSum -= root->val;
  if (!root->left && !root->right)
    return (targetSum == 0);

  return hasPathSum(root->left, targetSum) ||
         hasPathSum(root->right, targetSum);
}

} // namespace

class PathSumTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int, bool>> {};

TEST_P(PathSumTestFixture, shouldPass) {
  auto [tree_desc, target, expected_result] = GetParam();
  auto tree = deserializeTree(tree_desc);
  EXPECT_EQ(hasPathSum(tree.get(), target), expected_result);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    PathSumTests,
    PathSumTestFixture,
    ::testing::Values(
        std::make_tuple("", 0, false),
        std::make_tuple("1", 1, true),
        std::make_tuple("5,4,8,11,null,13,4,7,2,null,null,null,1", 22, true),
        std::make_tuple("1,2,3", 5, false)
    )
);
// clang-format on