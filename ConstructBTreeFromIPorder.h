#include <vector>

using namespace std;

/*
a.������������ڵ��ڿ�ʼλ��
b.������������ڵ��ڽ���λ��
c.��������������������Եõ����ڵ㣬������������и��ڵ��λ�ã����Ի�������������
d.�������õ����������Էֱ���еݹ飬����ȷ����������ʽ��

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