#include <iostream>
#include <algorithm>
using namespace std;
#define N 1024
int palindromePartitionII(string s)
{
	const int n = s.size();
	bool p[N][N];
	int f[N + 1];
	fill_n(&p[0][0], n, false);
	for (int i = 0; i <= n; i++)
	{
		f[i] = n - 1 - i;
	}
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = i; j < n; j++)
		{
			if (s[i] == s[j] && (j- i < 2 || p[i+1][j-1]))
			{
				p[i][j] = true;
				f[i] = min(f[i], f[j + 1] + 1);
			}
		}
	}
	return f[0];
}