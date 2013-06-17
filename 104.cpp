#include <stdio.h>

#define NMAX 20
#define THRESHOLD 1.01
#define i2c(i, j) (j + (int)(j>=i))
#define c2i(i, j) (j - (int)(j>=i))
#define INPUT stdin
#define EPS 1e-10

void findArbitrage(double** rates, int ***trace, double **curRate, int N){
	// initialization
	for(int i = 0; i < N; i++){// source
		for(int j = 0; j < N; j++){ // destination
			int k = 0;
			curRate[i][j] = rates[i][j];
			trace[i][j][k] = i;
			for(k = 1; k < N; k++){ // link size
				trace[i][j][k] = -1;
			}
			//===== DEBUG
			//printf("%f\t", curRate[i][j]);
		}
		// ===== DEBUG
		//printf("\n");
	}

	
	for(int k = 1; k < N; k++){
	  for(int i = 0; i < N; i++){
	    double bestRates[N];
 	    for(int j = 0; j < N; j++){
	      bestRates[j] = 0;
	      int bestSource = -1;
	      for(int l = 0; l < N; l++){
		double r = curRate[i][l] * rates[l][j];
		if(r > bestRates[j]){
			bestRates[j] = r;
			bestSource = l;
		}
	      }
	      trace[i][j][k] = bestSource;	
	    }
	    for(int j = 0; j < N; j++) curRate[i][j] = bestRates[j];	
	    if(curRate[i][i] - THRESHOLD >= EPS){
		int traceout[k+1];
		int back = trace[i][i][k];
		traceout[k] = back;
		for(int l = k-1; l >= 0 ; l--){
			back = trace[i][back][l];
			traceout[l] = back;
		}
		for(int l = 0; l < k+1; l++){
			printf("%d ", traceout[l]+1);
		}
		printf("%d\n", i+1);
		return;
	    }
	  }
	/*
	//====== DEBUG
	printf("k = %d:\n", k);
	for(int i = 0; i < N; i++){
		printf("i = %d:\n", i);
		for(int j = 0; j < N; j++){
			for(int l = 0; l < k; l++){
				printf("%d\t", trace[i][j][k]);
			}printf("%f\n", curRate[i][j]);
		}
	}
	//=================
	*/


	}

	printf("no arbitrage sequence exists\n");
}


int main(){
	int N;
	double **rates = new double*[NMAX];
	int ***trace = new int**[NMAX];
	double **curRates = new double*[NMAX];
	for(int i = 0; i < NMAX; i++){
		rates[i] = new double[NMAX];
		curRates[i] = new double[NMAX];
		trace[i] = new int*[NMAX];
		for(int j = 0; j < NMAX; j++){
			trace[i][j] = new int[NMAX];
		}
	}

	while(fscanf(INPUT, "%d", &N) != EOF){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(i==j){
					rates[i][j] = 1;
				}else{
					fscanf(INPUT, "%lf", &rates[i][j]);
				}
			}
		}
		/*
		//======= DEBUG
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				printf("%f\t", rates[i][j]);
			}printf("\n");
		}
		//=========================
		*/
		findArbitrage(rates, trace, curRates, N);
	}


	for(int i = 0; i < NMAX; i++){
		delete [] rates[i];
		delete [] curRates[i];
		for(int j = 0; j < NMAX; j++){
			delete [] trace[i][j];
		}
		delete [] trace[i];
	}
	delete [] curRates;
	delete [] rates;
	delete [] trace;
}
