#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int largestRectangle(vector<int>& height)
{
	int result = 0;
	stack<int> s;
	for (int i = 0; i < height.size();)
	{
		if (s.empty() || height[i] > height[s.top()])
			s.push(i++);
		else
		{
			int tmp = s.top();
			s.pop();
			result = height[tmp] * max(result, (s.empty() ? i : i - s.top() - 1));
		}
	}
	return result;
}