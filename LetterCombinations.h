#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const vector<string> keyboard{ "", "", "abc", "def", "ghi", "ljk", "mno", "pqrs", "tuv", "wxyz" };

vector<string> letterCombinations(const string& digits)
{
	if (digits.empty()) return vector<string>();
	vector<string> result(1, "");
	for (auto d: digits)
	{
		const size_t n = result.size();
		const size_t m = keyboard[d - '0'].size();
		result.resize(n*m);
		for (int i = 0; i < m; i++)
		{
			copy(result.begin(), result.begin() + n, result.begin() + n*i);
		}

		for (int i = 0; i < m; i++)
		{
			auto begin = result.begin();
			for_each(result.begin() + n*i, result.begin() + n*(i + 1), 
						[&](string& s){s += keyboard[d - '0'][i]; });
		}
	}
}