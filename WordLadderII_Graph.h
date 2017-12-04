//图的广度搜索
//本题可以看成是图上的广度搜索。 给定了字典dict, 可以基于它画出一个无向图，表示单词之间可以相互转换。 
//本题的本质就是已知起点和终点，在图上找出最短路径。

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

struct _state_t
{
	_state_t* father;
	string word;
	int level;

	_state_t(_state_t* father, const string& word, int level) :
		father(father), word(word), level(level){}
};

_state_t* create_state(_state_t* parent, const string& value, int length, vector<_state_t*>& pool)
{
	_state_t* node = new _state_t(parent, value, length);
	pool.push_back(node);

	return node;
}

vector<string> gen_path(const _state_t* node)
{
	vector<string> path;
	while (node != nullptr)
	{
		path.push_back(node->word);
		node = node->father;
	}

	reverse(path.begin(), path.end());
	return path;
}

unordered_map<string, unordered_set<string>> build_graph(const unordered_set<string>& dict)
{
	unordered_map<string, unordered_set<string>> adjacency_list;

	for (const auto& word : dict)
	{
		for (size_t i = 0; i < word.size(); i++)
		{
			string new_word(word);
			for (char c = 'a'; c <= 'z'; c++)
			{
				if (c == new_word[i]) continue;
				swap(c, new_word[i]);

				if ((dict.find(new_word) != dict.end()))
				{
					auto iter = adjacency_list.find(word);
					if (iter != adjacency_list.end())
					{
						iter->second.insert(new_word);
					}
					else
					{
						adjacency_list.insert(pair<string, unordered_set<string>>(word, unordered_set<string>()));
						adjacency_list[word].insert(new_word);
					}
				}
				swap(c, new_word[i]); //恢复该单词
			}
		}
	}
	return adjacency_list;
}

vector<vector<string>> findLaddersII(const string& start, const string& end, const unordered_set<string>& dict)
{
	const auto& g = build_graph(dict);
	vector<_state_t*> pool;
	queue<_state_t*> q; //未处理的点
	//value 是所在层次
	unordered_map<string, int> visited;
	auto state_is_target = [&](const _state_t* s) {
		return s->word == end;
	};
	vector<vector<string>> result;
	q.push(create_state(nullptr, start, 0, pool));
	while (!q.empty())
	{
		_state_t* state = q.front();
		q.pop();

		//如果当前路径长度已经超过当前最短路径长度，
		//可以终止对该路径的处理，所求为最短路径
		if (!result.empty() && state->level + 1 > result[0].size()) break;

		if (state_is_target(state))
		{
			const auto& path = gen_path(state);
			if (result.empty())
			{
				result.push_back(path);
			}
			else
			{
				if (path.size() < result[0].size())
				{
					result.clear();
					result.push_back(path);
				}
				else if (path.size() == result[0].size())
				{
					result.push_back(path);
				}
				else
				{
					throw std::logic_error("not possible to get here");
				}
			}
			continue;
		}
		visited[state->word] = state->level;

		//扩展节点
		auto iter = g.find(state->word);
		if (iter == g.end()) continue;

		for (const auto& neighbor : iter->second)
		{
			auto visited_iter = visited.find(neighbor);

			if (visited_iter != visited.end() &&
				visited_iter->second < state->level + 1) continue;

			q.push(create_state(state, neighbor, state->level + 1, pool));
		}
	}

	//release all states
	for (auto state : pool)
	{
		delete state;
	}
	return result;
}