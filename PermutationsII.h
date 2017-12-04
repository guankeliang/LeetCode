#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

size_t n;
typedef vector<pair<int, int>>::const_iterator Iter;

void permute(Iter first, Iter last, vector<int>& p, vector<vector<int>>& result)
{
	if (n == p.size()) // ��������
	{
		result.push_back(p);
	}
	for (auto i = first; i != last; ++i)
	{
		int count = 0; //ͳ��*i��p�г��ֶ��ٴ�
		for (auto j = p.begin(); j != p.end(); j++)
		{
			if (i->first == *j)
			{
				count++;
			}
		}
		if (count < i->second)
		{
			p.push_back(i->first);
			permute(first, last, p, result);
			p.pop_back();//����������������һ��
		}
	}
}


vector<vector<int>> permuteUnique(vector<int>& num)
{
	sort(num.begin(), num.end());

	unordered_map<int, int> count_map;
	for_each(num.begin(), num.end(), [&count_map](int e)
	{if (count_map.find(e) != count_map.end())
		count_map[e]++;
	else
		count_map[e] = 1;
	});

	n = num.size();
	vector<vector<int>> result;
	vector<int> p;
	vector<pair<int, int>> elems;
	for_each(count_map.begin(), count_map.end(), [&elems](const pair<int, int> &e){elems.push_back(e); });
	permute(elems.begin(), elems.end(), p, result);
	return result;
}

