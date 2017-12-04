#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int Candy(vector<int>& ratings)
{
	const int n = ratings.size();
	vector<int> increment(n);
	for (int i = 1, inc = 1; i < n; i++)
	{
		if (ratings[i] > ratings[i-1])
		{
			increment[i] = max(inc++, increment[i]);
		}
		else
			inc = 1;
	}
	for (int i = n-2, inc = 1; i >= 0; i--)
	{
		if (ratings[i] > ratings[i + 1])
		{
			increment[i] = max(inc++, increment[i]);
		}
		else
			inc = 1;
	}
	return accumulate(&increment[0], &increment[0] + n, n);
}

int CandyII(vector<int>& ratings)
{
	const int n = ratings.size();
	vector<int> increment(n);
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += solve(ratings, increment, i);
	}
	
	return sum;
}

int solve(vector<int> &ratings, vector<int> &increment, int i)
{
	if (increment[i] == 0)
	{
		increment[i] = 1;
		if (ratings[i] > ratings[i -1] && i > 0)
		{
			increment[i] = max(increment[i], solve(ratings, increment, i - 1) + 1);
		}
		if (ratings[i] > ratings[i + 1] && i < ratings.size() -1)
		{
			increment[i] = max(increment[i], solve(ratings, increment, i + 1) + 1);
		}
	}
	return increment[i];
}