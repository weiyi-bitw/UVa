/*
 * =====================================================================================
 *
 *       Filename:  108.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/03/2013 09:33:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

int maxSum(int** m, int N)
{
	int mx = m[0][0];
	for(int y = 0; y < N; y++){
		for(int w = 1; w <= (y+1); w++){
			int max_end_here = m[0][y+1] - m[0][y+1-w];
			int max_so_far = max_end_here;
			for(int x = 1; x < N; x++){
				int rowSum = (m[x][y+1] - m[x][y+1-w]);
				max_end_here = max_end_here > 0 ? rowSum + max_end_here : rowSum;
				max_so_far = max_end_here > max_so_far ? max_end_here : max_so_far;
			}
			//cout << "y = " << y << " : " << max_so_far << endl;
			if(max_so_far > mx) mx = max_so_far;
		}
	}
	return mx;
}


int main()
{
	int N;

	while(cin >> N){
		int *matmem = new int[ N * (N+1)];
		int **mat = new int* [ N ];
		int maxElement = 0;
		for(int i = 0; i < N; i++){
			mat[i] = &matmem[i*(N+1)];
			mat[i][0] = 0;
			for(int j = 1; j <= N; j++){
				int kIn;
				cin >> kIn;
				if(kIn > maxElement) maxElement = kIn;
				mat[i][j] = mat[i][j-1] + kIn;
			}
		}
		/* 
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N+1; j++){
				cout << mat[i][j] << "\t";
			}cout << endl;
		}
		*/
		int mx = maxSum(mat, N);
		mx = mx > 0 ? mx : maxElement;
		cout << mx << endl;
		delete [] matmem;
		delete [] mat;
	}

	

	return 0;
}



