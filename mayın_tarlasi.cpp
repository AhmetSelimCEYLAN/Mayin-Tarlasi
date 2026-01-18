#include <iostream>
#include "mayýn_tarlasý.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#define MAXWL 50



Cell::Cell()
{
	isMine=false;
	isFlag=false;
	isOpen=false;
	adj=0;
}


Game::Game(int w,int l, int m)
{
	wid=(w<=MAXWL) ? w : MAXWL;
	len=(l<=MAXWL) ? l : MAXWL;
	board.resize(wid * len);
	int maxMine = wid * len - 9; 
    mine_num = (m <= maxMine) ? m : maxMine;
    srand(time(NULL));
    isSafe=true;
}

void Game::flag(int index)
{
	board[index].isFlag=true;
}
#include <queue>

void Game::bomb(int index)
{
    if (index < 0 || index >= (int)board.size()) return;
    if (!isSafe) return;                 // oyun bitmiþse dokunma (opsiyonel)

    if (board[index].isFlag) return;     // flag varsa acma
    if (board[index].isOpen) return;     // zaten aciksa

    // Mayinsa: kaybettin
    if (board[index].isMine)
    {
        board[index].isOpen = true;      // istersen mayini da ac
        isSafe = false;
        return;
    }

    // Mayin degilse ac
    board[index].isOpen = true;

    // adj > 0 ise sadece bunu acip cik
    if (board[index].adj > 0) return;

    // adj == 0 ise flood-fill (BFS)
    std::queue<int> q;
    q.push(index);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        int r = cur / len;
        int c = cur % len;

        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                if (dr == 0 && dc == 0) continue;

                int nr = r + dr;
                int nc = c + dc;

                if (nr < 0 || nr >= wid || nc < 0 || nc >= len) continue;

                int ni = nr * len + nc;

                if (board[ni].isOpen) continue;
                if (board[ni].isFlag) continue;   // bayrakliysa elleme
                if (board[ni].isMine) continue;   // garanti olsun

                board[ni].isOpen = true;

                // komsu da bos ise yayilmaya devam
                if (board[ni].adj == 0)
                    q.push(ni);
            }
        }
    }
}

void Game::minePlacer(int index)
{
    std::vector<int> harita;
    for (int i = 0; i < board.size(); i++)
    {
        if (i == index) continue;

        if (index % len == 0)
        {
            if (i == index - len) continue;
            if (i == index - len + 1) continue;
            if (i == index + len) continue;
            if (i == index + len + 1) continue;
            if (i == index + 1) continue;
        }
        else if (index % len == len - 1)
        {
            if (i == index - len) continue;
            if (i == index - len - 1) continue;
            if (i == index + len) continue;
            if (i == index + len - 1) continue;
            if (i == index - 1) continue;
        }
        else
        {
            if (i == index - len) continue;
            if (i == index - len + 1) continue;
            if (i == index + len) continue;
            if (i == index + len + 1) continue;
            if (i == index + 1) continue;
            if (i == index - len - 1) continue;
            if (i == index + len - 1) continue;
            if (i == index - 1) continue;
        }

        harita.push_back(i);
    }
    std::random_shuffle(harita.begin(), harita.end());
    for(int i=0; i<mine_num; i++)
    {
    	board[harita[i]].isMine=true;	
	}
}

void Game::computeAdj()
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i].isMine)
        {
            board[i].adj = -1;
            continue;
        }

        int count = 0;
        int row = i / len;
        int col = i % len;

        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                if (dr == 0 && dc == 0) continue;

                int nr = row + dr;
                int nc = col + dc;

                if (nr < 0 || nr >= wid || nc < 0 || nc >= len)
                    continue;

                int ni = nr * len + nc;
                if (board[ni].isMine)
                    count++;
            }
        }

        board[i].adj = count;
    }
}


void Game::print_terminal()//No problemo
{
	for (int i=0; i<4; i++)	{std::cout << " ";} //4 boþluk koydum ve baþlýyorum.
	for (int i=0; i<len; i++) {std::cout << i << " ";}
	std::cout << std::endl;
	for (int i=0; i<2; i++)	{std::cout << " ";}
	for (int i=0; i<2; i++)	{std::cout << "-";}
	for (int i=0; i<len; i++) {std::cout <<"--";}
	std::cout << std::endl;
	for (int i=0; i<wid; i++)
	{
		std::cout << i << "   ";
		for(int j=0; j<len; j++)
		{
			if(board[(i)*len+j].isOpen)
			{
				if(board[(i)*len+j].adj==-1)
				{
					std::cout << "* ";
				}
				else
				{
					std::cout << board[(i)*len+j].adj << " ";
				}
			}
			else if (board[(i)*len+j].isFlag)
				{
					std::cout << "! ";
				}
			else
			{
				std::cout << "# ";
			}
		}
		std::cout << std::endl;
	}
}

void terminal()
{
    int w, l, num;
	int ind1,ind2;
    std::cout << std::endl
        << "Mayýn tarlasý oyunuma hos geldiniz." << std::endl
        << "Oyunu terminalden oynayacaksiniz." << std::endl
        << "Oyuna baslamadan once size oyunu nasil oynayacaginizi anlatacagim." << std::endl
        << "Ilk olarak oyunu hangi en ve boyda oynamak istediginizi," << std::endl
        << "daha sonra kac mayinla oynamak istediginizi soracagim." << std::endl
        << "Tahta max 50x50, mayin sayisi max alan-9 olabilir." << std::endl
        << "Sistem kontrolu kendisi yapar." << std::endl;

    std::cout << "En: ";
    std::cin >> w;

    std::cout << "Boy: ";
    std::cin >> l;

    std::cout << "Mayin sayisi: ";
    std::cin >> num;

    Game yeni(w, l, num);
    
    std::cout << "Þimdi oyunu nasýl oynayacaðýný anlatacaðým." << std::endl
    	<< "Ýlk olarak bu oyunu analitil düzlemde oynayacaðýz." << std::endl
    	<< "Yani bir noktayý o noktanýn koordinatlarýný yazarak eriþebilirsin." <<std::endl
    	<< "\"F\" ile bayrak yerleþtirebilirsin." << std::endl
    	<< "\"B\" ile o noktayý patlatabilirsin." << std::endl
    	<< "Artýk oynamaya hazýrsýn. Let's Go!" << std::endl;
    yeni.print_terminal();
    std::cout << "Patlamaya baþlayalým! Hadi ilk noktayý gir (Sol index ilk, Sonra sað index): ";
    std::cin >> ind1 >> ind2; //Bunlar ilk olduðu için gerekli kalaný while true ile yaparýz.
    yeni.minePlacer(ind1*yeni.get_wid()+ind2);
    yeni.computeAdj();
    yeni.bomb(ind1*yeni.get_wid()+ind2);
    yeni.print_terminal();
    while(true)
    {
    	char mak;
    	int in1,in2;
    	std::cout << std::endl << "Þimdi yapacaðýn iþlemin ilk harfi (Flag or Bomb) ve ayný indexleme sýrasýyla: ";
    	std::cin >> mak >> in1 >> in2;
    	if(mak=='b' or mak=='B')
    	{
    		yeni.bomb(in1*yeni.get_wid()+in2);
		}
		else if(mak=='F' or mak=='f')
		{
			yeni.flag(in1*yeni.get_wid()+in2);
		}
		else{continue;}
		yeni.print_terminal();
		if(!yeni.get_safe())
		{
			std::cout << endl << "Kaybettin Canim.";
			break;
		}
	}
    
}
int main()
{
	terminal();
	return 0;
}
