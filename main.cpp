#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include "SurroundedRegions.h"
#include "NQueens.h"
using namespace std;


int main01()
{
	vector<vector<char>> board = { { 'X', 'X', 'X', 'X', 'X', }, { 'X', 'O', 'O', 'O', 'X' },
	{ 'X', 'O', 'O', 'O', 'X' }, { 'X', 'O', 'O', 'O', 'X' }, { 'X', 'X', 'X', 'X', 'X' } };
	solve(board);
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

int main02()
{
	int n = 4;
	init();
	queen();
	system("pause");
	return 0;
}