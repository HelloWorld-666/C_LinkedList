#include <stdio.h>
#include <stdlib.h>

typedef struct node{	// node 类型
	int data;
	node* next;	
}node_obj;				// node_obj 类型对象

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
	for (i = 0; i < 10; i++)
	{
		ptr_new = (node*)malloc(1 * sizeof(node));
		ptr_new->data = i + 1;
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
	int i;
	node* ptr_current = ptr_head->next;
	while (ptr_current != NULL)
	{
		printf("%d\n", ptr_current->data);
		ptr_current = ptr_current->next;
	}
	printf("\n");
}

int main()
{
	node* ptr_head = create_link_list();
	printf("初始链表:\n");
	print_linked_list(ptr_head);

	int data = 17;
	int dest_value = 5;
	
	node* tmp_insert =insert_linked_list(ptr_head, dest_value, data);
	if (tmp_insert == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("插入节点后的链表:\n");
	print_linked_list(ptr_head);

	node* tmp_delete = delete_linked_list(ptr_head, dest_value);
	if (tmp_delete == NULL)
	{
		printf("not find dest_value value.\n");
	}
	printf("删除节点后的链表:\n");
	print_linked_list(ptr_head);

	free_link_list(ptr_head);

	getchar();
	return 0;
}
