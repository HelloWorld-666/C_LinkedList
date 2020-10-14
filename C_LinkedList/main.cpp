#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct node{				// node 类型
	int data;
	node* next;	
}node_obj;					// node_obj 类型对象

// 
node* create_link_list()
{
	node* ptr_head = NULL;
	node* ptr_current = NULL;
	node* ptr_new = NULL;

	ptr_head = (node*)malloc(1 * sizeof(node));
	ptr_head->data = -100;			// 头节点保存链表长度
	ptr_head->next = NULL;

	ptr_current = ptr_head;
	int len = 0;
	for (int i = 0; i < 10; i++)
	{
		ptr_new = (node*)malloc(1 * sizeof(node));
		ptr_new->data = i;
		ptr_new->next = NULL;

		ptr_current->next = ptr_new;
		ptr_current = ptr_current->next; // 这两句话效果一样：ptr_current = ptr_new;
		len++;
	}

	ptr_head->data = len;
	return ptr_head;
}

node* insert_linked_list(node* ptr_head, int dest_value, int data)
{
	node* ptr_new = (node*)malloc(1 * sizeof(node));
	ptr_new->data = data;
	ptr_new->next = NULL;

	node* ptr_current = ptr_head->next;	// 不用malloc
	node* ptr_current_pre = ptr_head;	// 指向current的前一个节点,仅用于前插
	while (ptr_current != NULL)
	{ 
		if (ptr_current->data == dest_value)
		{
			// dest_value后插
			ptr_new->next = ptr_current->next;
			ptr_current->next = ptr_new;
			// dest_value 前插
			//ptr_current_pre->next = ptr_new;
			//ptr_new->next = ptr_current;
			return ptr_head;
		}
		ptr_current_pre = ptr_current;
		ptr_current = ptr_current->next;
	}
	return NULL;
}

node* delete_linked_list(node* ptr_head, int dest_value)
{
	node* ptr_current = ptr_head->next;
	node* ptr_current_pre = ptr_head;
	while (ptr_current != NULL)
	{
		if (ptr_current->data == dest_value)
		{
			ptr_current_pre->next = ptr_current->next;
			free(ptr_current);
			ptr_current = NULL;
			return ptr_head;
		}
		ptr_current_pre = ptr_current;
		ptr_current = ptr_current->next;
	}

	return NULL;
}

void free_link_list(node* ptr_head)
{
	node* ptr_current = ptr_head->next;
	node* ptr_current_pre = ptr_current;
	while (ptr_current != NULL)
	{
		ptr_current = ptr_current->next;
		free(ptr_current_pre);
		ptr_current_pre = NULL;

		ptr_current_pre = ptr_current;
	}

	free(ptr_head);
	ptr_head = NULL;
}

void print_linked_list(node* ptr_head)
{
	node* ptr_current = ptr_head->next;
	while (ptr_current != NULL)
	{
		printf("%d\n", ptr_current->data);
		ptr_current = ptr_current->next;
	}
}

// qsort中的比较函数，默认格式如下：
int compare(const void* a, const void* b)
{
	//int a1 = *(int*)a;
	//int b1 = *(int*)b;
	return *(int*)a - *(int*)b;	// 如果compar返回值小于0（< 0），那么p1所指向元素会被排在p2所指向元素的前面；
}

/*
	思路：
    1.先统计链表节点个数nums
    2.再malloc一个nums大小的数组array，并将遍历链表的val赋值到数组中
    3.利用C库函数快排qsort()对数组array排序
	4.遍历链表，并将排好序的array[i]赋值给链表每个节点的val
	// sort-linkedlist
*/
node* sortList(node* ptr_head){
	/*
	// 冒泡sort：
	node* p_first = ptr_head;
	node* p_second = NULL;
	while (p_first != NULL)
	{
		p_second = p_first->next;	// j = i+1
		while (p_second != NULL)	// j < len
		{
			if (p_first->data > p_second->data)
			{
				int temp = p_first->data;
				p_first->data = p_second->data;
				p_second->data = temp;
			}
			p_second = p_second->next;
		}
		p_first = p_first->next;
	}
	
	return ptr_head;
	*/

	// qsort
	int nums = 0;
	node* p_cur = ptr_head;
	while (p_cur != NULL)
	{
		nums++;
		p_cur = p_cur->next;
	}
	
	int* array = (int*)malloc(nums * sizeof(int));
	int i = 0;
	p_cur = ptr_head;
	while (p_cur != NULL)
	{
		array[i++] = p_cur->data;
		p_cur = p_cur->next;
	}
	qsort(array, nums, sizeof(int), compare);

	p_cur = ptr_head;
	i = 0;
	while (p_cur != NULL)
	{
		p_cur->data = array[i++];
		p_cur = p_cur->next;
	}
		
	return ptr_head;
}

// reverse linklist （头结点中数据域是链表长度）
node* reverseList(node* pHead)
{
	if (NULL == pHead || NULL == pHead->next)
	{
		return pHead;
	}

	node* pPre = NULL;			// pPre开始时为NULL，当第一次反向连接时:pMid->next = pPre(NULL)，pMid的下一个正好指向NULL
	node* pMid = pHead->next;	        // 初始时pMid是指向头结点的下一个有效节点
	node* pEnd = NULL;

	pHead->next = NULL;			// 先将头结点独立出来

	while (pMid != NULL)
	{
		pEnd = pMid->next;
		pMid->next = pPre;		// link
		pPre = pMid;
		pMid = pEnd;
	}

	pHead->next = pPre;			// 再将头结点指向reverse之前的尾节点(也就是当前reverse之后头结点的下一个节点)

	return pHead;
}

// 如LeetCode中，头结点也存有效值，而不是链表长度等无效值时：
ListNode* reverseList(ListNode* head) {
        if (NULL == head || NULL == head->next)
        {
            return head;
        }

        ListNode* pPre = NULL;		// pPre开始时为NULL，当第一次反向连接时:pMid->next = pPre(NULL)，pMid的下一个正好指向NULL
        ListNode* pMid = head;	        // 初始时pMid是指向头结点的下一个有效节点
        ListNode* pEnd = NULL;

        // head->next = NULL;		// 略去：先将头结点独立出来

        while (pMid != NULL)
        {
            pEnd = pMid->next;
            pMid->next = pPre;		// link
            pPre = pMid;
            pMid = pEnd;
        }

        // head->next = pPre;		// 略去：再将头结点指向reverse之前的尾节点(也就是当前reverse之后头结点的下一个节点)

        return pPre;
    }

/**
	思路：
	1.分别遍历两个链表，统计节点数p_count和q_count
	2.让两条链表中较长的那条链表的指针p从头先走 n=abs(p_count-q_count)步
	3.最后p和q分别往后遍历，并比较是否有相同的节点，有则返回该节点，无返回NULL

	要考虑的情况如下：
	1.当两个链表head都为NULL
	2.两个链表都仅仅只有同一个节点，长度为1
*/
node *getIntersectionNode(node *headA, node *headB) {
	node* p = headA;
	node* q = headB;
	int p_count = 0;
	int q_count = 0;

	if (headA == NULL || headB == NULL)
	{
		return NULL;
	}
	if (headA == headB)
	{
		return headA;
	}

	while (p != NULL)
	{
		p_count++;				
		p = p->next;
	}
	while (q != NULL)
	{	
		q_count++;				
		q = q->next;
	}

	int n = p_count - q_count;
	
	p = headA;
	q = headB;
	if (n > 0)
	{
		while (n > 0)
		{
			p = p->next;
			n--;
		}
	}
	else if (n < 0)
	{
		n = abs(n);					//要取绝对值，否则逻辑有问题
		while (n > 0)
		{
			q = q->next;
			n--;
		}
	}

	// n = 0,继续往下执行

	while (p != NULL && q != NULL)
	{
		if (p == q)
		{
			return p;
		}
		p = p->next;
		q = q->next;
	}

	return NULL;
}

bool isPalindrome(struct node* head){
	// 暴力方法方法1：
	/*int nums = 0;
	node* p_curr = head->next;
	while (p_curr != NULL)
	{
		nums++;
		p_curr = p_curr->next;
	}

	int* array = (int*)malloc(nums*sizeof(int));
	int i = 0;
	p_curr = head->next;
	while (p_curr != NULL)
	{
		array[i++] = p_curr->data;
		p_curr = p_curr->next;
	}

	i = 0;
	while (i <= nums - i - 1)
	{
		if (array[i] != array[nums - i - 1])
		{
			return false;
		}
		i++;
	}

	return true;*/


	/* 
		方法2： 反转链表
		思路：利用快慢指针找到中间，然后将链表的后半部分反转，再依次进行比较
	*/
	if (head == NULL)
	{
		return false;
	}
	if (head->next != NULL && head->next->next == NULL)  // （ Let中则：if (head != NULL || head->next == NULL) ) // 如果只有一个节点
	{
		return true;
	}
	// 1 2 (2) 1                                   1 2 (1)
	node* p_slow = head;
	node* p_fast = head;

	// 找中间位置
	while (p_fast != NULL && p_fast->next != NULL)		// 头结点的下一个节点不为NULL，相当于除了头之外的第1、2、3....个节点不为NULL（Let中则：p_fast != NULL）
	{
		p_slow = p_slow->next;
		p_fast = p_fast->next->next;
	}

	// reverse linkedlist后半部分
	node* p_temp = p_slow->next;						// 备份中间节点:找中间位置，慢指针的下一个节点为中间节点
	p_fast = p_temp;
	node* p_fast1 = p_temp->next;
	node* p_fast2 = NULL;

	p_slow->next = NULL;								// 切断中间位置前的next连接1
	p_temp->next = NULL;								// 切断中间位置后的next连接2

	while (p_fast1 != NULL)
	{
		p_fast2 = p_fast1->next;

		p_fast1->next = p_fast;							// 反向连接
		p_fast = p_fast1;
		p_fast1 = p_fast2;
	}

	p_slow = head->next;								// 不重新定义指针，复用p_slow重新指向头(Let中：p_slow = head)
	while (p_slow != NULL && p_fast != NULL)
	{
		if (p_slow->data != p_fast->data)
		{
			return false;
		}
		p_slow = p_slow->next;
		p_fast = p_fast->next;
	}
	return true;
}

/* 
	奇偶linkedlist :
	1->2->3->4->5->NULL  1->3->5->2->4->NULL

	思路：
	1.用两个奇偶指针分别指向奇偶节点的起始位置，另外需要一个单独的指针even_head来保存偶节点的起点位置，
	2.然后把奇节点的指向偶节点的下一个(一定是奇节点)，此奇节点后移一步;
	  再把偶节点指向下一个奇节点的下一个(一定是偶节点)，此偶节点后移一步，以此类推直至末尾，
	3.此时把分开的偶节点的链表连在奇节点的链表后即可
*/

node* oddEvenList(node* head){
	if (!head || !head->next)
	{
		return head;
	}

	node* odd = head->next;
	node* even = head->next->next;
	node* even_head = even;
	while (even && even->next)
	{
		odd->next = even->next;
		odd = odd->next;
		even->next = odd->next;
		even = even->next;
	}
	odd->next = even_head;

	return head;

	/*
	下面的方法想不改变节点的指向，而直接交换节点的值，事实上，该方法经测试不可行.
	*/

	//// 第一个节点位置不变，所以从第三个节点开始
	//node* p_odd = head->next->next->next;					// 第二个奇
	//node* p_event = head->next->next;						// 偶
	//
	//while (p_odd != NULL && p_odd->next != NULL /*&& p_odd->next->next != NULL*/ /*p_event->next != NULL*/)
	//{
	//	// swap:
	//	swap(p_odd->data, p_event->data);
	//	//int tmp = p_odd->data;	// 第一个奇节点的下一个的下一个与第一个偶交换
	//	//p_odd->data = p_event->data;
	//	//p_event->data = tmp;

	//	p_odd = p_odd->next->next;		// 奇跳2
	//	p_event = p_event->next->next;  // 偶跳2	
	//}

	//return head;
}

int main()
{
	node* ptr_head = create_link_list();
	printf("初始链表:\n");
	print_linked_list(ptr_head);

	/*int data = 17;
	int dest_value = 5;
	
	node* tmp_insert =insert_linked_list(ptr_head, dest_value, data);
	if (tmp_insert == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("插入节点后的链表:\n");
	print_linked_list(ptr_head);*/

	//printf("排序后的链表:\n");
	//print_linked_list(sortList(ptr_head));

	printf("反转后的链表:\n");
	print_linked_list(reverseList(ptr_head));
	printf("len(list) = %d\n", ptr_head->data);	// 头结点中保存链表长度

	//node* IntersectionNode = getIntersectionNode(ptr_head, ptr_head);
	//if (IntersectionNode == NULL)
	//{
	//	printf("无相交节点");
	//}
	//else
	//{
	//	printf("相交的的节点:\n");
	//}
	//print_linked_list(IntersectionNode);

	//bool b = isPalindrome(ptr_head);
	//if (b == true)
	//{
	//	printf("是\n");
	//}
	//else
	//{
	//	printf("否\n");
	//}

	/*printf("奇偶：\n");
	node* p_t = oddEvenList(ptr_head);
	print_linked_list(p_t);*/

	/*node* tmp_delete = delete_linked_list(ptr_head, dest_value);
	if (tmp_delete == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("删除节点后的链表:\n");
	print_linked_list(ptr_head);

	free_link_list(ptr_head);*/

	getchar();
	return 0;
}
