#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
#include <vector>
#include <string>
using namespace std;

#define QUEEN 4     //�ʺ����Ŀ  
#define INITIAL -10000   //���̵ĳ�ʼֵ  

int a[QUEEN];    //һά�����ʾ����  

/*
�ǵݹ鷽����һ����Ҫ����ʱ��ʱ���ݼ���λ��ݵ����⡣�������ȶ�N���е�ÿһ�н���̽�⣬
Ѱ�Ҹ����п��Է��ûʺ��λ�ã����巽���ǶԸ��е�ÿһ�н���̽�⣬���Ƿ���Է��ûʺ�
������ԣ����ڸ��з���һ���ʺ�Ȼ�����̽����һ�еĻʺ�λ�á�
����Ѿ�̽�������е��ж�û���ҵ����Է��ûʺ���У���ʱ��Ӧ�û��ݣ�
����һ�лʺ��λ��������һ�У������һ�лʺ��ƶ���Ҳ�Ҳ���λ�ã�
���������ֱ��ĳһ���ҵ��ʺ��λ�û���ݵ���һ�У�
�����һ�лʺ�Ҳ�޷��ҵ����Է��ûʺ��λ�ã���˵���Ѿ��ҵ����еĽ������ֹ��
��������Ѿ������һ�У���̽������к�����ҵ����ûʺ��λ�ã���˵���ҵ�һ���������ӡ������
���Ǵ�ʱ�������ٴ˴�����������Ϊ����Ҫ�ҵ�������N�ʺ��������еĽ⣬
��ʱӦ��������еĻʺ󣬴ӵ�ǰ���ûʺ���������һ�м���̽�⡣
*/

void init()  //�����̽��г�ʼ��  
{
	int *p;
	for (p = a; p < a + QUEEN; ++p)
	{
		*p = INITIAL;
	}
}

int valid(int row, int col)    //�жϵ�row�е�col���Ƿ���Է��ûʺ�  
{
	int i;
	for (i = 0; i < QUEEN; ++i)   //�����̽���ɨ��  
	{
		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //�ж��г�ͻ��б���ϵĳ�ͻ  
			return 0;
	}
	return 1;
}

void print()    //��ӡ���N�ʺ��һ���  
{
	int i, j;
	for (i = 0; i < QUEEN; ++i)
	{
		for (j = 0; j < QUEEN; ++j)
		{
			if (a[i] != j)      //a[i]Ϊ��ʼֵ  
				printf("%c ", '.');
			else                //a[i]��ʾ�ڵ�i�еĵ�a[i]�п��Է��ûʺ�  
				printf("%c ", '#');
		}
		printf("\n");
	}
	for (i = 0; i < QUEEN; ++i)
		printf("%d ", a[i]);
	printf("\n");
	printf("--------------------------------\n");
}

void queen()      //N�ʺ����  
{
	int n = 0;
	int i = 0, j = 0;
	while (i < QUEEN)
	{
		while (j < QUEEN)        //��i�е�ÿһ�н���̽�⣬���Ƿ���Է��ûʺ�  
		{
			if (valid(i, j))      //��λ�ÿ��Է��ûʺ�  
			{
				a[i] = j;        //��i�з��ûʺ�  
				j = 0;           //��i�з��ûʺ��Ժ���Ҫ����̽����һ�еĻʺ�λ�ã����Դ˴���j���㣬����һ�еĵ�0�п�ʼ����̽��  
				break;
			}
			else
			{
				++j;             //����̽����һ��  
			}
		}
		if (a[i] == INITIAL)         //��i��û���ҵ����Է��ûʺ��λ��  
		{
			if (i == 0)             //���ݵ���һ�У���Ȼ�޷��ҵ����Է��ûʺ��λ�ã���˵���Ѿ��ҵ����еĽ⣬������ֹ  
				break;
			else                    //û���ҵ����Է��ûʺ���У���ʱ��Ӧ�û���  
			{
				--i;
				j = a[i] + 1;        //����һ�лʺ��λ��������һ��  
				a[i] = INITIAL;      //����һ�лʺ��λ�����������̽��  
				continue;
			}
		}
		if (i == QUEEN - 1)          //���һ���ҵ���һ���ʺ�λ�ã�˵���ҵ�һ���������ӡ����  
		{
			printf("answer %d : \n", ++n);
			print();
			//�����ڴ˴�����������Ϊ����Ҫ�ҵ���N�ʺ���������н⣬��ʱӦ��������еĻʺ󣬴ӵ�ǰ���ûʺ���������һ�м���̽�⡣  
			//_sleep(600);  
			j = a[i] + 1;             //�����һ�з��ûʺ���������һ�м���̽��  
			a[i] = INITIAL;           //������һ�еĻʺ�λ��  
			continue;
		}
		++i;              //����̽����һ�еĻʺ�λ��  
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