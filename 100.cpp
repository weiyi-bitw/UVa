#include <stdio.h>

int maxCycleLength(int a, int b, int *cl){
	int mcl = 0;
	for(int i = a; i <= b; i++){
		int x = i;
		if(cl[i] == 0){
			int c = 1;
			while(x != 1){
				if(x&1){
					x = 3*x+1;
				}
				else{
					 x = x/2;
				}
				if(x >= a & x <= b){
					if(cl[x] > 0){
						c = c + cl[x];
						break;
					}
				}
				c++;
			}
			cl[i] = c;
		}
		if(cl[i] > mcl) mcl = cl[i];
	}

	return mcl;

}

int main(){
	int lb, ub, mcl = -1;
	int *cl = new int[1000000];
	while(scanf("%d %d\n", &lb, &ub)==2){
		mcl = lb < ub? maxCycleLength(lb, ub, cl):maxCycleLength(ub, lb, cl) ;
		
		printf("%d %d %d\n", lb, ub, mcl);
	}

	delete []cl;
	return 0;
}
