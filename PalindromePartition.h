#include <string>
#include <vector>

#define  N 1000
using namespace std;

//����
//ÿһ���������ж��м����Ƿ�Ϊ�Ϸ�������û��ݷ���
//һ������Ϊn���ַ�������n-1���ط����Կ��ϣ�ÿ���ط��ɶϿɲ��ϣ���˸��Ӷ�ΪO(2^n -1);

bool isPalindrome(const string& s, int start, int end)
{
	while (start < end && s[start] == s[end])
	{
		++start; --end;
	}
	return start >= end;
}

//dfs1
void dfs(string& s, vector<string>& path, vector<vector<string>>& result, size_t prev, size_t start)
{
	if (start == s.size())
	{
		if (isPalindrome(s, prev, start -1))
		{
			path.push_back(s.substr(prev, start - prev));
			result.push_back(path);
			path.pop_back();
		}
		return;
	}
	//���Ͽ�
	dfs(s, path, result, prev, start + 1);
	//���[prev�� start -1]�ǻ��ģ�����ԶϿ���Ҳ���Բ��Ͽ�����һ��δ�Ͽ�����
	if (isPalindrome(s, prev, start -1))
	{
		//�Ͽ�
		path.push_back(s.substr(prev, start - prev));
		dfs(s, path, result, start, start + 1);
		path.pop_back();
	}
}

vector<vector<string>> palinrdomePartition(string s)
{
	vector<vector<string>> result;
	vector<string> path;
	dfs(s, path, result, 0, 1);
	return result;
}

//DP

vector<vector<string>> palinrdomePartitionII(string s)
{
	const int n = s.size();
	bool p[n][n];
	fill_n(&p[0][0], n*n, false);
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i; j < n; ++j)
			p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);
	}
	vector<vector<string>> sub_plains[n]; //sub palindromes of s[0, i];
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = i; j < i; ++j)
		{
			if (p[i][j])
			{
				const string palindrome = s.substr(i, j - i + 1);
				if (j+1 <n)
				{
					for (auto v : sub_plains[j+1])
					{
						v.insert(v.begin(), palindrome);
						sub_plains[i].push_back(v);
					}
				}
				else
				{
					sub_plains[i].push_back(vector<string> {palindrome});
				}
			}
		}
	}
	return sub_plains[0];
}