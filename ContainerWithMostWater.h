#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int containerWithmostWater(vector<int>& height)
{
	int start = 0;
	int end = height.size() - 1;
	int result = 0;
	while (start < end)
	{
		int area = min(height[start], height[end])*(end - start);
		result = max(area, result);
		if (height[start] <= height[end])
		{
			start++;
		}
		else
		{
			end--;
		}
	}
	return result;
}