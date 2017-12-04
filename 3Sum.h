#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> ThreeSum(vector<int>& nums, const int target)
{
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	auto last = nums.end();
	for (auto i = nums.begin(); i < last -2; ++i)
	{
		auto j = i + 1;
		if (i > nums.begin() && *i == *(i-1)) continue;
		auto k = last - 1;
		while (j < k)
		{
			if ((*i + *j + *k) < target)
			{
				++j;
				while (*j == *(j - 1) && j < k) ++j;
			}
			else if ((*i + *j + *k) > target)
			{
				--k;
				while (*k == *(k + 1) && j < k) --k;
			}
			else
			{
				result.push_back({ *i, *j, *k });
				++j; --k;
				while (*j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
			}
		}
	}
	return result;
}