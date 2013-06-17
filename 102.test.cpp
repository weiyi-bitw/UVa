#include<stdio.h>
#include<string>
#include<map>

int main(){

	unsigned int bottles[9];
	const int N = 3;
	int test[3];
	int best[3];

	while(scanf("%u", &bottles[0])!=EOF){
	
		for(int i = 1; i < 9; i++){
			scanf("%u", &bottles[i]);
		}
		std::string out = "GCB";
		int minMove = bottles[0] + bottles[2] + bottles[3+0] + bottles[3+1] + bottles[6+1] + bottles[6+2];

		// GBC
		int tmp = bottles[0] + bottles[2] + bottles[3+1] + bottles[3+2] + bottles[6+0] + bottles[6+1];
		if(tmp <= minMove){
			minMove = tmp;
			out = "GBC";
		}

		// CGB
		tmp = bottles[0] + bottles[1] + bottles[3+0] + bottles[3+2] + bottles[6+1] + bottles[6+2];
		if(tmp <= minMove){
			minMove = tmp;
			out = "CGB";
		}

		// CBG
		tmp = bottles[0] + bottles[1] + bottles[3+1] + bottles[3+2] + bottles[6+0] + bottles[6+2];
		if(tmp <= minMove){
			minMove = tmp;
			out = "CBG";
		}

		// BGC
		tmp = bottles[1] + bottles[2] + bottles[3+0] + bottles[3+2] + bottles[6+0] + bottles[6+1];
		if(tmp <= minMove){
			minMove = tmp;
			out = "BGC";
		}

		// BCG
		tmp = bottles[1] + bottles[2] + bottles[3+0] + bottles[3+1] + bottles[6+0] + bottles[6+2];
		if(tmp <= minMove){
			minMove = tmp;
			out = "BCG";
		}


		printf("%s %u\n",
			out.c_str(),
			minMove);

	
	}
	return 0;
}

