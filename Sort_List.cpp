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
void Quick_Sort_List(ListNode* head, int len,bool forward) {

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
			Quick_Sort_List(head, len - less, false);
		//if(less >= 2)
			Quick_Sort_List(temp, less, forward);
	}
	else
		return;

}
ListNode* QuickSortList(ListNode* head) {
	int len = 0;
	ListNode *temp = head;	
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (len <= 1)
		return head;
	Quick_Sort_List(head, len,true);
	return ans;
}
//solution 2:using merge sort
ListNode *MergeSortList(ListNode *head,int len) 
{

	if (len <= 1)
		return head;

	ListNode *linkX = NULL;
	ListNode *linkY = NULL;
	ListNode *headY = head;
	ListNode *cur = NULL;
	int lenX = len / 2;
	int lenY = len - lenX;
	int i;
	for (i = 0;i < lenX;i++)
	{
		headY = headY->next;
	}
	linkX = MergeSortList(head,lenX);
	
	linkY = MergeSortList(headY,lenY);
	head = NULL;
	/*
	ListNode *tempX = linkX;
	ListNode *tempY = linkY;
	cout << "\nlinkX: ";
	for (i = 0; i < lenX;i++)
	{
		cout << tempX->val << " ";
		tempX = tempX->next;
	}
	cout << "\nlinkY: ";
	for (i = 0;i < lenY;i++)
	{
		cout << tempY->val<<" ";
		tempY = tempY->next;
	}
	//*/
	for (i = 0;i < len && lenX != 0 && lenY != 0;i++)
	{
		if (head == NULL)
		{
			if (linkX->val < linkY->val)
			{
				head = linkX;
				cur = head;
				linkX = linkX->next;
				lenX--;
			}
			else
			{
				head = linkY;
				cur = head;
				linkY = linkY->next;
				lenY--;
			}
		}
		else
		{
			if (linkX->val < linkY->val)
			{
				cur->next = linkX;
				linkX = linkX->next;
				lenX--;
			}
			else
			{
				cur->next = linkY;
				linkY = linkY->next;
				lenY--;
			}
			cur = cur->next;
		}
	}
	if (lenX != 0)
	{
		if (head)
			cur->next = linkX;
		else
			head = linkX;
	}
	else if (lenY != 0)
	{
		if (head)
			cur->next = linkY;
		else
			head = linkY;
	}
	/*
	tempX = head;
	cout << "\nhead: ";
	for (i = 0;i < len;i++)
	{
		cout << tempX->val<<" ";
		tempX = tempX->next;
	}
	//*/
	return head;
}
ListNode *sortList(ListNode *head)
{
	if (head)
	{
		ListNode *temp = head;
		int len = 0;
		while (temp)
		{
			temp = temp->next;
			len++;
		}
		head = MergeSortList(head,len);
		temp = head;
		cout << "\n";
		for (int i = 0;i < len;i++)
		{
			//cout << temp->val << " ";
			if(i == len - 1)
				temp->next = NULL;
			else			
				temp = temp->next;
		}
		
	}
	return head;
}
/*
int main()
{
	int a[] = { -84,142,41,-17,-71,170,186,183,-21,-76,76,10,29,81,112,-39,-6,-43,58,41,111,33,69,97,-38,82,-44,-7,99,135,42,150,149,-21,-30,164,153,92,180,-61,99,-81,147,109,34,98,14,178,105,5,43,46,40,-37,23,16,123,-53,34,192,-73,94,39,96,115,88,-31,-96,106,131,64,189,-91,-34,-56,-22,105,104,22,-31,-43,90,96,65,-85,184,85,90,118,152,-31,161,22,104,-85,160,120,-31,144,115};
	//int a[] = {2,3,4,12,3,4,1,2,3,4,6,4,4};
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
}*/