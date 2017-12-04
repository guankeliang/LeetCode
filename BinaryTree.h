#include <vector>
#include <stack>
#include <functional>
using namespace std;

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//Non-recursive Preorder traversal
//1.Stack
vector<int> preOrderTraversal(TreeNode *root)
{
	vector<int> result;
	stack<const TreeNode*> s;
	if (root != nullptr) s.push(root);
	while (!s.empty())
	{
		const TreeNode *p = s.top();
		s.pop();
		result.push_back(p->val);
		if (p->right != nullptr) s.push(p->right);
		if (p->left != nullptr)  s.push(p->left);
	}
	return result;
}

//Morris traversal

vector<int> preOrderTraversalII(TreeNode *root)
{
	TreeNode *cur = root, *prev = nullptr;
	vector<int> result;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			result.push_back(cur->val);
			prev = cur;
			cur = cur->right;
		}
		else
		{
			/*search prev node*/
			TreeNode *node = cur->left;
			while (node->right != nullptr && node->right != cur)
			{
				node = node->right;
			}
			if (node->right == nullptr)
			{
				result.push_back(cur->val);
				node->right = cur;
				prev = cur;
				cur = cur->left;
			}
			else
			{
				node->right = nullptr;
				cur = cur->right;
			}
		}
	}
	return result;
}


//Stack
vector<int> inorderTraversal(TreeNode *root)
{
	vector<int> result;
	stack<const TreeNode*> s;
	const TreeNode *p = root;
	while (!s.empty() || p != nullptr)
	{
		if (p != nullptr)
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.top();
			s.pop();
			result.push_back(p->val);
			p = p->right;
		}
	}
	return result;
}

//Morris inorder

vector<int> preOrderTraversalII(TreeNode *root)
{
	TreeNode *cur = root, *prev = nullptr;
	vector<int> result;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			result.push_back(cur->val);
			prev = cur;
			cur = cur->right;
		}
		else
		{
			/*search prev node*/
			TreeNode *node = cur->left;
			while (node->right != nullptr && node->right != cur)
			{
				node = node->right;
			}
			if (node->right == nullptr)
			{
				node->right = cur;
				cur = cur->left;
			}
			else
			{
				result.push_back(cur->val);
				node->right = nullptr;
				prev = cur;
				cur = cur->left;
			}
		}
	}
	return result;
}

//PostOrder Traversal
//Stack

vector<int> postOrderTraversal(TreeNode *root)
{
	stack<const TreeNode*> s;
	vector<int> result;
	const TreeNode *p = root, *q = nullptr;
	do 
	{
		while (p != nullptr)
		{
			s.push(p);
			p = p->left;
		}
		q = nullptr;
		while (!s.empty())
		{
			p = s.top();
			s.pop();
			/*right child is not exist or visited*/
			if (p->right == q)
			{
				result.push_back(p->val);
				q = p; /*save visited node*/
			}
			else
			{
				s.push(p);
				p = p->right;
				break;
			}
		}
	} while (!s.empty());
}

//Morris postorder

vector<int> postorderTraversal(TreeNode *root)
{
	vector<int> result;
	TreeNode dummy(-1);
	TreeNode *cur, *prev = nullptr;
	std::function<void(const TreeNode*)> visit = [&result](const TreeNode *node) {result.push_back(node->val); };
	dummy.left = root;
	cur = &dummy;
	while (cur != nullptr)
	{
		if (cur->left == nullptr)
		{
			prev = cur;
			cur = cur->right;
		}
		else
		{
			TreeNode *node = cur->left;
			while (node->right != nullptr && node->right != cur)
			{
				node = node->right;
			}
			if (node->right == nullptr)
			{
				prev = cur;
				node->right = cur;
				cur = cur->left;
			}
			else
			{
				visit_reverse(cur->left, prev, visit);
				prev->right = nullptr;
				prev = cur;
				cur = cur->right;
			}
		}
	}
	return result;

}

static void reverse(TreeNode *from, TreeNode *to)
{
	TreeNode *x = from, *y = from->right, *z;
	if (from == to) return;
	while (x != to)
	{
		z = y->right;
		y->right = x;
		x = y;
		y = z;
	}
}

static void visit_reverse(TreeNode *from, TreeNode *to, 
	std::function<void (const TreeNode*)> &visit)
{
	TreeNode *p = to;
	reverse(from, to);
	while (true)
	{
		visit(p);
		if (p == from)
			break;
		p = p->right;
	}
	reverse(to, from);
}