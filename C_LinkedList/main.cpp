#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct node{	// node ����
	int data;
	node* next;	
}node_obj;				// node_obj ���Ͷ���

// 
node* create_link_list()
{
	node* ptr_head = NULL;
	node* ptr_current = NULL;
	node* ptr_new = NULL;

	ptr_head = (node*)malloc(1 * sizeof(node));
	ptr_head->data = -100;
	ptr_head->next = NULL;

	ptr_current = ptr_head;
	int i; 
	int array[] = { 1,2,3,4,5 };
	for (i = 0; i < (sizeof(array)/sizeof(int)); i++)
	{
		ptr_new = (node*)malloc(1 * sizeof(node));
		ptr_new->data = array[i];// i + 1;
		ptr_new->next = NULL;

		ptr_current->next = ptr_new;
		ptr_current = ptr_current->next;
	}

	return ptr_head;
}

node* insert_linked_list(node* ptr_head, int dest_value, int data)
{
	node* ptr_new = (node*)malloc(1 * sizeof(node));
	ptr_new->data = data;
	ptr_new->next = NULL;

	node* ptr_current = ptr_head->next;	// ����malloc
	node* ptr_current_pre = ptr_head;	// ָ��current��ǰһ���ڵ�,������ǰ��
	while (ptr_current != NULL)
	{ 
		if (ptr_current->data == dest_value)
		{
			// dest_value���
			ptr_new->next = ptr_current->next;
			ptr_current->next = ptr_new;
			// dest_value ǰ��
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
	int i = 0;
	node* ptr_current = ptr_head->next;
	while (ptr_current != NULL)
	{
		i++;
		printf("%d\n", ptr_current->data);
		ptr_current = ptr_current->next;
	}
	printf("i=%d\n", i);
}

// qsort�еıȽϺ�����Ĭ�ϸ�ʽ���£�
int compare(const void* a, const void* b)
{
	//int a1 = *(int*)a;
	//int b1 = *(int*)b;
	return *(int*)a - *(int*)b;	// ���compar����ֵС��0��< 0������ôp1��ָ��Ԫ�ػᱻ����p2��ָ��Ԫ�ص�ǰ�棻
}

/*
	˼·��
    1.��ͳ������ڵ����nums
    2.��mallocһ��nums��С������array���������������val��ֵ��������
    3.����C�⺯������qsort()������array����
	4.�������������ź����array[i]��ֵ������ÿ���ڵ��val
	// sort-linkedlist
*/
node* sortList(node* ptr_head){
	/*
	// ð��sort��
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

// reverse linklist
node* reverseList(node* ptr_head){

	if (NULL == ptr_head || NULL == ptr_head->next)
	{
		return ptr_head;
	}

	node* p1 = ptr_head;
	node* p2 = p1->next;
	node* temp = NULL;//node* temp = p2->next;
	ptr_head->next = NULL;	// p1->next = NULL;

	while (p2 != NULL)
	{
		temp = p2->next;// temp = temp->next;
		p2->next = p1;
		p1 = p2;
		p2 = temp;
		//temp = temp->next;
	}

	//ptr_head->next = p1;

	free(ptr_head);
	ptr_head = NULL;

	node* new_head = (node*)malloc(1*sizeof(node));
	new_head->data = -999;
	new_head->next = p1;


	return new_head;//ptr_head;
}

/**
	˼·��
	1.�ֱ������������ͳ�ƽڵ���p_count��q_count
	2.�����������нϳ������������ָ��p��ͷ���� n=abs(p_count-q_count)��
	3.���p��q�ֱ�������������Ƚ��Ƿ�����ͬ�Ľڵ㣬���򷵻ظýڵ㣬�޷���NULL

	Ҫ���ǵ�������£�
	1.����������head��ΪNULL
	2.������������ֻ��ͬһ���ڵ㣬����Ϊ1
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
		n = abs(n);					//Ҫȡ����ֵ�������߼�������
		while (n > 0)
		{
			q = q->next;
			n--;
		}
	}

	// n = 0,��������ִ��

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
	// ������������1��
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
		����2�� ��ת����
		˼·�����ÿ���ָ���ҵ��м䣬Ȼ������ĺ�벿�ַ�ת�������ν��бȽ�
	*/
	if (head == NULL)
	{
		return false;
	}
	if (head->next != NULL && head->next->next == NULL)  // �� Let����if (head != NULL || head->next == NULL) ) // ���ֻ��һ���ڵ�
	{
		return true;
	}
	// 1 2 (2) 1                                   1 2 (1)
	node* p_slow = head;
	node* p_fast = head;

	// ���м�λ��
	while (p_fast != NULL && p_fast->next != NULL)		// ͷ������һ���ڵ㲻ΪNULL���൱�ڳ���ͷ֮��ĵ�1��2��3....���ڵ㲻ΪNULL��Let����p_fast != NULL��
	{
		p_slow = p_slow->next;
		p_fast = p_fast->next->next;
	}

	// reverse linkedlist��벿��
	node* p_temp = p_slow->next;						// �����м�ڵ�:���м�λ�ã���ָ�����һ���ڵ�Ϊ�м�ڵ�
	p_fast = p_temp;
	node* p_fast1 = p_temp->next;
	node* p_fast2 = NULL;

	p_slow->next = NULL;								// �ж��м�λ��ǰ��next����1
	p_temp->next = NULL;								// �ж��м�λ�ú��next����2

	while (p_fast1 != NULL)
	{
		p_fast2 = p_fast1->next;

		p_fast1->next = p_fast;							// ��������
		p_fast = p_fast1;
		p_fast1 = p_fast2;
	}

	p_slow = head->next;								// �����¶���ָ�룬����p_slow����ָ��ͷ(Let�У�p_slow = head)
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
	��żlinkedlist :
	1->2->3->4->5->NULL  1->3->5->2->4->NULL

	˼·��
	1.��������żָ��ֱ�ָ����ż�ڵ����ʼλ�ã�������Ҫһ��������ָ��even_head������ż�ڵ�����λ�ã�
	2.Ȼ�����ڵ��ָ��ż�ڵ����һ��(һ������ڵ�)������ڵ����һ��;
	  �ٰ�ż�ڵ�ָ����һ����ڵ����һ��(һ����ż�ڵ�)����ż�ڵ����һ�����Դ�����ֱ��ĩβ��
	3.��ʱ�ѷֿ���ż�ڵ������������ڵ������󼴿�
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
	����ķ����벻�ı�ڵ��ָ�򣬶�ֱ�ӽ����ڵ��ֵ����ʵ�ϣ��÷��������Բ�����.
	*/

	//// ��һ���ڵ�λ�ò��䣬���Դӵ������ڵ㿪ʼ
	//node* p_odd = head->next->next->next;					// �ڶ�����
	//node* p_event = head->next->next;						// ż
	//
	//while (p_odd != NULL && p_odd->next != NULL /*&& p_odd->next->next != NULL*/ /*p_event->next != NULL*/)
	//{
	//	// swap:
	//	swap(p_odd->data, p_event->data);
	//	//int tmp = p_odd->data;	// ��һ����ڵ����һ������һ�����һ��ż����
	//	//p_odd->data = p_event->data;
	//	//p_event->data = tmp;

	//	p_odd = p_odd->next->next;		// ����2
	//	p_event = p_event->next->next;  // ż��2	
	//}

	//return head;
}

/**************************************************************************/
node* create_link_list1()
{
	node* ptr_head = NULL;
	node* ptr_current = NULL;
	node* ptr_new = NULL;

	ptr_head = (node*)malloc(1 * sizeof(node));
	ptr_head->data = 0;
	ptr_head->next = NULL;

	ptr_current = ptr_head;
	int i;
	int array[] = { 1, 2, 3, 4, 5 };
	for (i = 0; i < (sizeof(array) / sizeof(int)); i++)
	{
		ptr_new = (node*)malloc(1 * sizeof(node));
		ptr_new->data = array[i];// i + 1;
		ptr_new->next = NULL;

		ptr_current->next = ptr_new;
		ptr_current = ptr_current->next;
	}

	return ptr_head;
}

// reverse linklist(LiSenLing�汾)
node* reverseList1(node* ptr_head){

	if (NULL == ptr_head || NULL == ptr_head->next)
	{
		return ptr_head;
	}
	/***************************************************/
	node* cur = ptr_head;
	node* pre = NULL;
	node* end = NULL;
	while (cur != NULL)
	{
		end = cur->next;
		cur->next = pre;
		pre = cur;
		cur = end;
	}

	free(ptr_head);
	ptr_head = NULL;

	return pre;
}

void print_linked_list1(node* ptr_head)
{
	int i = 0;
	node* ptr_current = ptr_head;
	while (ptr_current != NULL)
	{
		i++;
		printf("%d\n", ptr_current->data);
		ptr_current = ptr_current->next;
	}
	printf("i=%d\n", i);
}

int main()
{
	node* ptr_head = create_link_list();
	printf("��ʼ����:\n");
	print_linked_list(ptr_head);

	/*int data = 17;
	int dest_value = 5;
	
	node* tmp_insert =insert_linked_list(ptr_head, dest_value, data);
	if (tmp_insert == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("����ڵ�������:\n");
	print_linked_list(ptr_head);*/

	/*printf("����������:\n");
	node* sort_list = sortList(ptr_head);
	print_linked_list(sort_list);*/

	printf("��ת�������:\n");
	//node* reverse_list = reverseList(ptr_head);
	//print_linked_list(reverse_list);
	// ��ת����(��ɭ�ְ汾)��
	node* ptr_head1 = create_link_list1();
	node* reverse_list = reverseList1(ptr_head1);
	print_linked_list1(reverse_list);

	//node* IntersectionNode = getIntersectionNode(ptr_head, ptr_head);
	//if (IntersectionNode == NULL)
	//{
	//	printf("���ཻ�ڵ�");
	//}
	//else
	//{
	//	printf("�ཻ�ĵĽڵ�:\n");
	//}
	//print_linked_list(IntersectionNode);

	//bool b = isPalindrome(ptr_head);
	//if (b == true)
	//{
	//	printf("��\n");
	//}
	//else
	//{
	//	printf("��\n");
	//}

	/*printf("��ż��\n");
	node* p_t = oddEvenList(ptr_head);
	print_linked_list(p_t);*/

	/*node* tmp_delete = delete_linked_list(ptr_head, dest_value);
	if (tmp_delete == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("ɾ���ڵ�������:\n");
	print_linked_list(ptr_head);

	free_link_list(ptr_head);*/

	getchar();
	return 0;
}
