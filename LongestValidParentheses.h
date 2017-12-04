#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int longestValidParenthese(string& s)
{
	int size = s.size();
	stack<int> lefts;
	int last = -1, max_len = 0;
	for (int i = 0; i < size; i++)
	{
		if (s[i] == '(')
			lefts.push(i);
		else
		{
			if (lefts.empty())
				last = i; //no match pair
			else
			{
				lefts.pop();
				if (lefts.empty())
					max_len = max(max_len, i - last);
				else
					max_len = max(max_len, i - lefts.top());
			}
		}
	}
	return max_len;
}


//DP for LVP

int longestValidParenthese(string& s)
{
	vector<int> f(s.size(), 0);
	int ret = 0;
	for (int i = s.size() - 2; i > 0; i--)
	{
		int match = i + f[i + 1] + 1;
		if (s[i] == '(' && match < s.size() && s[match] == ')')
		{
			f[i] = f[i + 1] + 2;
			if (match < s.size()) f[i] += f[match + 1];
		}
		ret = max(ret, f[i]);
	}
	return ret;
}