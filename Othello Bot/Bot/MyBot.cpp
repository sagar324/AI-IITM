/*
* @file botTemplate.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Template for users to create their own bots
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;
using namespace Desdemona;

#define MAXDEPTH 6
Turn MyTurn;
Coin MyCoin;

auto start = high_resolution_clock::now(); 
auto stop = high_resolution_clock::now();

double MIN = (double)INT_MIN;
double MAX = (double)INT_MAX;

vector<vector <double> > weights =       
{{139, -24.7, 24.7, 5.94, 5.94, 24.7, -24.7, 139},
{-24.7, -49.4, -5.94, -5.94, -5.94, -5.94, -49.4, -24.7},
{24.7, -5.94, 19.7, 3.94, 3.94, 19.7, -5.94, 24.7},
{5.94, -5.94, 3.94, 3.94, 3.94, 3.94, -5.94, 5.94},
{5.94, -5.94, 3.94, 3.94, 3.94, 3.94, -5.94, 5.94},
{24.7, -5.94, 19.7, 3.94, 3.94, 19.7, -5.94, 24.7},
{-24.7, -49.4, -5.94, -5.94, -5.94, -5.94, -49.4, -24.7},
{139, -24.7, 24.7, 5.94, 5.94, 24.7, -24.7, 139}};


double CalcWeight(OthelloBoard b){
    double value = 0;
    for(int ii = 0; ii < 8;ii++){
      for(int jj = 0; jj < 8;jj++){
        if(b.get(ii,jj) == BLACK){
            value += weights[ii][jj];
        }   
        else if(b.get(ii,jj)  == RED){
            value -= weights[ii][jj];
        }
      }
    }
    return value;
}


double eval_final(OthelloBoard board){
    if(MyTurn == BLACK){

        int b = board.getBlackCount();
        int r = board.getRedCount();

        if(b>r){
            return MAX;
        }
        else if(b<r){
            return MIN;
        }
        return 0;
    }
    else{
        int b = board.getBlackCount();
        int r = board.getRedCount();

        if(b>r){
            return MIN;
        }
        else if(b<r){
            return MAX;
        }
        return 0;
    }
}

double eval_pos(OthelloBoard board){
    double weight_check = CalcWeight(board);
    double score =   100.0*(weight_check) ;
    if(MyTurn == BLACK){
        return score;
    }
    else{
        return -score;
    }
}

double Alpha_Beta(OthelloBoard b,Turn turn,int depth,double alpha,double beta){
    if(depth >= MAXDEPTH){
        return eval_pos(b);
    }
    list <Move> moves = b.getValidMoves(turn);
    stop = high_resolution_clock::now(); 
    if(turn == MyTurn){
        auto duration = duration_cast<microseconds>(stop - start);
        if(duration.count()>1900000){
            return MIN;
        }

        if(moves.size()==0){
            //handle special case;
            Turn next_turn = other(turn);
            list <Move> moves = b.getValidMoves(next_turn);
            if(moves.size()==0){
                //either win/loss/draw;
                return eval_final(b);
            }

            for(auto m : moves){
                OthelloBoard new_board = b;
                new_board.makeMove(next_turn,m);
                beta = min(beta,Alpha_Beta(new_board,turn,depth+1,alpha,beta));
                if(alpha>=beta){
                    return alpha;
                }
            }
            return beta;
        }

        for(auto m : moves){
            OthelloBoard new_board = b;
            new_board.makeMove(turn,m);
            alpha = max(alpha,Alpha_Beta(new_board,other(turn),depth+1,alpha,beta));
            if(alpha>=beta){
                return beta;
            }
        }
        return alpha;
    }   
    else{
        auto duration = duration_cast<microseconds>(stop - start);
        if(duration.count()>1900000){
            return MAX;
        }

        if(moves.size() == 0){
            //handle special case;
            Turn next_turn = other(turn);
            moves = b.getValidMoves(next_turn);
            if(moves.size()==0){
                //win/loss/draw
                return eval_final(b);
            }

            for(auto m : moves){
                OthelloBoard new_board = b;
                new_board.makeMove(next_turn,m);
                alpha = max(alpha,Alpha_Beta(new_board,turn,depth+1,alpha,beta));
                if(alpha>=beta){
                    return beta;
                }
            }
            return alpha;
        }

        for(auto m : moves){
            OthelloBoard new_board = b;
            new_board.makeMove(turn,m);
            beta = min(beta,Alpha_Beta(new_board,other(turn),depth+1,alpha,beta));
            if(alpha>=beta){
                return alpha;
            }
        }
        return beta;
    }
}


class MyBot: public OthelloPlayer
{
    public:
        /**
         * Initialisation routines here
         * This could do anything from open up a cache of "best moves" to
         * spawning a background processing thread. 
         */

        MyBot( Turn turn );

        /**
         * Play something 
         */
        virtual Move play( const OthelloBoard& board );
    private:
};

MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{

}

Move MyBot::play( const OthelloBoard& board )
{   
    start = high_resolution_clock::now(); 

    list<Move> moves = board.getValidMoves( turn );
    Move ans = *(moves.begin());   
    if(moves.size()==0){
        return Move::pass();
    } 
    if(moves.size()<2){
        return ans;
    }
    MyTurn = turn;
    if(MyTurn == BLACK){
        MyCoin = BLACK;
    }
    else{
        MyCoin = RED;
    }
    double val = MIN;
    for(auto m:moves){
        OthelloBoard new_board = board;
        new_board.makeMove(turn,m);
        double check = Alpha_Beta(new_board,other(turn),1,val, MAX);
        if(val<check){
            val = check;
            ans = m;
        }
    }
    stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    return ans;
}

// The following lines are very important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}