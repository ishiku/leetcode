#include "leetcode.h"

#include <gtest/gtest.h>

#include <string>
#include <tuple>

using namespace leetcode;

namespace {

// TC=O(N), SC=O(LogN)..O(N)
bool isSameTree(TreeNode *p, TreeNode *q) {
  if (!p && !q)
    return true;
  if (p && !q || !p && q)
    return false;
  if (p->val != q->val)
    return false;
  return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

} // namespace

class SameTreeTestFixture : public ::testing::TestWithParam<
                                std::tuple<std::string, std::string, bool>> {};

TEST_P(SameTreeTestFixture, shouldPass) {
  auto [p_tree_desc, q_tree_desc, equality] = GetParam();

  auto p_tree = deserializeTree(p_tree_desc);
  auto q_tree = deserializeTree(q_tree_desc);

  EXPECT_TRUE((isSameTree(p_tree.get(), q_tree.get()) == equality));
}

INSTANTIATE_TEST_SUITE_P(
    SameTreeTests, SameTreeTestFixture,
    ::testing::Values(std::make_tuple("", "", true),
                      std::make_tuple("1", "", false),
                      std::make_tuple("", "1", false),
                      std::make_tuple("1", "2", false),
                      std::make_tuple("1,2,3", "1,2,3", true),
                      std::make_tuple("1,2,3", "1,3,3", false),
                      std::make_tuple("1,2,3", "1,2,2", false)));