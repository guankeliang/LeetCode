#include <vector>

using namespace std;

/*
a.先序遍历，根节点在开始位置
b.后序遍历，根节点在结束位置
c.根据先序或后序遍历，可以得到根节点，利用中序遍历中根节点的位置，可以划分左右子树；
d.根据所得的子树，可以分别进行递归，最终确定二叉树形式。

*/

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildBTree(vector<int>& preorder, vector<int>& inorder)
{
	return buildTree(begin(preorder), end(preorder), begin(inorder), end(inorder));

}

//preorder,inorder 
template<typename InputIterator>
TreeNode *buildTree(InputIterator pre_first, InputIterator pre_last,
	InputIterator in_first, InputIterator in_last)
{
	if (pre_first == pre_last) return nullptr;
	if (in_first == in_last) return nullptr;

	auto root = new TreeNode(*pre_first);

	auto inRootPos = find(in_first, in_last, *pre_first);
	auto leftSize = distance(in_first, inRootPos);

	root->left = buildTree(next(pre_first), next(pre_first, leftSize + 1), 
							in_first, next(in_first, leftSize));
	root->right = buildTree(next(pre_first, leftSize + 1), pre_last, 
							next(inRootPos), in_last);

	return root;
}