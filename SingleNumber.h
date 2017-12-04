#include <vector>

using namespace std;

int singleNumber(vector<int>& nums)
{
	int x = 0;
	for (auto i : nums)
	{
		x ^= i;
	}
	return x;
}

int singleNumberII(vector<int> &nums)
{
	int one = 0, two = 0, three = 0;
	for (auto i : nums)
	{
		two |= (one & i);
		one ^= i;
		three = ~(one & two);
		one &= three;
		two &= three;
	}
	return one;
}
