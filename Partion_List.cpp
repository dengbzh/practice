#include<iostream>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL) {}
};

ListNode *partition(ListNode *head,int x)
{
	if (head == NULL)
		return head;
	ListNode *smaller_head = NULL;
	ListNode *bigger_head = NULL;
	ListNode *smaller = NULL;
	ListNode *bigger = NULL;
	ListNode *cur = head;
	while (cur)
	{
		if (cur->val >= x)
		{
			if (bigger_head == NULL)
			{
				bigger_head = cur;
				bigger = bigger_head;
			}
			else
			{
				bigger->next = cur;
				bigger = bigger->next;
			}
		}
		else
		{
			if (smaller_head == NULL)
			{
				smaller_head = cur;
				smaller = smaller_head;
			}
			else
			{
				smaller->next = cur;
				smaller = smaller->next;
			}
		}
		cur = cur->next;
	}

	if (smaller_head)
	{
		smaller->next = bigger_head;
	}
	else
	{
		smaller_head = bigger_head;
	}
	if(bigger)
		bigger->next = NULL;
	return smaller_head;
}
int main()
{
	int a[] = {2,1};
	int len = sizeof(a) / sizeof(int);
	ListNode *head = new ListNode(0);
	ListNode *cur = head;
	for (int i = 0;i < len;i++)
	{
		cur->val = a[i];
		if(i != len-1)
			cur->next = new ListNode(0);
		cur = cur->next;
	}
	cur = partition(head,1);
	while (cur)
	{
		cout << cur->val << " ";
		cur = cur->next;
	}
	getchar();
	return 0;
}