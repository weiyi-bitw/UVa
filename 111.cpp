/*
 * =====================================================================================
 *
 *       Filename:  111.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/09/2013 02:53:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <stdio.h>

int dpMatrix[21][21];
int gs[20];
int ans[20];
int order[20];

int dpLongestSequence(int gs[], int ans[], int N)
{
	for(int j = 0; j < N+1; j++) dpMatrix[0][j] = 0;
	for(int i = 1; i < N+1; i++){
		dpMatrix[i][0] = 0;
		for(int j = 1; j < N+1; j++){
			if(ans[i-1] == gs[j-1]) dpMatrix[i][j] = dpMatrix[i-1][j-1] + 1;
			else dpMatrix[i][j] = dpMatrix[i-1][j] > dpMatrix[i][j-1] ? dpMatrix[i-1][j] : dpMatrix[i][j-1];
		}
	}

	return dpMatrix[N][N];
}

int main()
{
	int n;
	int temp;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &order[i]);
	for(int i = 0; i < n; i++)
		gs[order[i]-1] = i;

	while( scanf("%d", &temp) == 1){
		order[0] = temp;
		for(int i = 1; i < n; i++) scanf("%d", &order[i]); 
		for(int i = 0; i < n; i++) ans[order[i]-1] = i;
		printf("%d\n", dpLongestSequence(gs, ans, n));
	}

	
	return 0;
}





