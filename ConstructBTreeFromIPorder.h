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

TreeNode* buildBTree(vector<int>& inorder, vector<int>& postorder)
{
	return buildTree(begin(inorder), end(inorder), begin(postorder), end(postorder));

}

//inorder ,postorder
template<typename InputIterator>
TreeNode *buildTree(InputIterator in_first, InputIterator in_last,
	InputIterator post_first, InputIterator post_last)
{
	if (in_first == in_last) return nullptr;
	if (post_first == post_last) return nullptr;

	const auto val = *prev(post_last);
	auto root = new TreeNode(val);

	auto inRootPos = find(in_first, in_last, val);
	auto left_size = distance(in_first, inRootPos);
	auto post_left_last = next(post_first, left_size);

	root->left = buildTree(in_first, inRootPos,
		post_first, post_left_last);
	root->right = buildTree(next(inRootPos), in_last,
		post_left_last, prev(post_last));

	return root;
}