#include <vector>
#include <iostream>
using namespace std;

void Permutation(vector<int>& a, int k, int n)
{
	if (k == n)
	{
		for (int i = 0; i < a.size(); i++)
		{
			cout << " " << a[i];
		}
		cout << endl;
	}
	else
	{
		for (int i = k; k < n; k++)
		{
			a[k] = a[i];
			Permutation(a, k + 1, n);
		}
	}
}