// https://leetcode.com/problems/sum-of-left-leaves/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <string>
#include <tuple>

using namespace leetcode;

namespace {

// TC=O(N), SC=O(LogN)..O(N)
int sumOfLeftLeaves(TreeNode *node) {
  int sum = 0;
  std::stack<TreeNode *> st;
  while (node || !st.empty())
    if (node) {
      st.push(node);
      node = node->left;
    } else {
      auto peek = st.top();
      st.pop();
      node = peek->right;

      if (!peek->left && !peek->right && !st.empty() && peek == st.top()->left)
        sum += peek->val;
    }
  return sum;
}

} // namespace

class SumOfLeftLeavesFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {};

TEST_P(SumOfLeftLeavesFixture, shouldPass) {
  auto [tree_desc, sum] = GetParam();
  auto tree = deserializeTree(tree_desc);

  EXPECT_EQ(sumOfLeftLeaves(tree.get()), sum);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
	SumOfLeftLeavesTests,
	SumOfLeftLeavesFixture,
	::testing::Values(
		std::make_tuple("1", 0),
		std::make_tuple("3,9,20,null,null,15,7", 24)
	));
// clang-format on
