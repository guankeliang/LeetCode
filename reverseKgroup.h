struct ListNode
{
	ListNode *next;
	int val;
	ListNode(int x) : val(x), next(nullptr) {}
};


ListNode* reverse(ListNode *prev, ListNode *begin, ListNode *end)
{
	ListNode *end_next = end->next;
	for (ListNode *p = begin, *cur = p->next, *next = cur->next;
		cur != end_next;
		p = cur, cur = next, next = next ? next->next : nullptr)
		cur->next = p;
	begin->next = end_next;
	prev->next = end;
	return begin;
}

ListNode* reverseKgroup(ListNode* head, int k)
{
	if (head == nullptr || head->next == nullptr || k < 2) return head;
	ListNode dummy(-1);
	dummy.next = head;
	for (ListNode *prev = &dummy, *end = head; end; end = prev->next)
	{
		for (int i = 1; i < k && end; i++)
			end = end->next;
		if (end == nullptr) break;
		prev = reverse(prev, prev->next, end);
	}
	return dummy.next;
}
