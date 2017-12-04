#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target)
{
	unordered_map<int, int> mapping;
	vector<int> result;
	int size = nums.size();
	for (int i = 0; i < size; i++)
		mapping[nums[i]] = i;
	for (int i = 0; i < size; i++)
	{
		int gap = target - nums[i];
		if (mapping.find(gap) != mapping.end() && mapping[gap] > i)
		{
			result.push_back(i + 1);
			result.push_back(mapping[gap] + 1);
		}
	}
	return result;
}