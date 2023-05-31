#include <iostream>
#include<conio.h>
#include<time.h>
#include <iomanip>

using namespace std;

#define cap 100
#define hum 0
#define comp 1



void init(char B[][cap], int& dim, int& nop, int& turn, char sym[cap], char playerName[][cap],int& winCond)
{
	cout << "Enter Dimensions :";
	cin >> dim;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			B[r][c] = '_';
		}
	}
	cout << "\n\nEnter Number of Players :";
	cin >> nop;
	for (int i = 0; i < nop; i++)
	{
		cout << "\n\nName of Player " << i + 1 << " : ";
		cin >> playerName[i];
		cout << "\n\nEnter Symbol of Player " << i + 1 << " : ";
		cin >> sym[i];
	}
	cout << "\n\nEnter your Win Condition : ";
	cin >> winCond;
	srand(time(NULL));
	turn = rand() % nop;
}

void boardPrint(char B[][cap], int dim)
{
	system("cls");
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout << B[r][c] << " ";
		}
		cout << endl;
	}
}

void turnMsg(char playerName[cap])
{
	cout << "\n\n" << playerName << " 's Turn : ";
}

void selectPos(int& pr, int& pc, int dim)
{
	cout << "\n\nEnter Row(1...." << dim << ") : ";
	cin >> pr;
	pr--;
	cout << "\n\nEnter column(1...." << dim << ") : ";
	cin >> pc;
	pc--;
}

bool isValid(char B[][cap], int dim, int pr, int pc)
{
	if (B[pr][pc] != '_')
	{
		return false;
	}
	if (pr<0 || pc<0 || pr>dim || pc>dim)
	{
		return false;
	}
	else
		return true;
}


void placeMove(char B[][cap], int pr, int pc, char sym)
{
	B[pr][pc] = sym;
}

void turnChange(int& turn, int nop)
{
	turn = (turn + 1) % nop;
}

bool checkHorizental(char B[][cap], int dim, int pri, int pci, int winCond, char pSym)
{
	if (pci + winCond > dim)
		return false;
	for (int i = 0; i < winCond; i++)
	{
		if (B[pri][pci + i] != pSym)
			return false;
	}
	return true;
}

bool checkVertical(char B[][cap], int dim, int pri, int pci, int winCond, char pSym)
{
	if (pri + winCond > dim)
		return false;
	for (int i = 0; i < winCond; i++)
	{
		if (B[pri + i][pci] != pSym)
			return false;
	}
	return true;
}

bool checkDiagnolL2R(char B[][cap], int dim, int pri, int pci, int winCond, char pSym)
{
	if (pri + winCond > dim || pci + winCond > dim)
		return false;
	for (int i = 0; i < winCond; i++)
	{
		if (B[pri + i][pci + i] != pSym)
			return false;
	}
	return true;
}

bool checkDiagnolR2L(char B[][cap], int dim, int pri, int pci, int winCond, char pSym)
{
	if (pri + winCond > dim || pci + winCond > dim)
		return false;
	for (int i = 0; i < winCond; i++)
	{
		if (B[pri + i][pci - i] != pSym)
			return false;
	}
	return true;
}

bool allWinConditions(char B[][cap], int dim, int pri, int pci, int winCond, char pSym)
{
	if (checkHorizental(B, dim, pri, pci, winCond, pSym))
		return true;
	if (checkVertical(B, dim, pri, pci, winCond, pSym))
		return true;
	if (checkDiagnolL2R(B, dim, pri, pci, winCond, pSym))
		return true;
	if (checkDiagnolR2L(B, dim, pri, pci, winCond, pSym))
		return true;
	else
		return false;
}

bool isWinner(char B[][cap], int dim, int winCond, char pSym)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (allWinConditions(B, dim, r, c, winCond, pSym))
				return true;
		}
	}
	return false;
}

bool isDraw(char B[][cap], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (B[r][c] == '_')
				return false;
		}
	}
	return true;
}

void init2(char B[][cap], int& dim, char pName[][cap], char sym[cap], int& winCond, int& turn)
{
	cout << "\nEnter Dimensions :";
	cin >> dim;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			B[r][c] = '_';
		}
	}
	cout << "\nEnter your Name : ";
	cin >> pName[hum];
	cout << "\nEnter your symbol : ";
	cin >> sym[hum];
	cout << "\nEnter comp name : ";
	cin >> pName[comp];
	cout << "\nEnter Winning Condition : ";
	cin >> winCond;
	srand(time(NULL));
	turn = rand() % 2;
}

void compPositioning(char B[][cap], int dim, int& pr, int& pc, char sym[cap], int winCond)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			pr = r;
			pc = c;
			if (isValid(B, dim, pr, pc))
			{
				B[r][c] = sym[comp];
				if (isWinner(B, dim, winCond, sym[comp]))
				{
					B[r][c] = '_';
					return;
				}
				B[r][c] = '_';
			}
		}
	}
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			pr = r;
			pc = c;
			if (isValid(B, dim, pr, pc))
			{
				B[r][c] = sym[hum];
				if (isWinner(B, dim, winCond, sym[hum]))
				{
					B[r][c] = '_';
					return;
				}
				B[r][c] = '_';
			}
		}
	}
	do {
		pr = rand() % dim;
		pc = rand() % dim;
	} while (!isValid(B, dim, pr, pc));
}

void mainhumvshum()
{
	char B[cap][cap], sym[cap], pName[cap][cap];
	int dim, turn, nop, winCond, pr, pc, dCheck = -99;
	bool gameEnd = false;
	init(B, dim, nop, turn, sym, pName, winCond);
	boardPrint(B, dim);
	while (!gameEnd)
	{
		turnMsg(pName[turn]);
		do {
			selectPos(pr, pc, dim);
			if (!isValid(B, dim, pr, pc))
			{
				cout << "\n\nIllegal Move\n\nEnter Again : \n";
			}
		} while (!isValid(B, dim, pr, pc));
		placeMove(B, pr, pc, sym[turn]);
		boardPrint(B, dim);
		if (isWinner(B, dim, winCond, sym[turn]))
		{
			gameEnd = true;
			dCheck = 0;
		}
		if (isDraw(B,dim))
		{
			gameEnd = true;
		}
		if (gameEnd == false)
		{
			turnChange(turn, nop);
		}
	}
	if (dCheck == -99)
	{
		cout << "\n\nIt is a tie\n";
	}
	else
		cout << "\n\n" << pName[turn] << " has won the game\n\n";
}

void mainAIvsHum()
{
	char B[cap][cap], sym[cap];char pName[cap][cap];
	sym[comp] = '0';
	int dim, turn, nop = 2, winCond, pr, pc, dCheck = -99;
	bool gameEnd = false;
	init2(B, dim, pName, sym, winCond, turn);
	boardPrint(B, dim);
	while (!gameEnd)
	{
		turnMsg(pName[turn]);
		if (turn == comp)
		{
			compPositioning(B, dim, pr, pc, sym, winCond);
		}
		else
		{
			do {
				selectPos(pr, pc, dim);
				if (!isValid(B, dim, pr, pc))
				{
					cout << "\nIllegal Move\nEnter Again :\n";
				}
			} while (!isValid(B, dim, pr, pc));
		}
		placeMove(B, pr, pc, sym[turn]);
		boardPrint(B, dim);
		if (isWinner(B, dim, winCond, sym[turn]))
		{
			gameEnd = true;
			dCheck = 0;
		}
		if (isDraw(B, dim))
		{
			gameEnd = true;
		}
		if (gameEnd == false)
		{
			turnChange(turn, nop);
		}
	}
	if (dCheck == -99)
	{
		cout << "\n\nIt is a tie\n";
	}
	else
		cout << "\n\n" << pName[turn] << " has won the game\n\n";
}

int main() {
	int choose;
	cout << "\nChoose between\n1: Single Player\n2: Multiplayer" << endl;
	cin >> choose;
	while (true) {
		while (choose < 1 || choose >2) {
			cout << "Invalid Input!...Enter Again: ";
			cin >> choose;
		}
		if (choose == 1) {
			mainAIvsHum();
		}
		else if (choose == 2) {
			mainhumvshum();
		}
		cout << "\nChoose between\n1: Single Player\n2: Multiplayer" << endl;
		cin >> choose;
	}
	return 0;
}












