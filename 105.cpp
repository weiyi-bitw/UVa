/*
 * =====================================================================================
 *
 *       Filename:  105.cpp
 *
 *    Description:  105 - The Skyline Problem
 *
 *        Version:  1.0
 *        Created:  06/19/2013 10:22:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

/*
 * Tree solution will probably need parent index, which is too complicated
 * Here I will try a sorted list solution.
 */

#include <stdlib.h>
#include <stdio.h>

#define INPUT stdin

class Node{
  public:
	int x;
	int h;
	Node* next;
	Node(int xin, int hin){
		x = xin;
		h = hin;
		next = NULL;
	}
};

class Skyline{
  public:
	Node *head;
	int size;
	Skyline(){
		head = NULL;
		size = 0;
	}
	void addBuilding(int x1, int h, int x2){ 
		/* debug message */
			//printf("Insert (%d, %d, %d)\n", x1, h, x2);
		Node *p = NULL, *it;
		int lowerBound = 0;
		// (x1, h) insert after p, (x2, 0) insert after q
		if(head == NULL){ 
			head = new Node(x1, h);
		}
		it = head;
		// find insertion point for x1
		while(it != NULL){
			if(it->x >= x1) break;
			p = it;
			it = it->next;
		}

		if(it == NULL){
			p->next = new Node(x1, h);
			p = p->next;
		// change height of it or insert after p
		}else if(it->x == x1){ // change the height of it
			if(it->h < h){ 
				lowerBound = it->h;
				it->h = h;
			}

			p = it;
			it = it->next;
		}else if(p->h < h){ // insert node after p
			lowerBound = p->h;
			p->next = new Node(x1, h);
			p = p->next;
			p->next = it;
		}
	
		// find insertion point for x2
		while(it != NULL){
			if(it->x >= x2) break;
			if(it->h <= h){
				lowerBound = it->h;
				if(p->h > h){
					it->h = h; 
				}else{
					Node *tmp = it->next;
					p->next = tmp;
					delete it;
					it = p;
				}
			}
			p = it;
			it = it->next;
		}
		if(it == NULL){
			p->next = new Node(x2, 0);	
		}else if(it->x > x2){
			if(p->h == h){
				p->next = new Node(x2, lowerBound);
				p = p->next;
				p->next = it;
			}
		}
	}

	void print(){
		Node *it = head;
		printf("%d %d", it->x, it->h);
		it = it->next;
		while(it != NULL){
			printf(" %d %d", it->x, it->h);
			it = it->next;
		}
		printf("\n");
	}
};

int main(){
	int x1, h, x2;
	Skyline skl;
	while(fscanf(INPUT, "%d %d %d", &x1, &h, &x2) == 3){
		skl.addBuilding(x1, h, x2);
	}
	skl.print();
	return 0;
}
