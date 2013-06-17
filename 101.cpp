#include <stdio.h>
#include <string.h>

class Block;
class Stack;

class Block{
  private:
	int id;
  public:
	Stack *pos;
	Block *below;
	Block(){below=NULL;}
	Block(int i){
		id = i;
		pos = NULL;
		below = NULL;
	}
	Block(int i, Block* b){
		id = i;
		pos = b->pos;
		below = b;
	}
	void setID(int i){
		id = i;
	}
	int getID(){
		return id;
	}
	
};

class Stack{
  public:
	Block *top;
	Stack(){top = NULL;}
	Stack(Block *b){
		top = b;
		b->pos = this;
	}
	void push(Block *b){
		b->below = top;
		b->pos = this;
		top = b;
	}
	Block* pop(){
		Block *b = top;
		top = top->below;
		b->below = NULL;
		b->pos = NULL;
		return b;
	}
	
};

Block* move(Stack *s, Block *b){
	Block *p;
	while(b->pos->top != b){
		// return all blocks on top of b back to where they started
		p = b->pos->pop();
		s[p->getID()].push(p);
	}
	return b->pos->pop();
}

Block* pile(Stack *s, Block *b){ 
// clear all position information and return the top block of the pile
	Block *p = b->pos->top;
	
	if(p != b){
		Block *pp = p;
		while(pp != b){
			pp->pos = NULL;
			pp = pp->below;
		}	
	}
	
	b->pos->top = b->below;
	b->below=NULL;
	b->pos = NULL;
	return p;
}

void onto(Stack *s, Block *b, Block *bdes){
	Block *p;
	while(bdes->pos->top != bdes){
		// return all blocks on top of b back to where they started
		p = bdes->pos->pop();
		s[p->getID()].push(p);
	}
	bdes->pos->top = b;
	while(b->below != NULL){
		b->pos = bdes->pos;
		b = b->below;
	}
	b->pos = bdes->pos;
	b->below = bdes;
}

void over(Stack *s, Block *b, Block *bdes){
	Block *p = bdes->pos->top;
	bdes->pos->top = b;
	while(b->below != NULL){
		b->pos = bdes->pos;
		b = b->below;
	}
	b->pos = bdes->pos;
	b->below = p;
}

void printStacks(Stack *s, int size){
	int buffer[25];
	for(int i = 0; i < size; i++){
		Block *p = s[i].top;
		int count = 0;
		while(p != NULL){
			buffer[count] = p->getID();
			p = p->below;
			count++;
		}
		printf("%d:", i);
		while(count > 0){
			printf(" %d", buffer[count-1]);
			count--;
		}
		printf("\n");
	}
}


int main(){
	int size;
	int pos1, pos2;
	char action[5], prepo[5], cmdEndPhrase[] = "quit";
	char cmdmove[] = "move";
	char cmdpile[] = "pile";
	char cmdonto[] = "onto";
	char cmdover[] = "over";

	scanf("%d\n", &size);
	Stack *place = new Stack[size];
	Block *blks = new Block[size];
	for(int i = 0; i < size; i++){
		blks[i].setID(i);
		place[i].push( &blks[i] );
	}
	//printStacks(place, size);
	do{
		scanf("%s %d %s %d\n", action, &pos1, prepo, &pos2);
		//printf("%s\t%d\t%s\t%d...", action, pos1, prepo, pos2);
		// check for command integrity
		if(pos1 == pos2) continue;
		if(pos1 < 0 || pos1 >= size) continue;
		if(pos2 < 0 || pos2 >= size) continue;
		if(blks[pos1].pos == blks[pos2].pos) continue;

		Block *p1;
		if(strncmp(action, cmdmove, 4) == 0){
		//if(action[0] == 'm'){
			p1 = move(place, &blks[pos1]);
		}else if(strncmp(action, cmdpile, 4) == 0){
		//}else if(action[0] == 'p'){
			p1 = pile(place, &blks[pos1]);
		}else{
			continue;
		}

		if(strncmp(prepo, cmdonto, 4)==0){
		//if(prepo[1] == 'n'){
			onto(place, p1, &blks[pos2]);
		}else if(strncmp(prepo, cmdover, 4) == 0){
		//}else if(prepo[1] == 'v'){
			over(place, p1, &blks[pos2]);
		}
		//printf("Finished.\n");
		//printStacks(place, size);
	}while(strncmp(action, cmdEndPhrase, 4) != 0);

	printStacks(place, size);

	delete []blks;
	delete []place;

	return 0;
}


