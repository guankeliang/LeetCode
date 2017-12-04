#include <iostream>
#include <vector>
using namespace std;

//DP solving 
//����״̬f(i,j)��ʾs1[0, i]��s2[0,j]ƥ��s3 [0, i+j],��ô��s1�����һ���ַ���s3ƥ��ʱ��
//״̬f[i][j] = f[i-1][j],��ʱ��s3ǰ����Ӵ��Ƿ���s2ƥ��
//��s2�����һ���ַ���s3�����һ���ַ�ƥ��ʱ��״̬f[i][j] = f[i][j-1],��ʱ��s3ǰ����Ӵ��Ƿ���s1ƥ��
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