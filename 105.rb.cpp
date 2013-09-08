/*
Red black tree, Node.idx, Node.height
insert(Building)
find index interval, change heights (or delete nodes) of Nodes between

** 'cause the input is sorted, it is unbalanced if we create a BST

The RB tree implementation is from:
http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx
*/

#include<stdio.h>
#include<stdlib.h>

class Node{
  public:
	int x;
	int h;
	bool red;
	Node* child[2];
	Node(int xin){
		x = xin;
		h = -1;
		red = true; // always color a new node red
		child[0] = child[1] = NULL;
	}
	Node(int xin, int hin){
		x = xin;
		h = hin;
		red = true; // always color a new node red
		child[0] = child[1] = NULL;
	}
};

class RedBlackTree{
  private:
	void printTree_r(Node*, int);
	Node* rotate(Node*, int);
	Node* double_rotate(Node*, int);
  public:
	Node* root;
	RedBlackTree(){root = NULL;}
	bool insert(int d);
	bool remove(int d);
	void printTree(){
		printTree_r(root, 0);
		printf("\n");
	}
};

bool is_red(Node *n){
	return (n!=NULL && n->red);
}

void RedBlackTree::printTree_r(Node* n, int level){
	if(n==NULL){
		for(int i = 0; i < level; i++) printf("\t");
		printf("~\n");
	}else{
		printTree_r(n->child[1], level+1);
		for(int i = 0; i < level; i++) printf("\t");
		printf("%d,%d,%c\n", n->x, n->h, n->red? 'R' : 'B');
		printTree_r(n->child[0], level+1);
	}
}

Node* RedBlackTree::rotate(Node* n, int dir){
	printf("Single rotation -- n: %d, dir: %d\n", n->x, dir);
	Node* c = n->child[!dir];
	n->child[!dir] = c->child[dir];
	c->child[dir] = n;

	c->red = false;
	n->red = true;
	return c;
}

Node* RedBlackTree::double_rotate(Node* n, int dir){
	printf("Double rotation -- n: %d, dir: %d\n", n->x, dir);
	n->child[!dir] = rotate(n->child[!dir], !dir);
	return rotate(n, dir);
}

bool RedBlackTree::insert(int d){
	printf("Insert %d.\n", d);
	if(root == NULL) root = new Node(d);
	else{
		Node *head = new Node(-999);
		Node *g, *t; // t: great grandparent and g: grandparent
		Node *p, *q; // q: iterator and p: parent
		int dir = 0, last;
		
		t = head;
		g = p = NULL;
		q = t->child[1] = root;

		/* search down the tree */
		while(true){
			if(q==NULL){
				/* insert new node at bottom */
				p->child[dir] = q = new Node(d);
			}else if( is_red(q->child[0]) && is_red(q->child[1]) ){
				/* color flip */
				q->red = true;
				q->child[0]->red = q->child[1]->red = false;
			}

			/*  fix red violation */
			if(is_red(q) && is_red(p)){
				int dir2 = t->child[1] == g;
				if(q == p->child[last])
					t->child[dir2] = rotate(g, !last);
				else
					t->child[dir2] = double_rotate(g, !last);
			}

			/*  stop if found */
			if(q->x == d) break;
			
			last = dir;
			dir = d > q->x;

			if(g != NULL) t = g;
			g = p;
			p = q;
			q = q->child[dir];
		}
		/* update root */
		root = head->child[1];
		delete head;
	}
	/* make root black */
	root->red=false;
	return 1;
}

bool RedBlackTree::remove(int d){
	printf("Remove %d.\n", d);
	if(root != NULL){
		Node *head = new Node(-999);
		Node *q, *p, *g;
		Node *f = NULL;
		int dir = 1;
	
		q = head;
		g = p = NULL;
		q->child[1] = root;
		/* search and push red down */
		while(q->child[dir] != NULL){
			int last = dir;
			
			/* update helpers */
			g = p; p = q;
			q = q->child[dir];
			dir = d > q->x;
			
			if(q->x == d) f = q;

			/* push red node down */
			if(!is_red(q) && !is_red(q->child[dir])){
				if(is_red(q->child[!dir])){
					/* black q, black q child, red sibling */
					p = p->child[last] = rotate(q, dir);
				}else if(!is_red(q->child[!dir])){
					Node *s = p->child[!last];
					
					if(s != NULL){
						if(!is_red(s->child[!last]) && !is_red(s->child[last])){
							/* color flip */
							p->red = false;
							q->red = true;
							s->red = true;
						}else{
							int dir2 = g->child[1] == p;
							if(is_red(s->child[last])){
								g->child[dir2] = double_rotate(p, last);
							}else if(is_red(s->child[!last])){
								g->child[dir2] = rotate(p, last);
							}

							/* correct coloring */
							q->red = g->child[dir2]->red = true;
							g->child[dir2]->child[0]->red = false;
							g->child[dir2]->child[1]->red = false;
						}
					}
				}
			}
		}
		if(f != NULL){
			f->x = q->x;
			p->child[p->child[1]==q] = q->child[q->child[0] == NULL];
			delete q;
		}

		/* update root and make it black */
		root = head->child[1];
		delete head;
		if(root != NULL) root->red = false;
	}
	return 1;
}

int main(){
	RedBlackTree rbt;
	rbt.insert(0);
	rbt.printTree();
	rbt.insert(2);
	rbt.printTree();
	rbt.insert(4);
	rbt.printTree();
	rbt.insert(6);
	rbt.printTree();
	rbt.insert(5);
	rbt.printTree();
	rbt.insert(3);
	rbt.printTree();
	rbt.insert(1);
	rbt.printTree();
	
	rbt.remove(1);
	rbt.printTree();
	rbt.remove(6);
	rbt.printTree();


	return 0;
}

