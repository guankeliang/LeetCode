#include <iostream>
#include <vector>
using namespace std;

//DP solving 
//假设状态f(i,j)表示s1[0, i]和s2[0,j]匹配s3 [0, i+j],那么当s1的最后一个字符与s3匹配时，
//状态f[i][j] = f[i-1][j],这时看s3前面的子串是否与s2匹配
//当s2的最后一个字符与s3的最后一个字符匹配时，状态f[i][j] = f[i][j-1],这时看s3前面的子串是否与s1匹配
bool interLeavingString(const string& s1, const string& s2, const string& s3)
{
	if (s3.length() != s1.length() + s2.length())
	{
		return false;
	}
	vector<vector<bool>> f(s1.length() + 1, vector<bool>(s2.length() + 1, true));

	for (size_t i = 1; i < s1.length() + 1; i++)
	{
		f[i][0] = f[i - 1][0] && s1[i - 1] == s3[i - 1];
	}
	for (size_t i = 1; i < s2.length() + 1; i++)
	{
		f[0][i] = f[0][i - 1] && s2[i - 1] == s3[i - 1];
	}

	for (size_t i = 1; i < s1.length() + 1; i++)
	{
		for (int j = 1; j < s2.length() + 1; j++)
		{
			f[i][j] = (s1[i - 1] == s3[i + j - 1] && f[i - 1][j]) ||
				(s2[j - 1] == s3[i + j - 1] && f[i][j - 1]);
		}
	}
	return f[s1.length()][s2.length()];
}