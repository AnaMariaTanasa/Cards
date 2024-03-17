#pragma once
struct Card
{
	unsigned int val;
	char* symbol;
	Card* next, * prec;
};
struct Deck
{
	unsigned int nc;//number of cards
	Card* fc, * lc;//first card,last card;
	Deck* next, * prec;
};
struct Game
{
	unsigned int nd;
	Deck* fd, * ld;//first deck,last deck;
};

//functii
void ADD_DECK(Game& g, unsigned int nrc);//nrc=number of cards
void ADD_CARD(Deck*& d, char* s, unsigned int val);
void SHOW_ALL(Game& g);
void SHOW_DECK(Game& g, unsigned int index);
void erori(const char* s);
void EXIT(void);
void DECK_NUMBER(Game& g);
void DECK_LEN(Game& g, unsigned int index);
Deck* parcurgerePSD(Game& g, unsigned int index);
Deck* parcurgerePFD(Game& g, unsigned int index);//parcurgere de la  elementul final
void DEL_CARD(Game& g, unsigned int index1, unsigned int index2);
Card* parcurgerePSC(Deck*& d, unsigned int index);
Card* parcurgerePFC(Deck*& d, unsigned int index);
void DEL_DECK(Game& g, unsigned int index);
void ADD_CARDS(Game& g, unsigned int indexd, unsigned int nrc);
//void SORT_DECK(Game& g, unsigned int index,char s[][8]);
Deck* FIND_DECK(Game& g, unsigned int index);
void SPLIT_DECK(Game& g, unsigned int indexd, unsigned int indexs);
void SHUFFLE_DECK(Game& g, unsigned int index);
Card* FIND_CARD(Deck*& d, unsigned int index);
void MERGE_DECKS(Game& g, unsigned int index1, unsigned int index2);
void help();
void meniu(char*& com, Game& g, char s[][8]);
void REVERSE_DECK(Game& g, unsigned int index);