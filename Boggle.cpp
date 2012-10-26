#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;


#define LEN 18

struct WNode
{
	char word[LEN];
	WNode* next;
};

class Boogle
{
public:
	Boogle(void){};
//	Boogle(Boogle &other);
	int Randomize(const char* dice[]);
	int Customize(void);
	int Print(int score);
	WNode* FindWords(WNode* dict);
	WNode* FakeWords(WNode* dict);
	int PrintWords(void);
	bool isValidWord(char* word);

	int maxP;

private:
	char letters[17];
};




int validate(const char* word, WNode* wordList, WNode* prev);
WNode* addWord(const char* word, WNode* list);

bool checkGuess(const char* word, WNode* sList, WNode* pList)
{
	auto WNode* traverser = pList;

	while(traverser)
		{
		if(0== strcmp(word, traverser->word)) return false;
		traverser = traverser->next;
		}

	traverser = sList;
	while(traverser)
		{
		if(0 == strcmp(word, traverser->word)) return true;
		traverser = traverser->next;
		}
	return false;
}


WNode* LoadDict(const char* fname)
{
	auto ifstream infile;
	auto int i = 0;
	auto char word[LEN];
	auto WNode* headPtr = new WNode;
	auto WNode* adder = headPtr;

	infile.open(fname);
	infile >> adder->word;
	adder->next = new WNode;

	while(infile >> adder->next->word)
		{
		adder = adder->next;
		adder->next = new WNode;
		}
	delete adder->next;
	adder->next = NULL;
	infile.close();
if (headPtr == NULL) cout << "Dictionary failed to load\n";
	return headPtr;
}

void DestroyList(WNode* head)
{
	auto WNode* trail = head;
	while(head)
		{
		head = head->next;
		delete trail;
		trail = head;
		}
}



void tester(WNode* d)
{
	int i;
	for(i = 0; i < 20; i++)
		{
		cout << d->word << endl;
		d = d->next;
		}

	cout << "\nLast Word:\n  ";
	while(d->next != NULL) d = d->next;

	cout << d->word << endl;
}


int MaxScore(WNode* wList)
{
	auto WNode* traverser = wList;
	auto int total = 0;

	while(traverser)
		{
		total += (strlen(traverser->word) - 2);
		traverser = traverser->next;
		}

	return total;
}



int main(void)
{
	auto const char* dice[16] = {"VITEGN"
								,"ACESLR"
								,"VAZEDN"
								,"ICATAO"
								,"NODUKT"
								,"ENIPHS"
								,"ORIFBX"
								,"KULEGY"
								,"EYIEHF"
								,"ESUTLP"
								,"EWOSDN"
								,"PECADM"
								,"ALIBTY"
								,"SAHOMR"
								,"JABOMQ"
								,"URIGLW"};


	srand((unsigned)time(NULL));
	auto WNode* wordList = LoadDict("dict.txt");
//	tester(wordList);//yep it looks like it worked

	//create grid
	auto Boogle grid;

	//randomize, solve, & print
	grid.Randomize(dice);
	auto WNode* solvedList = grid.FindWords(wordList);
//auto WNode* solvedList = grid.FakeWords(wordList);

	auto WNode* pList = NULL;
	auto WNode* tbag;
	auto char datChar;
	auto char userWord[LEN];
	auto int wolen;
	auto int ctr;
	auto int Pscore = 0;

	grid.Print(Pscore);
	//loop for words + print
	while(cin >> userWord)
		{
		wolen = strlen(userWord);
		for(ctr=0; ctr<wolen; ctr++) userWord[ctr] = toupper(userWord[ctr]);
		//if !, print all words
		if('!' == userWord[0])
			{
			cout << "  (M)y Words\n  (C)ustom\n  (S)olve\n  (N)ew\n  (Q)uit\n";
			cin >> datChar;
			switch(toupper(datChar))
				{
//create case to see pList
				case 'M':
					cout << "\n Your words:\n";
					tbag = pList;
					while(tbag)
						{
						cout << "  " << tbag->word << endl;
						tbag = tbag->next;
						}
					break;
				case 'C':
					grid.Customize();
					DestroyList(solvedList);
					DestroyList(pList);
					pList = NULL;
					solvedList = grid.FindWords(wordList);
					Pscore = 0;
					break;
				case 'S':
					tbag = solvedList;
					while(tbag)
						{
						cout << tbag->word << endl;
						tbag = tbag->next;
						}
					cout << "Max possible score: " << grid.maxP << endl;
					break;
				case 'N':
					grid.Randomize(dice);
					DestroyList(solvedList);
					DestroyList(pList);pList = NULL;
					solvedList = grid.FindWords(wordList);
					Pscore = 0;
					break;
				case 'Q':
					cout << "Thank you for playing!\n\n";
					exit(EXIT_SUCCESS);
				}
			}
		else{
			if (checkGuess(userWord, solvedList, pList))
				{
				pList = addWord(userWord, pList);
				cout << endl << userWord << " found!\n";
				}
			else cout << "Sorry, invalid guess\n";
			}

		Pscore = MaxScore(pList);
		grid.Print(Pscore);
		}//should keep looping until the menu calls exit

	DestroyList(wordList);
//release lists... bah
	return 0;
}


int Boogle::Randomize(const char* dice[])
{
	auto int sand;
	auto int ctr;

	for (ctr = 0; ctr < 16; ctr++)
		{
		sand = rand() % 6;
		letters[ctr] = dice[ctr][sand];
		}
	letters[ctr] = '\0';
	return ctr;
}


int Boogle::Customize(void)
{
	auto char inch;
	auto int ctr;

	cout << "Enter 16 letters:\n";
	for (ctr = 0; ctr < 16; ctr++)
		{
		cin >> inch;
		letters[ctr] = toupper(inch);
		}
	letters[ctr] = '\0';
	return ctr;
}



int Boogle::Print(int score)
{
	auto int ctr;

	for (ctr = 0; ctr < 16; ctr++)
		{
		if (0 == ctr%4) cout << "\n  ";
		if ('Q' == letters[ctr]) cout << " Qu";
		else cout << " " << letters[ctr] << " ";
		}
	cout << "\nScore: " << score << "\nEnter a word: (Enter an '!' for menu)\n";
	return ctr;
}


bool isIn(int a, const int* path, int n)
{
	auto int ctr;
	for (ctr = 0; ctr < n; ctr++)
		{
		if (a == path[ctr]) return true;
		}
	return false;
}

int nextAdj(const int* path, int n)
{
	auto int ctr = 0;
	auto int numPoss;
	auto int poss[8];

	switch(path[n-1])
		{
		case 0: poss[0] = 1;
				poss[1] = 4;
				poss[2] = 5;
				numPoss = 3;
				break;
		case 1: poss[0] = 0;
				poss[1] = 2;
				poss[2] = 4;
				poss[3] = 5;
				poss[4] = 6;
				numPoss = 5;
				break;
		case 2: poss[0] = 1;
				poss[1] = 3;
				poss[2] = 5;
				poss[3] = 6;
				poss[4] = 7;
				numPoss = 5;
				break;
		case 3: poss[0] = 2;
				poss[1] = 6;
				poss[2] = 7;
				numPoss = 3;
				break;
		case 4: poss[0] = 0;
				poss[1] = 1;
				poss[2] = 5;
				poss[3] = 8;
				poss[4] = 9;
				numPoss = 5;
				break;
		case 5: poss[0] = 0;
				poss[1] = 1;
				poss[2] = 2;
				poss[3] = 4;
				poss[4] = 6;
				poss[5] = 8;
				poss[6] = 9;
				poss[7] = 10;
				numPoss = 8;
				break;
		case 6: poss[0] = 1;
				poss[1] = 2;
				poss[2] = 3;
				poss[3] = 5;
				poss[4] = 7;
				poss[5] = 9;
				poss[6] = 10;
				poss[7] = 11;
				numPoss = 8;
				break;
		case 7: poss[0] = 2;
				poss[1] = 3;
				poss[2] = 6;
				poss[3] = 10;
				poss[4] = 11;
				numPoss = 5;
				break;
		case 8: poss[0] = 4;
				poss[1] = 5;
				poss[2] = 9;
				poss[3] = 12;
				poss[4] = 13;
				numPoss = 5;
				break;
		case 9: poss[0] = 4;
				poss[1] = 5;
				poss[2] = 6;
				poss[3] = 8;
				poss[4] = 10;
				poss[5] = 12;
				poss[6] = 13;
				poss[7] = 14;
				numPoss = 8;
				break;
		case 10:poss[0] = 5;
				poss[1] = 6;
				poss[2] = 7;
				poss[3] = 9;
				poss[4] = 11;
				poss[5] = 13;
				poss[6] = 14;
				poss[7] = 15;
				numPoss = 8;
				break;
		case 11:poss[0] = 6;
				poss[1] = 7;
				poss[2] = 10;
				poss[3] = 14;
				poss[4] = 15;
				numPoss = 5;
				break;
		case 12:poss[0] = 8;
				poss[1] = 9;
				poss[2] = 13;
				numPoss = 3;
				break;
		case 13:poss[0] = 8;
				poss[1] = 9;
				poss[2] = 10;
				poss[3] = 12;
				poss[4] = 14;
				numPoss = 5;
				break;
		case 14:poss[0] = 9;
				poss[1] = 10;
				poss[2] = 11;
				poss[3] = 13;
				poss[4] = 15;
			 	numPoss = 5;
			 	break;
		case 15:poss[0] = 10;
				poss[1] = 11;
				poss[2] = 14;
				numPoss = 3;
				break;
		default: cout << "path[n-1] out of bounds in nextAdj. n = " << n << endl;
				int j; for (j=0; path[j] > 0; j++) cout << path[j] << " ";
		}

	//basically the NEXT possible...
	while (ctr<numPoss && ((path[n] >= poss[ctr]) || (isIn(poss[ctr], path, n-1)))) ctr++;

	//poss[ctr] is our nextAdj, unless there was no poss.
	if (ctr == numPoss) return -1;
	else return poss[ctr];
}


//major work in progress here
WNode* Boogle::FindWords(WNode* dict)
{
	auto WNode* Words = NULL;
	auto char bogWord[17];
	auto int ltrCpy;
	auto int path[16] = {0, 1, 2, -1};
	auto int n = 3;
	auto int wlen;
	auto int val;
	auto bool bLoop = true;


	while(bLoop)//this guy rotates from the end
		{
		for(ltrCpy = 0; ltrCpy < n; ltrCpy++)
			{
			bogWord[ltrCpy] = letters[(path[ltrCpy])];
			}
		bogWord[ltrCpy] = '\0';

		val = validate(bogWord, dict, Words);

		if		(val == 1) Words = addWord(bogWord, Words);
		else if (val <  0) n = -1 * val;


//path[n] should be set to the next adjecent available.
//if there is no possible next path, roll back the path and...
//look for a next possible. again if there is none, roll back
//if we roll back to n=0, we should increment path[0] until it is >15
		while (-1 == (path[n] = nextAdj(path, n)))
			{
			n--;
			if (0 == n)
				{
				path[0]++;
				if (path[0] == 16)
					{
					bLoop = false;
					break;
					}
				n++;
				}
			}
		++n;
		path[n] = -1;
		}

	maxP = MaxScore(Words);
	return Words;
}




WNode* Boogle::FakeWords(WNode* dict)
{
	auto WNode* Words = NULL;
	auto char word[17];
	auto int ctr,ctr2, val;
	for (ctr=0; ctr<3; ctr++)
		{
		cout << "Enter a fake word: ";
		cin >> word;
		val = validate(word, dict, Words);
		if (-1 == val) cout << "Invalid\n";
		else if (1 == val) Words = addWord(word, Words);
		}
	maxP = MaxScore(Words);
	return Words;
}


int validate(const char* word, WNode* dict, WNode* prev)
{//-n invalid word, 0 possible word, 1 add to list

	auto int wlen = strlen(word);

	while(prev)
		{//may have been gettting errors here...
		if (wlen == strlen(prev->word))//may still be...
			{
			if (0 == strcmp(word, prev->word)) return wlen * -1;
			}
		prev = prev->next;
		}

	auto WNode* traverser = dict;
	auto int ctr = 0;

	while (traverser)
		{
		while (traverser->word[ctr] < word[ctr])
			{
			if (ctr > 0) if (traverser->word[ctr-1] != word[ctr-1]) break;
			traverser = traverser->next;
			}
		if (traverser->word[ctr] == word[ctr]) ctr++;
		else return -1 * ctr;

		if (ctr == wlen)
			{
			if (strlen(traverser->word) == wlen)
				{
				return 1;
				}
			else return 0;
			}
		}

}



WNode* addWord(const char* word, WNode* list)
{
	auto int wlen = strlen(word)+1;
	auto WNode* adder = new WNode;

	strncpy(adder->word, word, wlen);
	adder->next = list;

	return adder;
}


