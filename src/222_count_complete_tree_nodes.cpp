// https://leetcode.com/problems/count-complete-tree-nodes/description/?envType=problem-list-v2&envId=tree

#include "leetcode.h"

#include <gtest/gtest.h>

#include <string>
#include <tuple>

using namespace leetcode;

namespace {
	int depth(TreeNode* root) {
		if (root == nullptr) return 0;
		return depth(root->left) + 1;
	}

	// TC=O(LogN ^ 2), SC=O(LogN)..O(N)
	int countNodes(TreeNode *root, int DL = -1) {
		if (root == nullptr) return 0;

		int count = 1;
		if (DL == -1)
			DL = depth(root->left);

		int DR = depth(root->right);

		if (DL == DR) {
			count += (1 << DL) - 1;
			count += countNodes(root->right, DL-1);
		}
		else {
			count += (1 << DR) - 1;
			count += countNodes(root->left, DL-1);
		}
		return count;
	}
}

class CountCompleteTreeNodeFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> {};

TEST_P(CountCompleteTreeNodeFixture, shouldPass) {
	auto [tree_desc, count] = GetParam();
	auto tree = deserializeTree(tree_desc);
	EXPECT_EQ(countNodes(tree.get()), count);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
	CountCompleteTreeNodeTests,
	CountCompleteTreeNodeFixture,
	::testing::Values(
		std::make_tuple("",0),
		std::make_tuple("1", 1),
		std::make_tuple("1,2,3,4,5,6", 6)		
	));
// clang-format on
