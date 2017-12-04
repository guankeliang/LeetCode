#include <utility>
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void recoverTree(TreeNode *root)
{
	std::pair<TreeNode*, TreeNode*> broken;
	TreeNode *prev = nullptr;
	TreeNode *cur = root;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			detect(broken, prev, cur);
			prev = cur;
			cur = cur->right;
		}
		else
		{
			auto node = cur->left;
			while (node->right != nullptr && node->right != cur)
			{
				node = node->right;
			}
			if (node->right == nullptr)
			{
				detect(broken, prev, cur);
				node->right = cur;
				cur = cur->left;
			}
			else
			{
				detect(broken, prev, cur);
				node->right = nullptr;
				prev = cur;
				cur = cur->right;
			}
		}
	}
	std::swap(broken.first->val, broken.second->val);
}

void detect(std::pair<TreeNode*, TreeNode*>& broken, TreeNode* prev, TreeNode *cur)
{
	if (prev != nullptr && prev->val > cur->val)
	{
		if (broken.first == nullptr)
			broken.first == prev;
		broken.second = cur;
	}
}