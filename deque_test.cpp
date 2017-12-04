#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int maindeq()
{
	vector<int> a;
	deque<int> d;
	for (int i = 0; i < 1e10; i++)
	{
		a.push_back(i + i*i);
	}
	sort(a.begin(), a.end());
	d.push_front(*prev(a.end()));
	a.pop_back();
	for (auto it = a.begin(); it != a.end(); it += 2)
	{
		if (it == prev(a.end()))
		{
			d.push_back(*it);
			break;
		}
		d.push_front(*it);
		d.push_back(*(it+1));
		
	}
	long sum = 0;
	for (int i = 0; i < d.size() - 1; ++i)
	{
		sum += abs(d[i] - d[i + 1]);
	}
	cout << sum << endl;
	system("pause");
	return 0;
}