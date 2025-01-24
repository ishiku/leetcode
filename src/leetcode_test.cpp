#include "leetcode.h"

#include <gtest/gtest.h>

TEST(leetcode, deserialize_empty_tree) {
  auto root = leetcode::deserializeTree("");
  EXPECT_FALSE(root);
}

TEST(leetcode, deserialize_single_node_tree) {
  auto root = leetcode::deserializeTree("1");

  EXPECT_TRUE(root);
  EXPECT_EQ(root->val, 1);
  EXPECT_TRUE(root->left == nullptr);
  EXPECT_TRUE(root->right == nullptr);
}

TEST(leetcode, deserialize_root_with_left_child) {
  auto root = leetcode::deserializeTree("1,2");

  EXPECT_TRUE(root);
  EXPECT_EQ(root->val, 1);

  EXPECT_TRUE(root->left != nullptr);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_TRUE(root->left->left == nullptr);
  EXPECT_TRUE(root->left->right == nullptr);

  EXPECT_TRUE(root->right == nullptr);
}

TEST(leetcode, deserialize_root_with_right_child) {
  auto root = leetcode::deserializeTree("1,null,2");

  EXPECT_TRUE(root != nullptr);
  EXPECT_EQ(root->val, 1);

  EXPECT_TRUE(root->left == nullptr);

  EXPECT_TRUE(root->right != nullptr);
  EXPECT_EQ(root->right->val, 2);
  EXPECT_TRUE(root->right->left == nullptr);
  EXPECT_TRUE(root->right->right == nullptr);
}

TEST(leetcode, deserialize_root_with_both_children) {
  auto root = leetcode::deserializeTree("1,2,3");

  EXPECT_TRUE(root != nullptr);
  EXPECT_EQ(root->val, 1);

  EXPECT_TRUE(root->left != nullptr);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_TRUE(root->left->left == nullptr);
  EXPECT_TRUE(root->left->right == nullptr);

  EXPECT_TRUE(root->right != nullptr);
  EXPECT_EQ(root->right->val, 3);
  EXPECT_TRUE(root->right->left == nullptr);
  EXPECT_TRUE(root->right->right == nullptr);
}

TEST(leetcode, deserialize_three_left) {
  auto root = leetcode::deserializeTree("1,2,null,3");

  EXPECT_TRUE(root != nullptr);
  EXPECT_TRUE(root->left != nullptr);
  EXPECT_TRUE(root->right == nullptr);
  EXPECT_TRUE(root->left->left != nullptr);
  EXPECT_TRUE(root->left->right == nullptr);
  EXPECT_TRUE(root->left->left->left == nullptr);
  EXPECT_TRUE(root->left->left->right == nullptr);

  EXPECT_EQ(root->val, 1);
  EXPECT_EQ(root->left->val, 2);
  EXPECT_EQ(root->left->left->val, 3);
}

TEST(leetcode, deserialize_three_right) {
  auto root = leetcode::deserializeTree("1,null,2,null,3");

  EXPECT_TRUE(root != nullptr);
  EXPECT_TRUE(root->left == nullptr);
  EXPECT_TRUE(root->right != nullptr);
  EXPECT_TRUE(root->right->left == nullptr);
  EXPECT_TRUE(root->right->right != nullptr);
  EXPECT_TRUE(root->right->right->left == nullptr);
  EXPECT_TRUE(root->right->right->right == nullptr);

  EXPECT_EQ(root->val, 1);
  EXPECT_EQ(root->right->val, 2);
  EXPECT_EQ(root->right->right->val, 3);
}