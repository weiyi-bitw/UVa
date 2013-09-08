/*
 * =====================================================================================
 *
 *       Filename:  106.cpp
 *
 *    Description:  106 - Fermat vs. Pythagoras
 *
 *        Version:  1.0
 *        Created:  06/17/2013 04:17:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>
#define INPUT stdin


bool relativePrime2(int x, int y){
	int t1 = x, t2 = y, r;
	if(t1 == 1) return true;
	r = t2 % t1;
	while(r > 1){
		t2 = t1;
		t1 = r;
		r = t2 % t1;	
	}
	return r;
}

bool relativePrime(int x, int y, int z){
	if(!relativePrime2(x, y)) return false;
	if(!relativePrime2(y, z)) return false;
	if(!relativePrime2(x, z)) return false;
	return true;
}

void find_fermat(int N){
	int r, s, x, y, z, tmp, tripCnt = 0;
	bool *trip = new bool[N];
	for(int i = 0; i < N; i++) trip[i] = false;
	int upperBound = sqrt(N) + 1;	

	for(r = 1; r < upperBound-1; r++){
		for(s = r+1; s < upperBound; s++){
			if(!relativePrime2(r, s)) continue;
			x = s*s - r*r;
			y = 2*r*s;
			if(x > y){
				tmp = y;
				y = x;
				x = tmp;
			} 
			z = s*s + r*r;
			if(z > N) break;
			trip[x-1] = trip[y-1] = trip[z-1] = true;
			if(relativePrime(x, y, z)){ 
				tripCnt++;
				//printf("%d, %d: %d %d %d\n",r, s, x, y, z);
				for(int k = 2; z*k <= N; k++){
					trip[x*k-1] = trip[y*k-1] = trip[z*k-1] = true;
				}
			}
		}
	}

	int loneCnt = 0;
	for(int i = 0; i < N; i++) if(!trip[i]) loneCnt++;

	printf("%d %d\n",tripCnt, loneCnt);

	delete [] trip;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	int N;
	while(fscanf(INPUT, "%d", &N) != EOF){
		find_fermat(N);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */



