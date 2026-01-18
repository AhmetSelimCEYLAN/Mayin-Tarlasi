#ifndef _MAYIN_TARLASI__H_
#define _MAYIN_TARLASI__H_

#include <iostream>
#include <vector>
using namespace std;

class Cell
{
	public:
		Cell();
		bool isMine;
		bool isFlag;
		bool isOpen;
		int adj;
};


class Game
{
	public:
		Game(int w,int l,int m);
		void minePlacer(int index);
		void print_terminal();
		void flag(int index);
		void bomb(int index);
		int get_wid() {return wid;}
		int get_len() {return len;}
		int get_num() {return mine_num;}
		bool get_safe() {return isSafe;}
		void computeAdj();
	private:
		bool isSafe;
		int wid;
		int len;
		int mine_num;
		vector<Cell> board;
};

void terminal();

#endif
