/*
 * =====================================================================================
 *
 *       Filename:  107.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2013 04:00:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <math.h>

#define INPUT stdin

int powerOf2(double k)
{
	int p = 0;
	int res = 1;
	while(true){
		if(res > k) return p-1;
		p++;
		res = res << 1;
	}
}

int main()
{
	int x, y;
	while(true){
		fscanf(INPUT, "%d %d", &x, &y);
		int ans1, ans2, N, k;
		if(x == 0 && y == 0 ) break;
		if(y == 1){
			N = 1; k = powerOf2(x);
			ans1 = k;
			ans2 = x*2 - 1;
		}else if(x == y + 1){
			N = y; k = 1;
			ans1 = 1;
			ans2 = x*(N+1) - y*N;
		}else{
			double n = 2.0;
			long double r = log(x) / log(y);
			while(fabs(log(n+1)/log(n) - r) > 1e-12) n++;
			N = n;
			//printf("N: %d \t k: %d\t\n", N,  k);
			ans1 = (y-1)/(N-1);
			ans2 = x*(N+1) - y * N;
		}
		printf("%d %d\n", ans1, ans2);
	}

	return 0;
}
