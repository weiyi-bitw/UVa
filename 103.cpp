#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define INPUT stdin

int compare(const void *a, const void *b){
	return (*(int*)a - *(int*)b);
}


class Box{
  private:
	int nd; // number of dimensions
	int *dim; // measurements of each dimension
	int ID;
  public:
	Box *inside;
	int streak;
	int dimsum;
	Box(){}
	void setBox(int i, int n, int *d){
		ID = i;
		nd = n;
		inside = NULL;
		streak = 1;
		dimsum = 0;
		dim = new int[n];
		for(int i = 0; i < n; i++){
			dim[i] = d[i];
			dimsum += dim[i];
		}
		qsort(dim, n, sizeof(int), compare);
	}
	Box(int i, int n, int *d){
		ID = i;
		nd = n;
		inside = NULL;
		streak = 1;
		dimsum = 0;
		dim = new int[n];
		for(int i = 0; i < n; i++){
			 dim[i] = d[i];
			dimsum += dim[i];
		}
		qsort(dim, n, sizeof(int), compare);
	}
	~Box(){
		inside = NULL;
		delete[] dim;
	}
	void print(){
		printf("%d: ", ID);
		for(int i = 0; i < nd; i++) printf(" %d", dim[i]);
		printf("\n");
	}
	void printStreak(){
		printf("%d\n", this->streak);

		int *buffer = new int[streak];
		Box *p = this;
		for(int i = 0; i < streak; i++){
			//p->print();
			buffer[streak-i-1] = p->ID;
			p = p->inside;
		}
		printf("%d", buffer[0]);
		for(int i = 1; i < streak; i++){
			printf(" %d", buffer[i]);
		}printf("\n");

		delete [] buffer;
	}
	bool fitIn(Box *bigBox){
		int *dim2 = bigBox->dim;
		for(int i = 0; i < nd; i++){
			if(dim2[i] <= dim[i]) return false;
		}
		return true;
	}

};
int compareStreak(const void *a, const void *b){
	const Box* _a = reinterpret_cast<const Box*>(a);
	const Box* _b = reinterpret_cast<const Box*>(b);
	return (_a->streak - _b->streak);
}
int compareDim(const void *a, const void *b){
	const Box* _a = reinterpret_cast<const Box*>(a);
	const Box* _b = reinterpret_cast<const Box*>(b);
	return (_a->dimsum - _b->dimsum);
}

Box* findLongestNesting(Box* boxes, int numB){
	int ln = 1;
	Box* p = &boxes[0];
	for(int i = 1; i < numB; i++){
		int bestStreak = 1;
		Box* bestInside;
		for(int j = 0; j < i; j++){
			if(boxes[j].fitIn(&boxes[i])){
				if(boxes[j].streak + boxes[i].streak > bestStreak){
					bestInside = &boxes[j];
					bestStreak = boxes[i].streak + boxes[j].streak;
				}				
			}
		}
		boxes[i].inside = bestInside;
		boxes[i].streak = bestStreak;
		if(boxes[i].streak > ln){
			p = &boxes[i];
			ln = boxes[i].streak;
		}
	}
	return p;
}




int main(){
	int numBox;
	int numDim;

	while(fscanf(INPUT, "%d %d", &numBox, &numDim) != EOF){
		//printf("Number of boxes: %d\n Dimension: %d\n", numBox, numDim);
		int* dims = new int[numDim];
		Box* boxes = new Box[numBox];

		for(int b = 0; b < numBox; b++){
			for(int i = 0; i < numDim; i++){
				fscanf(INPUT, "%d", &dims[i]);
			}
			boxes[b].setBox(b+1, numDim, dims);
		}

		qsort(boxes, numBox, sizeof(Box), compareDim);
		//printf("Boxes: \n");
		//for(int i = 0; i < numBox; i++){
		//	boxes[i].print();
		//}

		Box* outMost = findLongestNesting(boxes, numBox);
		//printf("Streak:\n");
		outMost->printStreak();

		delete [] dims;
		delete [] boxes;

	}

}
