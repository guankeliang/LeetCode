#include <vector>

using namespace std;
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<TreeNode*> generateTree(int n)
{
	if (n == 0) return generate(1, 0);
	return generate(1, n);
}

vector<TreeNode*> generate(int start, int end)
{
	vector<TreeNode*> subTree;
	if (start > end)
	{
		subTree.push_back(nullptr);
		return subTree;
	}
	for (int k = start; k <= end; k++)
	{
		vector<TreeNode*> leftSubs = generate(start, k - 1);
		vector<TreeNode*> rightSubs = generate(k + 1, end);
		for (auto i : leftSubs)
		{
			for (auto j : rightSubs)
			{
				TreeNode *node = new TreeNode(k);
				node->left = i;
				node->right = j;
				subTree.push_back(node);
			}
		}
	}
	return subTree;
}
