#include <vector>
#include <string>
#include <stack>
using namespace std;


int evalRPN(vector<string>& tokens)
{
	int x, y;
	auto token = tokens.back();
	tokens.pop_back();
	if (is_operator(token))
	{
		y = evalRPN(tokens);
		x = evalRPN(tokens);
		if (token[0] == '+')
		{
			x += y;
		}
		else if (token[0] == '-') x -= y;
		else if (token[0] == '*') x *= y;
		else x /= y;
	}
	else
	{
		size_t i;
		x = stoi(token, &i);
	}
	return x;
}


int evalRPNII(vector<string>& tokens)
{
	stack<string> s;
	for (auto token : tokens)
	{
		if (!is_operator(token))
		{
			s.push(token);
		}
		else
		{
			int y = stoi(s.top());
			s.pop();
			int x = stoi(s.top());
			s.pop();
			if (token[0] == '+') x += y;
			else if (token[0] == '-') x -= y;
			else if (token[0] == '*') x *= y;
			else x /= y;
			s.push(to_string(x));
		}
		return stoi(s.top());
	}
	
}
bool is_operator(const string &op)
{
	return op.size() == 1 && string("+-*/").find(op) != op.npos;
}