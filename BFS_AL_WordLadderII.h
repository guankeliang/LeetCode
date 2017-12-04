#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution {
public:
	~Solution()
	{
		for (auto iter = pool_.begin(); iter != pool_.end(); ++iter)
		{
			delete *iter;
		}
	}

	std::vector<std::vector<std::string> > findLadders(std::string start, std::string end, std::unordered_set<std::string> &dict)
	{
		nextPoolPos_ = 0;
		std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyList;
		std::string word;

		for (auto iter = dict.begin(); iter != dict.end(); ++iter)
		{
			word = *iter;
			BuildAdjacencyList(word, adjacencyList, dict);
		}

		std::vector<std::vector<std::string>> result;
		std::queue<PathTag*> candidate;
		std::unordered_map<std::string, int> usedWord;

		std::string currentString;
		bool foundShortest = false;
		size_t shortest = 0;

		candidate.push(AllocatePathTag(nullptr, start, 1));

		while (!candidate.empty())
		{
			PathTag* current = candidate.front();

			if (foundShortest && current->length_ >= shortest)
			{
				break;
			}

			candidate.pop();

			auto adjacentIter = adjacencyList.find(current->value_);

			if (adjacentIter != adjacencyList.end())
			{
				for (auto iter = adjacentIter->second.begin(); iter != adjacentIter->second.end(); ++iter)
				{
					if (*iter == end)
					{
						GeneratePath(result, current, *iter);
						foundShortest = true;
						shortest = result.rbegin()->size();
						continue;
					}

					auto usedIter = usedWord.find(*iter);


					if (usedIter != usedWord.end() && usedIter->second != current->length_ + 1)
					{
						continue;
					}

					usedWord[*iter] = current->length_ + 1;

					candidate.push(AllocatePathTag(current, *iter, current->length_ + 1));
				}
			}
			else
			{
				continue;
			}

		}

		return result;
	}

private:
	struct PathTag
	{
		PathTag* parent_;
		std::string value_;
		int length_;

		PathTag(PathTag* parent, const std::string& value, int length) : parent_(parent), value_(value), length_(length)
		{
		}

	};

	PathTag* AllocatePathTag(PathTag* parent, const std::string& value, int length)
	{
		if (nextPoolPos_ >= pool_.size())
		{
			for (int i = 0; i < 100; ++i)
			{
				PathTag* newTag = new PathTag(nullptr, " ", 0);
				pool_.push_back(newTag);
			}
		}

		PathTag* toReturn = pool_[nextPoolPos_];
		toReturn->parent_ = parent;
		toReturn->value_ = value;
		toReturn->length_ = length;

		++nextPoolPos_;

		return toReturn;
	}

	int nextPoolPos_;

	std::vector<PathTag*> pool_;

	void GeneratePath(std::vector<std::vector<std::string>>& result, PathTag* pathTag, const std::string& end)
	{
		std::vector<std::string> path;

		path.push_back(end);

		while (pathTag != nullptr)
		{
			path.push_back(pathTag->value_);

			pathTag = pathTag->parent_;
		}

		size_t left = 0;
		size_t right = path.size() - 1;

		while (left < right)
		{
			std::swap(path[left], path[right]);

			++left;
			--right;
		}

		result.push_back(path);
	}

	//ÁÚ½ÓÁÐ±íBFS
	void BuildAdjacencyList(std::string& word, std::unordered_map<std::string, std::unordered_set<std::string>>& adjacencyList, const std::unordered_set<std::string>& dict)
	{
		std::string original = word;

		for (size_t pos = 0; pos < word.size(); ++pos)
		{
			char beforeChange = ' ';
			for (int i = 'a'; i <= 'z'; ++i)
			{
				beforeChange = word[pos];

				if (beforeChange == i)
				{
					continue;
				}

				word[pos] = i;

				if (dict.count(word) > 0)
				{
					auto iter = adjacencyList.find(original);
					if (iter != adjacencyList.end())
					{
						iter->second.insert(word);
					}
					else
					{
						adjacencyList.insert(std::pair<std::string, std::unordered_set<std::string>>(original, std::unordered_set<std::string>()));
						adjacencyList[original].insert(word);
					}
				}

				word[pos] = beforeChange;
			}
		}

	}
};
