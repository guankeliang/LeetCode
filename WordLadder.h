#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

struct state_t{
	string word;
	int level;

	state_t() { word = " "; level = 0; }
	state_t(const string& word, int level){
		this->word = word;
		this->level = level;
	}

	bool operator==(const state_t& other){
		return this->word == other.word;
	}
};

namespace std{
	template<> struct hash<state_t>{
	public:
		size_t operator()(const state_t& s) { return str_hash(s.word); }
	private:
		std::hash<std::string> str_hash;
	};
}

//single queue

int ladderLength(const string& start, const string& end, const unordered_set<string> &dict)
{
	queue<state_t> q;
	unordered_set<state_t> visited;

	auto state_is_valid = [&](const state_t& s) {
		return dict.find(s.word) != dict.end() || s.word == end;
	};
	auto state_is_target = [&](const state_t& s) {return s.word == end; };
	auto state_extend = [&](const state_t& s){
		unordered_set<state_t> result;

		for (size_t i = 0; i < s.word.size(); ++i)
		{
			state_t new_state(s.word, s.level + 1);
			for (char c = 'a'; c <= 'z'; c++)
			{
				//in case ladder instead
				if (c == new_state.word[i]) continue;
				
				swap(c, new_state.word[i]);
				if (state_is_valid(new_state) && visited.find(new_state) == visited.end())
				{
					result.insert(new_state);
				}
				swap(c, new_state.word[i]); //recover the word
			}
		}
		return result;
	};
	
	state_t start_state(start, 0);
	q.push(start_state);
	visited.insert(start_state);
	while (!q.empty())
	{
		//not use const auto&, it will delete element when used pop()
		//the & will be decrypted
		const auto state = q.front();
		q.pop();

		if (state_is_target(state)) return state.level + 1;

		const auto& new_states = state_extend(state);
		for (const auto& new_state : new_states)
		{
			q.push(new_state);
			visited.insert(new_state);
		}
	}
	return 0;
} 


//double queue

int ladderLengthII(const string& start, const string& end, const unordered_set<string> &dict)
{
	queue<string> current, next;
	unordered_set<string> visited;

	int level = -1;

	auto statae_is_valid = [&](const string& s) {
		return dict.find(s) != dict.end() || s == end; };
	auto statae_is_target = [&](const string& s) {return s == end; };
	auto state_extend = [&](const string& s){
		unordered_set<string> result;

		for (size_t i = 0; i < s.size(); ++i)
		{
			string new_word(s);
			for (char c = 'a'; c <= 'z'; c++)
			{
				//in case ladder instead
				if (c == new_word[i]) continue;

				swap(c, new_word[i]);
				if (statae_is_valid(new_word) && visited.find(new_word) == visited.end())
				{
					result.insert(new_word);
				}
				swap(c, new_word[i]); //recover the word
			}
		}
		return result;
	};

	current.push(start);
	visited.insert(start);

	while (!current.empty())
	{
		const auto state = current.front();
		current.pop();
		if (statae_is_target(state))
		{
			return level + 1;
		}
		const auto& new_states = state_extend(state);
		for (const auto& new_state : new_states)
		{
			next.push(new_state);
			visited.insert(new_state);
		}
		swap(next, current);
	}
	return 0;
}