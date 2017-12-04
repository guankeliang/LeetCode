struct ListNode
{
	ListNode *next;
	int val;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *reverseBetween(ListNode *head, int m, int n)
{
	ListNode dummy(-1);
	dummy.next = head;
	ListNode *prev = &dummy;
	for (int i = 0; i < m - 1; i++)
		prev = prev->next;
	ListNode *const head2 = prev;
	ListNode *cur = prev->next;
	for (int i = m; i < n; i++)
	{
		prev->next = cur->next;
		cur->next = head2->next;
		head2->next = cur;
		cur = prev->next;
	}
	return dummy.next;
}



/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/

ListNode *reverseBetweenII(ListNode *head, int m, int n) {
	// Start typing your C/C++ solution below  
	// DO NOT write int main() function  
	if (head == NULL)
		return NULL;

	ListNode *q = NULL;
	ListNode *p = head;
	for (int i = 0; i < m - 1; i++)
	{
		q = p;
		p = p->next;
	}

	ListNode *end = p;
	ListNode *pPre = p;
	p = p->next;
	for (int i = m + 1; i <= n; i++)
	{
		ListNode *pNext = p->next;

		p->next = pPre;
		pPre = p;
		p = pNext;
	}

	end->next = p;
	if (q)
		q->next = pPre;
	else
		head = pPre;

	return head;
}
