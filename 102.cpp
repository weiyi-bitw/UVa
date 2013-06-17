#include<stdio.h>
#include<string>
#include<cstring>
#include<map>

bool getNext(int *indices, int N){
	int i = N-2;
	int tmp;
	while(indices[i] >= indices[i+1]){
	// find the first pair of indices that's of the right order
		i--;
		if(i == 0) break;
	}

	int j = N-1;
	while(indices[j] <= indices[i]){
	// find the first index that's greater than i
		j--;
		if(j == 0) break;
	}
	if(i == j) return false;
	// swap(i, j)
	tmp = indices[j];
	indices[j] = indices[i];
	indices[i] = tmp;

	i++;
	j = N-1;
	while(i < j){
		tmp = indices[j];
		indices[j] = indices[i];
		indices[i] = tmp;
		i++;
		j--;
	}

	return true;
}
int main(){

	unsigned int bottles[9];
	const int N = 3;
	int test[3];
	int best[3];
	std::map<int, char> bottleMap;
	bottleMap[0] = 'B';
	bottleMap[1] = 'G';
	bottleMap[2] = 'C';

	while(scanf("%u", &bottles[0])!=EOF){
	
		for(int i = 1; i < 9; i++){
			int garbage = scanf("%u", &bottles[i]);
		}
		for(int i = 0; i < N; i++){
			best[i] = i;
			test[i] = i;
		}
		unsigned int minMove = 0;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(j != test[i]) minMove += bottles[j+i*3];
			}
		}
		int bestCount = ( (bottleMap[best[0]] << 2) + (bottleMap[best[1]]<<1) + bottleMap[best[2]]);
		while(getNext(test, N)){
			unsigned int moveCount = 0;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if(j != test[i]) moveCount += bottles[j+i*3];
				}
			}
			if(moveCount < minMove){
				minMove = moveCount;
				for(int i = 0; i < N; i++){
					best[i] = test[i];
				}
			}else if(moveCount == minMove){
				int newCount = ( (bottleMap[test[0]]<<2) + (bottleMap[test[1]]<<1) + bottleMap[test[2]]);
				if(newCount < bestCount) {
					for(int i = 0; i < N; i++){
						best[i] = test[i];
					}
					bestCount = newCount;
				}
			}
		}
		char out[] = {bottleMap[best[0]], bottleMap[best[1]], bottleMap[best[2]], '\0'};
		printf("%s %u\n",
			out,
			minMove);
	
	}
	return 0;
}

