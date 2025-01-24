#include "leetcode.h"

#include <gtest/gtest.h>

#include <string>
#include <tuple>

using namespace leetcode;

namespace {

bool isSymmetric(TreeNode *p, TreeNode *q) {
  if (!p && !q)
    return true;
  if (!p && q || p && !q)
    return false;
  if (p->val != q->val)
    return false;
  return isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left);
}

// TC=O(N), SC=O(LogN)..O(N)
bool isSymmetric(TreeNode *root) {
  if (root == nullptr)
    return true;
  return isSymmetric(root->left, root->right);
}

} // namespace

class SymmetricTreeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, bool>> {};

TEST_P(SymmetricTreeTestFixture, shouldPass) {
  auto [tree_desc, symmetric] = GetParam();
  auto tree = deserializeTree(tree_desc);

  EXPECT_EQ(isSymmetric(tree.get()), symmetric);
}

INSTANTIATE_TEST_SUITE_P(
    SymmetricTreeTests, SymmetricTreeTestFixture,
    ::testing::Values(std::make_tuple("", true), std::make_tuple("1", true),
                      std::make_tuple("1,null,2", false),
                      std::make_tuple("1,2", false),
                      std::make_tuple("1,2,3", false),
                      std::make_tuple("1,2,2", true),
                      std::make_tuple("1,2,2,3,null,null,3", true),
                      std::make_tuple("1,2,2,null,3,3", true),
                      std::make_tuple("1,2,2,null,3,null,3", false)));