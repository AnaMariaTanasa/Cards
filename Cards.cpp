#include <iostream>
#include <cstring>
#include "Cards.h"
using namespace std;
void ADD_DECK(Game& g, unsigned int nrc)//nrc=number of cards
{
	unsigned int i = 0;
	char str[10];
	unsigned int val;
	Deck* d = new Deck;
	memset(d, 0, sizeof(Deck));
	if (g.fd == 0 && g.ld == 0)//game is empty
	{
		g.fd = g.ld = d;
		g.nd = 1;
	}
	else// insert after last deck
	{
		g.nd++;
		g.ld->next = d;
		d->prec = g.ld;
		g.ld = g.ld->next;
	}
	while (i < nrc)//adds nrc cards
	{
		printf("Card %d from deck %u\n", i + 1, g.nd);
		cout << "Symbol:" << '\n';
		cin >> str;
		cout << "Value:" << '\n';
		cin >> val;
		if ((strcmp(str, "PICA") == 0 || strcmp(str, "CUPA") == 0 || strcmp(str, "CARO") == 0 || strcmp(str, "TREFLA") == 0) && (val >= 1 && val <= 14))
		{
			ADD_CARD(d, str, val);
			d->nc++;
			i++;
		}
		else
			erori("INVALID_CARD");
	}
	printf("The deck was succesfully created with %u cards.\n", nrc);
}
void ADD_CARD(Deck*& d, char* s, unsigned int val)
{
	Card* c = new Card;
	memset(c, 0, sizeof(Card));//init card
	c->symbol = new char;
	strcpy_s(c->symbol,sizeof(s), s);
	c->val = val;
	if (d->fc == 0 && d->lc == 0)//if deck is empty,init deck
	{
		d->fc = d->lc = c;
	}
	else
	{
		d->lc->next = c;
		c->prec = d->lc;
		d->lc = c;
	}
}
void ADD_CARDS(Game& g, unsigned int indexd, unsigned int nrc)
{
	Deck* d;
	char str[8];
	unsigned int val, i = 0;
	if (indexd > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	else
	{
		d = FIND_DECK(g, indexd);
		while (i < nrc)
		{
			printf("Card %d from deck %u\n", d->nc + 1, g.nd);
			cin >> str;
			cin >> val;
			if ((strcmp(str, "PICA") == 0 || strcmp(str, "CUPA") == 0 || strcmp(str, "CARO") == 0 || strcmp(str, "TREFLA") == 0) && (val >= 1 && val <= 14))
			{
				ADD_CARD(d, str, val);
				d->nc++;
				i++;
			}
			else
				erori("INVALID_CARD");
		}
		printf("The cards were successfully added to deck %u.\n", indexd);
	}

}
void SHOW_ALL(Game& g)
{
	int contor = 1;
	Deck* d = g.fd;
	Card* c;
	while (d)
	{
		printf("Deck %d:\n", contor);
		c = d->fc;
		while (c)
		{
			printf("\t%u %s\n", c->val, c->symbol);
			c = c->next;
		}
		d = d->next;
		contor++;
	}
}
void SHOW_DECK(Game& g, unsigned int index)
{
	if (g.nd > index)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Deck* d = FIND_DECK(g, index);
	Card* c = d->fc;//first card of the deck
	printf("Deck %u:\n", index);
	while (c)
	{
		printf("\t%u %s\n", c->val, c->symbol);
		c = c->next;
	}
}
void erori(const char* s)
{
	if (strcmp(s, "INVALID_CARD") == 0)
		fprintf(stderr, "The provided card is not valid.\n");
	else if (strcmp(s, "DECK_INDEX_OUT_OF_BOUNDS") == 0)
		fprintf(stderr, "The provided deck index is out of bounds.\n");
	else if (strcmp(s, "CARD_INDEX_OUT_OF_BOUNDS") == 0)
		fprintf(stderr, "The provided card index is out of bounds.\n");
	else fprintf(stderr, "Invalid command.Please try again.\n");
}
void EXIT(void)
{
	exit(0);
}
void DECK_NUMBER(Game& g)
{
	printf("The number of decks is %u.\n", g.nd);
}
Deck* parcurgerePSD(Game& g, unsigned int index)//parcurgere de la primul element
{
	unsigned int i = 1;
	Deck* d = g.fd;
	while (i < index)
	{
		d = d->next;
		i++;
	}
	return d;
}
Deck* parcurgerePFD(Game& g, unsigned int index)//parcurgere de la elementul final
{
	unsigned int i = 1;
	Deck* d = g.ld;
	while (i < index)
	{
		d = d->prec;
		i++;
	}
	return d;
}
void DECK_LEN(Game& g, unsigned int index)
{
	if (g.nd < index)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Deck* d = FIND_DECK(g, index);
	printf("The length of deck %u is %u.\n", index, d->nc);
}
void DEL_DECK(Game& g, unsigned int index)
{
	Deck* d;
	Card* c;
	if (index > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	else
	{
		d = FIND_DECK(g, index);
		if (d->next == 0 && d->prec)// if deck is last in the game
		{
			g.ld = g.ld->prec;
			g.ld->next = 0;
		}
		else if (d->prec == 0 && d->next)//if deck is first in the game
		{
			g.fd = g.fd->next;
			g.fd->prec = 0;
		}
		else if (d->prec && d->next)
		{
			d->prec->next = d->next;
			d->next->prec = d->prec;
		}
		//deletes cards
		while (d->fc)
		{
			c = d->fc;
			d->fc = d->fc->next;
			memset(c, 0, sizeof(Card));
			delete c->symbol;
			delete c;
			c = 0;
		}
		memset(d, 0, sizeof(Deck));
		delete d;
		d = 0;
		g.nd--;
		printf("The deck %u was successfully deleted.\n", index);
	}
}
void DEL_CARD(Game& g, unsigned int index1, unsigned int index2)
{
	Deck* d;
	Card* c;
	if (index1 > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	else
	{
		d = FIND_DECK(g, index1);
		if (index2 > d->nc)
		{
			erori("CARD_INDEX_OUT_OF_BOUNDS");
			return;
		}
		else
		{
			c = FIND_CARD(d, index2);
			if (c->prec == 0 && c->next == 0)//if deck is empty,deletes deck
			{
				DEL_DECK(g, index1);
				return;
			}
			if (c->prec == 0 && c->next)//if card is first in deck
			{
				d->fc = c->next;
				d->fc->prec = 0;
			}
			else if (c->next == 0 && c->prec)//if card is last in deck
			{
				d->lc = d->lc->prec;
				d->lc->next = 0;
			}
			else if (c->next && c->prec)
			{
				c->prec->next = c->next;
				c->next->prec = c->prec;
			}
			memset(c->symbol, 0, sizeof(char));//deletes card
			delete c->symbol;
			c->symbol = 0;
			memset(c, 0, sizeof(Card));
			delete c;
			c = 0;
			d->nc--;
		}
		printf("The card %u was successfully deleted from deck %u.\n", index2, index1);
	}
}
Card* parcurgerePSC(Deck*& d, unsigned int index)
{
	unsigned int i = 1;
	Card* c = d->fc;
	while (i < index)
	{
		c = c->next;
		i++;
	}
	return c;
}
Card* parcurgerePFC(Deck*& d, unsigned int index)//parcurgere de la elementul final
{
	unsigned int i = 1;
	Card* c = d->lc;
	while (i < index)
	{
		c = c->prec;
		i++;
	}
	return c;
}
/*void SORT_DECK(Game& g, unsigned int index, char s[][8])//s={PICA,CUPA,CARO,TREFLA}
{
	if (g.nd <index)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Deck* d = FIND_DECK(g, index);
	Card* c;
	int i, j;
	bool ok = 0;
	bool schimb = 1;
	while (schimb)//bubble sort by value and symbol
	{
		schimb = 0;
		c = d->fc;
		while (c && c->next)
		{
			ok = 0;
			if (c->val > (c->next)->val)
			{
				ok = 1;
			}
			else if (c->val == c->next->val)
			{
				for (i = 0; i < 3; i++)
				{
					if (strcmp(c->symbol, s[i]) == 0)
					{
						for (j = i + 1; j < 4; j++)
						{
							if (strcmp(c->next->symbol, s[j]) == 0)
							{
								ok = 1; break;
							}
						}
					}
				}
			}

			if (ok)//swaps values and symbols
			{
				schimb = 1;
				swap(c->symbol, (c->next)->symbol);
				swap(c->val, (c->next)->val);
			}
			c = c->next;
		}
	}
	printf("The deck %u was successfully sorted.\n", index);

}
*/
Deck* FIND_DECK(Game& g, unsigned int index)
{
	Deck* d;
	if (index <= g.nd / 2)
		d = parcurgerePSD(g, index);
	else
		d = parcurgerePFD(g, g.nd - index + 1);
	return d;
}
Card* FIND_CARD(Deck*& d, unsigned int index)
{
	Card* c;
	if (index <= d->nc / 2)//if index is closer to first element of the deck
		c = parcurgerePSC(d, index);
	else
		c = parcurgerePFC(d, d->nc - index + 1);// if index is closer to final element of the deck
	return c;
}
void SPLIT_DECK(Game& g, unsigned int indexd, unsigned int indexs)
{
	if (g.nd < indexd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Deck* d = FIND_DECK(g, indexd);
	if (indexs == 0 || indexs == d->nc)
	{
		printf("The deck %u was successfully split by index %u.\n", indexd, indexs);
		return;
	}
	Deck* nd = new Deck;//new deck
	Card* c;
	if (d->nc < indexs)
	{
		erori("CARD_INDEX_OUT_OF_BOUNDS");
		return;
	}
	//find card with indexs
	c = parcurgerePSC(d, indexs + 1);
	//removes links from split-index card and makes the specified card first in the new deck
	c->prec->next = 0;
	c->prec = 0;
	nd->nc = d->nc - indexs;
	nd->fc = c;
	nd->lc = d->lc;
	//adds deck to game
	nd->prec = d;
	nd->next = d->next;
	if (d->next)
	{
		d->next->prec = nd;

	}
	d->next = nd;
	g.nd++;
	printf("The deck %u was successfully split by index %u.\n", indexd, indexs);
}
void SHUFFLE_DECK(Game& g, unsigned int index)
{
	if (index > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Card* c;
	Deck* d = FIND_DECK(g, index);
	c = FIND_CARD(d, d->nc / 2 + 1);
	//removes link from middle cards and makes the middle card first in deck
	c->prec->next = 0;
	c->prec = 0;
	d->lc->next = d->fc;
	d->fc->prec = d->lc;
	d->fc = c;
}
void MERGE_DECKS(Game& g, unsigned int index1, unsigned int index2)
{
	if (index1 > g.nd || index2 > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	Deck* d1 = FIND_DECK(g, index1);
	Deck* d2 = FIND_DECK(g, index2);
	Card* c1 = d1->fc, * c2 = d2->fc;
	Deck* dfinal = new Deck;
	memset(dfinal, 0, sizeof(Deck));
	while (c1 && c2)
	{
		ADD_CARD(dfinal, c1->symbol, c1->val);
		ADD_CARD(dfinal, c2->symbol, c2->val);
		c1 = c1->next;
		c2 = c2->next;
		dfinal->nc += 2;
	}
	while (c1)
	{
		ADD_CARD(dfinal, c1->symbol, c1->val);
		c1 = c1->next;
		dfinal->nc++;
	}
	while (c2)
	{
		ADD_CARD(dfinal, c2->symbol, c2->val);
		c2 = c2->next;
		dfinal->nc++;
	}
	//adds deck at the end of game
	g.nd++;
	g.ld->next = dfinal;
	dfinal->prec = g.ld;
	dfinal->next = 0;
	g.ld = dfinal;
	//deletes decks
	if (index1 < index2)
	{
		DEL_DECK(g, index2);
		DEL_DECK(g, index1);
	}
	else
	{
		DEL_DECK(g, index1);
		DEL_DECK(g, index2);
	}
}
void help()
{
	printf("\t\t\t\tAvailable commands\n");
	printf("\tADD_DECK <number of cards> adds a deck to the game with specified number of cards\n");
	printf("\tDEL_DECK <deck_index> deletes the deck with specified index\n");
	printf("\tDEL_CARD <deck_index> <card_index> deletes specified card from specified deck\n");
	printf("\tADD_CARDS <deck_index> <number of cards> add a given number of cards to a specified deck\n");
	printf("\tDECK_NUMBER shows number of decks in the game\n");
	printf("\tDECK_LEN <deck_index> shows number of cards in specified deck\n");
	printf("\tSHUFFLE_DECK <deck_index> shuffles deck\n");
	printf("\tMERGE_DECKS <deck_index1> <deck_index2> merges the 2 decks in a new one\n");
	printf("\tSPLIT_DECK <deck_index> <split_index> splits given deck by specified index\n");
	printf("\tREVERSE_DECK <deck_index> reverses given deck.\n");
	printf("\tSHOW_DECK <deck_index> shows cards from specified deck\n");
	printf("\tSHOW_ALL shows all the decks and cards\n");
	printf("\tSORT_DECK <deck_index> sorts deck by priority rules\n");
	printf("\t help() shows this list again\n");
}
void meniu(char*& com, Game& g, char s[][8])
{
	unsigned int nrcards = 0, index1, index2;
	if (strcmp(com, "ADD_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> nrcards;
		ADD_DECK(g, nrcards);
	}
	else if (strcmp(com, "DEL_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		DEL_DECK(g, index1);
	}
	else if (strcmp(com, "DEL_CARD") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1 >> index2;
		if (index1 == 0 || index2 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		DEL_CARD(g, index1, index2);
	}
	else if (strcmp(com, "ADD_CARDS") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1 >> nrcards;
		if (index1 == 0 || nrcards == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		ADD_CARDS(g, index1, nrcards);
	}
	else if (strcmp(com, "DECK_NUMBER") == 0)
	{
		DECK_NUMBER(g);
	}
	else if (strcmp(com, "DECK_LEN") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		DECK_LEN(g, index1);
	}
	else if (strcmp(com, "SHUFFLE_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		SHUFFLE_DECK(g, index1);
	}
	else if (strcmp(com, "MERGE_DECKS") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1 >> index2;
		if (index1 == 0 || index2 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		MERGE_DECKS(g, index1, index2);
	}
	else if (strcmp(com, "SPLIT_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1 >> index2;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		SPLIT_DECK(g, index1, index2);
	}
	else if (strcmp(com, "REVERSE_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		REVERSE_DECK(g, index1);
	}
	else if (strcmp(com, "SHOW_DECK") == 0)
	{
		cout << "Params" << '\n';
		cin >> index1;
		if (index1 == 0)
		{
			cout << "Invalid command.\n";
			return;
		}
		SHOW_DECK(g, index1);
	}
	else if (strcmp(com, "SHOW_ALL") == 0)
	{
		if (g.nd == 0)
		{
			cout << "There are no decks.\n";
			return;
		}
		SHOW_ALL(g);
	}

	else if (strcmp(com, "EXIT") == 0)
	{
		EXIT();
	}
	else if (strcmp(com, "help") == 0 || strcmp(com, "h") == 0
		|| strcmp(com, "HELP") == 0)
	{
		help();
	}
	else
	{
		cout << "Invalid command" << '\n';
		return;
	}
}
void REVERSE_DECK(Game& g, unsigned int index)
{
	if (index > g.nd)
	{
		erori("DECK_INDEX_OUT_OF_BOUNDS");
		return;
	}
	else
	{
		Deck* d = FIND_DECK(g, index);
		Card* temp = NULL;
		Card* current = d->fc;
		//swap all nodes until the second pointer is not NULL
		while (current)
		{
			temp = current->prec;
			current->prec = current->next;
			current->next = temp;
			current = current->prec;
		}
		//changes first card of the deck
		if (temp)
			d->fc = temp->prec;
	}
}