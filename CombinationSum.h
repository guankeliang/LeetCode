#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<int>& nums, vector<int>& path, vector<vector<int>> &result, int gap, int start)
{
	if (gap == 0)
	{
		result.push_back(path);
		return;
	}
	for (size_t i = start; i < nums.size(); i++)
	{
		if (gap < nums[i]) return;

		path.push_back(nums[i]); //extend
		dfs(nums, path, result, gap - nums[i], i);
		path.pop_back();//back
	}
}

vector<vector<int>> combinationSum(vector<int>& nums, int target)
{
	sort(nums.begin(), nums.end());
	vector<vector<int>> result;
	vector<int> path;
	dfs(nums, path, result, target, 0);
	return result;
}