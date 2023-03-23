#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "Header.h"

int isListEmpty(stack s)
{
	return s.pTop == NULL;
}

int countNode(node *pHead)
{
	if (!pHead)
		return 0;
	int len = 0;
	while (pHead)
	{
		len++;
	}
	return len;
}
node *creatNode(int data)
{
	node *lst = new node;
	lst->key = data;
	lst->next = NULL;
	return lst;
}

void addHead(node *&pHead, int data)
{
	if (!pHead)
		return;
	node *Curr = pHead;
	pHead = new node;
	pHead->key = data;
	pHead->next = Curr;
}

void addTail(node *&pHead, int data)
{
	if (!pHead)
		return;
	node *Curr = pHead;
	while (Curr->next != NULL)
	{
		Curr = Curr->next;
	}
	Curr->next = new node;
	Curr->next->key = data;
	Curr->next->next = NULL;
}

void removeHead(node *&pHead)
{
	if (!pHead)
		return;
	node *curr = pHead;
	pHead = pHead->next;
	delete curr;
}

void removeTail(node *&pHead)
{
	if (!pHead)
		return;
	node *curr = pHead;
	while (curr->next)
	{
		curr = curr->next;
	}
	delete curr;
}
void removeAll(node *&pHead)
{
	if (!pHead)
		return;
	while (pHead)
	{
		node *curr = pHead;
		pHead = pHead->next;
		delete curr;
	}
	pHead = NULL;
}

void removeBefore(node *&pHead, int val)
{
	if (countNode(pHead) <= 1)
		return;
	node *curr = pHead;
	if (curr->next->key == val)
	{
		removeHead(pHead);
		return;
	}
	while (curr->next->next)
	{
		if (curr->next->next->key == val)
		{
			node *temp = curr->next;
			curr->next = curr->next->next;
			delete temp;
		}
	}
}

void removeAfter(node *&pHead, int val)
{
	if (!pHead)
		return;
	node *curr = pHead;
	while (curr)
	{
		if (curr->key == val)
		{
			if (curr->next == NULL)
				return;
			if (curr->next->next == NULL)
			{
				removeTail(pHead);
				return;
			}
			node *temp = curr->next;
			curr->next = curr->next->next;
			delete temp;
		}
	}
}

node *reverseList(node *&pHead)
{
	if (!pHead)
		return pHead;
	node *temp = pHead;
	node *curr = creatNode(temp->key);
	temp = temp->next;
	while (temp)
	{
		addHead(curr, temp->key);
		temp = temp->next;
	}
	return curr;
}

void removeDuplicate(node *&pHead)
{
	if (!pHead)
		return;
	node *curr = pHead;
	while (curr)
	{
		node *temp = curr;
		while (temp->next)
		{
			if (curr->key == temp->next->key)
			{
				removeHead(temp->next);
			}
			else
			{
				temp = temp->next;
			}
		}
		curr = curr->next;
	}
}
void calcPoke(int *&typeLimit, int amountPoke, int boardSize)
{
	typeLimit = new int[amountPoke];
	// min xài để đếm số lượng tối thiểu 1 pokemon sẽ xuất hiện
	int minPoke = (boardSize * boardSize) / amountPoke;
	// excess dùng để tính có bao nhiêu pokemon sẽ dc +2 vào số lượng có thể dc xuất hiện
	int excessPoke = ((boardSize * boardSize) % amountPoke) / 2;
	// phân bổ số lượng vào từng pokemon
	for (int i = 0; i < amountPoke; i++)
	{
		typeLimit[i] = minPoke;
	}
	// chọn ngẫu nhiên những pokemon dc xuất hiện nhiều hơn
	for (int i = 0; i < excessPoke; i++)
	{
		typeLimit[rand() % 8] += 2;
	}
}
void generateRandomMatrix(int **&game, int boardSize, int *typeLimit)
{
	int type[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int countType[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	// khai báo mảng động
	game = new int *[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		game[i] = new int[boardSize];
	}
	// Tạo phần tử ngẫu nhiên
	for (int i = 0; i < boardSize; i++)
	{
		for (int k = 0; k < boardSize; k++)
		{
			int random;
			do
			{
				random = rand() % 8;
			} while (countType[random] >= typeLimit[random]);
			game[i][k] = type[random];
			countType[random]++;
		}
	}
}

void coutMatrix(int **&game, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			cout << game[i][k] << "  ";
		}
		cout << endl;
	}
}
void PrintNum(int n)
{
cout << n << endl;
if(n > 0)
PrintNum(n-1);
}
int main()
{
	srand(time(0));
	int **game;
	int n = 4;
	int *typeLimit;
	calcPoke(typeLimit, 8, n);
	generateRandomMatrix(game, n, typeLimit);
	coutMatrix(game, n);
	for (int i = 0; i < n; i++)
	{
		delete[] game[i];
	}
	delete[] game;
	game = NULL;
	delete[] typeLimit;
	system("pause");
	PrintNum(8);
	return 0;
}
