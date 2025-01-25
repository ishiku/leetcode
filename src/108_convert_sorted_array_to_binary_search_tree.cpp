// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <string>
#include <tuple>

using namespace leetcode;

namespace {

TreeNode *arrayRangeToBT(std::vector<int> const &nums, int L, int R) {
  if (L > R)
    return nullptr;

  int M = L + (R - L) / 2;
  TreeNode *root = new TreeNode(nums[M]);
  root->left = arrayRangeToBT(nums, L, M - 1);
  root->right = arrayRangeToBT(nums, M + 1, R);

  return root;
}

// TC=O(N), SC=O(LogN)
TreeNode *sortedArrayToBST(std::vector<int> nums) {
  return arrayRangeToBT(nums, 0, nums.size() - 1);
}

} // namespace

class SortedArrayToBSTTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

TEST_P(SortedArrayToBSTTestFixture, shouldPass) {
  auto [vec_desc, tree_desc] = GetParam();
  auto nums = deserializeVector(vec_desc);
  auto expected_tree = deserializeTree(tree_desc);
  auto result_tree = createTree(sortedArrayToBST(nums));

  EXPECT_TRUE(isEqualTree(expected_tree.get(), result_tree.get()));
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    SortedArrayToBSTTests, 
    SortedArrayToBSTTestFixture,
    ::testing::Values(
        std::make_tuple("", ""),
        std::make_tuple("1", "1"),
        std::make_tuple("1,2", "1,null,2"),
        std::make_tuple("-10,-3,0,5,9", "0,-10,5,null,-3,null,9")

    ));
// clang-format on