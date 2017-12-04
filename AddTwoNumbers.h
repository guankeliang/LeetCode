#include <string>

using namespace std;


struct ListNode
{
	ListNode *next;
	int val;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode dummy(-1);
	ListNode *prev = &dummy;
	int carry = 0;
	for (ListNode *pa = l1, *pb = l2; pa != nullptr || pb != nullptr;
		pa = pa == nullptr ? nullptr : pa->next,
		pb = pb == nullptr ? nullptr : pb->next, 
		prev = prev->next)
	{
		const int value = (pa->val + pb->val + carry) % 10;
		carry = (pa->val + pb->val + carry) / 10;
		prev->next = new ListNode(value);
	}
	if (carry > 0)
	{
		prev->next = new ListNode(carry);
	}
	return dummy.next;
}

string addBinary(const string& a, const string& b)
{
	size_t n = a.size() > b.size() ? a.size() : b.size();
	int carry = 0;
	string result;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < n; i++)
	{
		const int ai = i < a.size() ? a[i] - '0' : 0;
		const int bi = i < b.size() ? b[i] - '0' : 0;
		const int val = (ai + bi + carry) % 2;
		carry = (ai + bi + carry) / 2;
		result.insert(result.begin(), val + '0');
	}
	if (carry == 1)
	{
		result.insert(result.begin(), '1');
	}
	return result;
}