#include <string>

using namespace std;

string LongestPalindrome(const string& s)
{
	const int n = 1000;
	int max_len = 0;
	int start = 0;
	bool f[n][n] = {false};
	for (size_t i = 0; i < n; i++)
	{
		f[i][i] = true;
		for (int j = 0; j < i; j++)
		{
			f[j][i] = (s[j] == s[i] && (i - j < 2 || f[j + 1][i - 1]));
			if (f[j][i] && max_len < i- j +1)
			{
				max_len = i - j + 1;
				start = j;
			}
		}
	}
	return s.substr(start, max_len);
}