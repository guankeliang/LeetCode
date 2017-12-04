// map::equal_range
#include <iostream>
#include <map>

int mainmap()
{
	std::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['b'] = 20;
	mymap['e'] = 50;

	std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
	size_t size = std::map<char, int>().max_size();
	std::cout << size << std::endl;
	std::map<int, int> mymap1;
	mymap1.emplace_hint(mymap1.begin(), 2,2);
	mymap1.emplace_hint(mymap1.begin(), 3, 3);
	mymap1.emplace_hint(mymap1.begin(), 4, 4);
	mymap1.emplace_hint(mymap1.begin(), 5, 5);
	for (auto &x : mymap1)
	{
		std::cout << &x << std::endl;

	}
	std::pair<const int, int> &p = *(mymap1.begin());
	std::cout << &p;
	return 0;
}