#include <iostream>
using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
};

void printList (ListNode *list)
{
  while (list != nullptr)
    {
      cout << list->val;
      list = list->next;
    }
  cout << endl;
}

void addTwoNum (ListNode *list1, ListNode *list2)
{
  if (list1 == nullptr)
    printList (list2);
  if (list2 == nullptr)
    printList (list1);

  ListNode *node1 = list1->next;
  ListNode *node2 = list2->next;
  int sum = list1->val + list2->val;
  ListNode *result = new ListNode {sum % 10, nullptr};
  sum = sum / 10;
  ListNode *node = result;

  while (node1 != nullptr || node2 != nullptr || sum != 0)
    {
      if (node1 != nullptr)
	{
	  sum += node1->val;
	  node1 = node1->next;
	}
      if (node2 != nullptr)
	{
	  sum += node2->val;
	  node2 = node2->next;
	}

      ListNode *newNode = new ListNode {sum % 10, nullptr};
      node->next = newNode;
      node = newNode;
      sum = sum / 10;
    }

  printList (result);

  while (result != nullptr)
    {
      ListNode *tmp = result;
      result = result->next;
      delete tmp;
    }
}

int
main ()
{
  ListNode node1 = {2, nullptr};
  ListNode node2 = {2, &node1};
  ListNode node3 = {7, &node2};

  ListNode node4 = {9, nullptr};
  ListNode node5 = {7, &node4};
  ListNode node6 = {7, &node5};

  addTwoNum (&node3, &node6);
  return 0;
}
