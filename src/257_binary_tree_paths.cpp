// https://leetcode.com/problems/binary-tree-paths/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>

using namespace leetcode;

namespace {
std::string pathNodesToString(std::vector<TreeNode *> const &pathNodes) {
  std::ostringstream os;
  for (int i = 0; i < pathNodes.size() - 1; ++i)
    os << pathNodes[i]->val << "->";
  os << pathNodes.back()->val;
  return os.str();
}

std::vector<std::string> binaryTreePaths(TreeNode *node) {
  std::vector<std::string> vec;
  std::vector<TreeNode *> st;
  TreeNode *last_visited = nullptr;
  while (node || !st.empty())
    if (node) {
      st.push_back(node);
      node = node->left;
    } else {
      auto peek = st.back();
      if (peek->right && peek->right != last_visited)
        node = peek->right;
      else {
        if (!peek->left && !peek->right)
          vec.push_back(pathNodesToString(st));
        last_visited = peek;
        st.pop_back();
      }
    }

  return vec;
}
} // namespace

class BinaryTreePathsFixture
    : public ::testing::TestWithParam<
          std::tuple<std::string, std::vector<std::string>>> {};

TEST_P(BinaryTreePathsFixture, shouldPass) {
  auto [tree_desc, paths] = GetParam();
  auto tree = deserializeTree(tree_desc);
  auto result = binaryTreePaths(tree.get());

  std::sort(paths.begin(), paths.end());
  std::sort(result.begin(), result.end());

  EXPECT_EQ(paths.size(), result.size());
  EXPECT_TRUE(std::equal(paths.begin(), paths.end(), result.begin()));
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
	BinaryTreePathsTests,
	BinaryTreePathsFixture,
	::testing::Values(
		std::make_tuple("", std::vector<std::string>{}),
		std::make_tuple("1", std::vector<std::string>{"1"}),
		std::make_tuple("1,2,3,null,5", std::vector<std::string>{"1->2->5", "1->3"})
	));
// clang-format on
