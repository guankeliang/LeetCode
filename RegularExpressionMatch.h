#include <string>
#include <iostream>
using namespace std;

bool _isMatch(const char *s, const char *p)
{
	if (*p == '\0') return *s == '\0';
	cout << *(p + 1) << endl;
	if (*(p + 1) != '*')
	{
		if (*p == *s || (*p == '.' && *s != '\0'))
			return _isMatch(s + 1, p + 1);
		else
			return false;
	}
	else
	{
		while (*p == *s || (*p == '.' && *s != '\0'))
		{
			if (_isMatch(s, p + 2))
				return true;
			s++;
		}
		return _isMatch(s, p + 2);
	}
}


bool isMatch(const string& s, const string& p)
{
	return _isMatch(s.c_str(), p.c_str());
}


bool _isMatchII(const char *s, const char *p)
{
	bool star = false;
	const char *str, *ptr;
	for (str = s, ptr = p; *str != '\0'; str++, ptr++)
	{
		switch (*ptr)
		{
		case '?':
			break;
		case '*':
			star = true;
			s = str; p = ptr;
			while (*p == '*') p++;
			if (*p == '\0')
			{
				return true;
			}
			str = s - 1;
			ptr = p - 1;
			break;
		default:
			if (*str != *ptr)
			{
				if (!star) return false;
				s++;
				str = s - 1;
				ptr = p - 1;
			}
			break;
		}
	}
	while (*ptr == '*') ptr++;
	return (*ptr == '\0');
}

bool isMatchII(const string& s, const string& p)
{
	return _isMatchII(s.c_str(), p.c_str());
}

