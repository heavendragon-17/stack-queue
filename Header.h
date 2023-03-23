#pragma once
#include <string.h>
struct video {
	char* title;
	char catagory;
 };

struct node {
	int key;
	node* next;
};

struct stack {
	node* pTop;
};
