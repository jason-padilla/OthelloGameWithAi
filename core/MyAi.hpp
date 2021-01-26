#ifndef MY_AI
#define MY_AI
#include "OthelloAI.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


namespace jpadill3
{
	class MyAi:public OthelloAI
	{
	public:
		virtual pair<int,int> chooseMove(const OthelloGameState& state);
		vector <pair<int,int>> MakeVectorOfPossibleMoves(OthelloGameState& game_state);
		vector <pair<int,int>> search(OthelloGameState& s, int depth, pair<int,int> passsed);
		vector<pair<int,int>> EvaluateTheBestMove(OthelloGameState& state, pair<int,int> passed_possible_moves);
	private:
		string my_color_is;
		int array_of_weights[8][8] =
			{
				{50,-1,10,2,2,10,-1,50},
				{-1,-25,1,1,1,1,-25,-1},
				{10,1,1,1,1,1,1,10},
				{2,1,1,0,0,1,1,2},
				{2,1,1,0,0,1,1,2},
				{10,1,1,1,1,1,1,10},
				{-1,-25,1,1,1,1,-25,-1},
				{50,-1,10,2,2,10,-1,50}
			};
	};
}


#endif