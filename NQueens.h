#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
#include <vector>
#include <string>
using namespace std;

#define QUEEN 4     //皇后的数目  
#define INITIAL -10000   //棋盘的初始值  

int a[QUEEN];    //一维数组表示棋盘  

/*
非递归方法的一个重要问题时何时回溯及如何回溯的问题。程序首先对N行中的每一行进行探测，
寻找该行中可以放置皇后的位置，具体方法是对该行的每一列进行探测，看是否可以放置皇后，
如果可以，则在该列放置一个皇后，然后继续探测下一行的皇后位置。
如果已经探测完所有的列都没有找到可以放置皇后的列，此时就应该回溯，
把上一行皇后的位置往后移一列，如果上一行皇后移动后也找不到位置，
则继续回溯直至某一行找到皇后的位置或回溯到第一行，
如果第一行皇后也无法找到可以放置皇后的位置，则说明已经找到所有的解程序终止。
如果该行已经是最后一行，则探测完该行后，如果找到放置皇后的位置，则说明找到一个结果，打印出来。
但是此时并不能再此处结束程序，因为我们要找的是所有N皇后问题所有的解，
此时应该清除该行的皇后，从当前放置皇后列数的下一列继续探测。
*/

void init()  //对棋盘进行初始化  
{
	int *p;
	for (p = a; p < a + QUEEN; ++p)
	{
		*p = INITIAL;
	}
}

int valid(int row, int col)    //判断第row行第col列是否可以放置皇后  
{
	int i;
	for (i = 0; i < QUEEN; ++i)   //对棋盘进行扫描  
	{
		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //判断列冲突与斜线上的冲突  
			return 0;
	}
	return 1;
}

void print()    //打印输出N皇后的一组解  
{
	int i, j;
	for (i = 0; i < QUEEN; ++i)
	{
		for (j = 0; j < QUEEN; ++j)
		{
			if (a[i] != j)      //a[i]为初始值  
				printf("%c ", '.');
			else                //a[i]表示在第i行的第a[i]列可以放置皇后  
				printf("%c ", '#');
		}
		printf("\n");
	}
	for (i = 0; i < QUEEN; ++i)
		printf("%d ", a[i]);
	printf("\n");
	printf("--------------------------------\n");
}

void queen()      //N皇后程序  
{
	int n = 0;
	int i = 0, j = 0;
	while (i < QUEEN)
	{
		while (j < QUEEN)        //对i行的每一列进行探测，看是否可以放置皇后  
		{
			if (valid(i, j))      //该位置可以放置皇后  
			{
				a[i] = j;        //第i行放置皇后  
				j = 0;           //第i行放置皇后以后，需要继续探测下一行的皇后位置，所以此处将j清零，从下一行的第0列开始逐列探测  
				break;
			}
			else
			{
				++j;             //继续探测下一列  
			}
		}
		if (a[i] == INITIAL)         //第i行没有找到可以放置皇后的位置  
		{
			if (i == 0)             //回溯到第一行，仍然无法找到可以放置皇后的位置，则说明已经找到所有的解，程序终止  
				break;
			else                    //没有找到可以放置皇后的列，此时就应该回溯  
			{
				--i;
				j = a[i] + 1;        //把上一行皇后的位置往后移一列  
				a[i] = INITIAL;      //把上一行皇后的位置清除，重新探测  
				continue;
			}
		}
		if (i == QUEEN - 1)          //最后一行找到了一个皇后位置，说明找到一个结果，打印出来  
		{
			printf("answer %d : \n", ++n);
			print();
			//不能在此处结束程序，因为我们要找的是N皇后问题的所有解，此时应该清除该行的皇后，从当前放置皇后列数的下一列继续探测。  
			//_sleep(600);  
			j = a[i] + 1;             //从最后一行放置皇后列数的下一列继续探测  
			a[i] = INITIAL;           //清除最后一行的皇后位置  
			continue;
		}
		++i;              //继续探测下一行的皇后位置  
	}
}

bool isValid(const vector<int> &C, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		//the same col
		if (C[i] == col) return false;
		if (abs(i - row) == abs(a[i] - col)) return false;
	}
	return true;
}

void dfs(vector<int> &C, vector<vector<string>> &result, int row)
{
	const int N = C.size();
	if (row == N){ //solution get
		vector<string> solution;
		
		for (int i = 0; i < N; ++i)
		{
			string s(N, '.');
			for (int j = 0; j < N; ++j)
			{
				if (j == C[i]) s[j] = 'Q';
			}
			solution.push_back(s);
		}
		result.push_back(solution);
		return;
	}

	for (int j = 0; j < N; ++j)
	{
		const bool ok = isValid(C, row, j);
		if (!ok) continue;
		//extend
		C[row] = j;
		dfs(C, result, row + 1);
		//back
		//C[row] = -1;
	}
}

vector<vector<string>> solveNQueens(int n)
{
	vector<vector<string>> result;
	vector<int> C(n, -1);
	dfs(C, result, 0);
	return result;
}


void queenII()
{
	int i = 0, j = 0;
	while (i < QUEEN)
	{
		while (j < QUEEN)
		{
			if (valid(i, j))
			{
				a[i] = j;
				j = 0; 
				break;
			}
			else
			{
				++j;
			}
		}
		if (a[i] == INITIAL)
		{
			if (i == 0)
			{
				break; //get all result
			}
			else
			{
				--i;
				j = a[i] + 1;
				a[i] = INITIAL;
				continue;
			}
		}
		if (i == QUEEN -1)
		{
			//print();
			j = a[i] + 1;
			a[i] = INITIAL;
			continue;
		}
		 
	}
}