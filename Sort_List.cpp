#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL) {}
	ListNode() :val(0), next(NULL) {}
};
//solution 1: using quick sort~~~
ListNode *ans;
void Sort_List(ListNode* head, int len,bool forward) {

	int i;
	ListNode *smaller;
	if (forward) 
	{
		smaller = new ListNode(0);
		smaller->next = head;
	}
	else
	{
		if (head->next == NULL)
			return;
		smaller = head;
		head = head->next;
	}
		
	ListNode *sample = head;
	ListNode *temp;
	int less = 1;
	bool same = true;
	for (i = 1; i < len; i++)
	{
		if (head->val != sample->next->val)
			same = false;
		if (head->val > sample->next->val)
		{
			less++;
			temp = sample->next;
			sample->next = sample->next->next;

			temp->next = smaller->next;
			smaller->next = temp;
		}
		else
		{
			sample = sample->next;
		}
		
	}
	
	
	if (forward)
	{
		temp = smaller->next;
		ans = temp;
		delete smaller;
	}
	else
		temp = smaller;
	
	ListNode *tt = temp;
	cout << "\nless: ";
	for (int i = 0; i < less;i++)
	{
		cout << tt->val << " ";
		tt = tt->next;
	}
	cout << "\n big: ";
	for (int i = 0;i < (len - less);i++)
	{
		cout << tt->val << " ";
		tt = tt->next;
	}
	
	if (len > 2 && same == false)
	{
		//if(len-less >= 2)
			Sort_List(head, len - less, false);
		//if(less >= 2)
			Sort_List(temp, less, forward);
	}
	else
		return;

}
ListNode* sortList(ListNode* head) {
	int len = 0;
	ListNode *temp = head;	
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (len <= 1)
		return head;
	Sort_List(head, len,true);
	return ans;
}
//solution 2:using merge sort
int main()
{
	int a[] = { -84,142,41,-17,-71,170,186,183,-21,-76,76,10,29,81,112,-39,-6,-43,58,41,111,33,69,97,-38,82,-44,-7,99,135,42,150,149,-21,-30,164,153,92,180,-61,99,-81,147,109,34,98,14,178,105,5,43,46,40,-37,23,16,123,-53,34,192,-73,94,39,96,115,88,-31,-96,106,131,64,189,-91,-34,-56,-22,105,104,22,-31,-43,90,96,65,-85,184,85,90,118,152,-31,161,22,104,-85,160,120,-31,144,115};
	int len = sizeof(a) / sizeof(int);
	ListNode *temp = new ListNode;
	ListNode *head = temp;
	ListNode *t = head;

	for (int i = 0; i < len;i++)
	{
		temp->val = a[i];
		if(i +1 != len)
			temp->next = new ListNode;
		temp = temp->next;
	}

	t = sortList(head);
	for (;t != NULL;t = t->next)
		cout << t->val << " " ;
	cout << endl;
	vector<int> k(a, a + len);
	sort(k.begin(),k.end());
	for (int i = 0; i < len;i++)
		cout << k[i] << " ";
	cout << endl;
	getchar();
	return 0;
}