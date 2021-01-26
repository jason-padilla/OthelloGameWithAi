#include <ics46/factory/DynamicFactory.hpp>
#include "MyAi.hpp"
#include "OthelloCell.hpp"
#include "OthelloGameState.hpp"

using namespace std;

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,jpadill3::MyAi,"JasonPadilla AI(Required)");
pair<int,int> jpadill3::MyAi::chooseMove(const OthelloGameState& state)
{
	unique_ptr<OthelloGameState> uniqptr_of_copystate = state.clone();
	vector<pair<int,int>> vector_of_moves;
	pair<int,int> pair_of_best_move;
	
	if(state.isBlackTurn())
		my_color_is = "black";
	
	else
		my_color_is = "white";
		
	pair<int,int> pass_pair;
	pass_pair.first = 0;
	pass_pair.second = 0;

	vector<pair<int,int>> int_of_returned_score = search(*uniqptr_of_copystate,1,pass_pair);

	return int_of_returned_score.at(1);
}

vector<pair<int,int>> jpadill3::MyAi::MakeVectorOfPossibleMoves(OthelloGameState& game_state)
{
	
	vector<pair<int,int>> possible_moves;

	for (int x = 0; x < game_state.board().width(); x++)
		for (int y = 0; y < game_state.board().height(); y++)
			if (game_state.isValidMove(x,y))
				possible_moves.push_back(pair<int,int> (x,y));

	return possible_moves;
}

vector<pair<int,int>> jpadill3::MyAi::search(OthelloGameState& s, int depth, pair<int,int> passed)
{

	if(s.isGameOver())
	{
		return EvaluateTheBestMove(s,passed);
	}

	vector<pair<int,int>> vector_of_moves;
	vector_of_moves = MakeVectorOfPossibleMoves(s);

	
	if (depth == 0)
	{
		return EvaluateTheBestMove(s,passed);
	}
	
	else
	{
		if((s.isBlackTurn() and my_color_is == "black") or  (s.isWhiteTurn() and my_color_is == "white"))
		{

			vector<pair<int,int>> product;
			pair<int,int> pass_pair;
			product.push_back(pair<int,int>(0,0));
			product.push_back(pair<int,int>(0,0));
			int score = -50;
			
			for(int move_index = 0; move_index < vector_of_moves.size(); move_index++)
			{
				unique_ptr<OthelloGameState> uniqptr_of_copystate2 = s.clone();
				uniqptr_of_copystate2->makeMove(vector_of_moves.at(move_index).first,vector_of_moves.at(move_index).second);
				
				pass_pair.first =  vector_of_moves.at(move_index).first;
				pass_pair.second =  vector_of_moves.at(move_index).second;
				
				vector<pair<int,int>> current_result = search(*uniqptr_of_copystate2,depth - 1,pass_pair);

				if( current_result.at(0).first > score)
				{
					score = current_result.at(0).first;
					product.at(0).first = score;
					product.at(1) = pass_pair;
					
				}
			}
			
			return product;
		
		}
		else
		{
			vector<pair<int,int>> product;
			pair<int,int> pass_pair;
			product.push_back(pair<int,int>(0,0));
			product.push_back(pair<int,int>(0,0));
			int score = -1;
			
			for(int move_index = 0; move_index < vector_of_moves.size(); move_index++)
			{
				unique_ptr<OthelloGameState> uniqptr_of_copystate2 = s.clone();
				uniqptr_of_copystate2->makeMove(vector_of_moves.at(move_index).first,vector_of_moves.at(move_index).second);
				
				pass_pair.first =  vector_of_moves.at(move_index).first;
				pass_pair.second =  vector_of_moves.at(move_index).second;
				
				vector<pair<int,int>> current_result = search(*uniqptr_of_copystate2,depth - 1,pass_pair);

				if( current_result.at(0).first <= score)
				{
					score = current_result.at(0).first;
					product.at(0).first = score;
					product.at(1) = pass_pair;
				}
			}
			return product;
		}
	}
}

vector<pair<int,int>> jpadill3::MyAi::EvaluateTheBestMove(OthelloGameState& state, pair<int,int> passed_possible_moves)
{	
	vector<pair<int,int>> send;
	
	send.push_back(pair<int,int> (array_of_weights[passed_possible_moves.first][passed_possible_moves.second],0));
	
	return send;
}
