#ifndef GIN_RUMMY_H
#define GIN_RUMMY_H

#include <iostream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;
////
//  Node<T>
////
//
template <typename T>
struct Node
{
	Node(T ndata) : data(ndata), next(nullptr), prev(nullptr){};
	T data;
	Node<T> *next;
	Node<T> *prev;
};

////
//  List<T>
////
//
//  Doubly linked list.  Supports inserting and deleting at any position.
//

//
//  List<T> Header
//
template <typename T>
class List
{
	template <typename D>
	friend std::ostream &operator<<(std::ostream &out, const List<D> &li);

private:
	Node<T> *firstPtr;
	Node<T> *lastPtr;
	int count = 0;

public:
	Node<T> *firstNode() { return firstPtr; };
	List();
	~List();
	T first() const;
	T last() const;
	int size();
	void push_back(T newData);
	void push_front(T newData);
	T pop_back();
	T pop_front();
	void insert_at(int i, T newData);
	T remove_at(int i);
	int find(T card);
};
//
//  List<T> Implementation
//

template <typename T>
int List<T>::find(T card)
{
	int result = -1;
	int i = 1;
	Node<T> *curr = firstPtr;
	if (firstPtr->data == card)
		return i;
	while (curr and result == -1)
	{ //run thru whole list cause dont want no seg fault
		if (curr->data == card)
			result = i;
		else
		{
			curr = curr->next;
			i++;
		}
	}
	return result;
};

template <typename T>
List<T>::List()
{
	firstPtr = nullptr;
	lastPtr = nullptr;
};

template <typename T>
List<T>::~List()
{
	while (firstPtr)
	{
		Node<T> *trash = firstPtr;
		firstPtr = trash->next;
		delete trash;
	}
};

template <typename T>
T List<T>::first() const
{
	return (firstPtr->data);
};

template <typename T>
T List<T>::last() const
{
	return (lastPtr->data);
};

template <typename T>
int List<T>::size()
{
	return count;
};

template <typename T>
void List<T>::push_back(T newData)
{
	if (count == 0)
	{
		firstPtr = new Node<T>(newData);
		firstPtr->data = newData;
		firstPtr->next = nullptr;
		firstPtr->prev = nullptr;
		lastPtr = firstPtr;
	}
	else
	{
		Node<T> *current = new Node<T>(newData);
		current->data = newData;
		current->next = nullptr;
		current->prev = lastPtr;
		lastPtr->next = current;
		lastPtr = current;
	}
	count++;
};

template <typename T>
void List<T>::push_front(T newData)
{
	if (count == 0)
		push_back(newData);
	else
	{
		Node<T> *newFirst = new Node<T>(newData);
		newFirst->data = newData;
		firstPtr->prev = newFirst;
		newFirst->next = firstPtr;
		newFirst->prev = nullptr;
		firstPtr = newFirst;
		count++;
	}
};

template <typename T>
T List<T>::pop_back()
{
	T result = lastPtr->data;
	if (count > 1)
	{
		Node<T> *trash = lastPtr;
		lastPtr = trash->prev;
		lastPtr->next = nullptr;
		delete trash;
	}
	if (count == 1)
	{
		delete firstPtr;
		firstPtr = nullptr;
		lastPtr = nullptr;
	}
	count--;
	return result;
};

template <typename T>
T List<T>::pop_front()
{
	T result = firstPtr->data;
	if (count == 1)
		pop_back();
	if (count > 1)
	{
		Node<T> *trash = firstPtr;
		firstPtr = trash->next;
		firstPtr->prev = nullptr;
		delete trash;
		count--;
	}
	return result;
};

template <typename T>
void List<T>::insert_at(int i, T newData)
{
	Node<T> *newNode = new Node<T>;
	newNode->data = newData;
	if (firstPtr == nullptr)
		push_back(newData);
	if (count == 1)
		push_front(newData);
	if (i <= 0)
		push_front(newData);
	else
	{
		Node<T> *curr = firstPtr;
		int j = 1;
		while (curr->next and j <= i)
		{
			curr = curr->next;
			j++;
		}
		newNode->next = curr->next;
		newNode->prev = curr;
		curr->next = newNode;
		if (newNode->next)
			newNode->next->prev = newNode;
		count++;
	}
};

template <typename T>
T List<T>::remove_at(int i)
{
	T result;
	//	if(firstPtr == nullptr)
	//		return result;//wont accept return 0; since its an int :(
	if (count == 1 or i == 1) //was i <= 0 but took out since -1 return from find causin issues potentially
		return pop_front();
	else if (i >= count) //if i >= count
		return pop_back();
	else
	{
		Node<T> *trash = firstPtr;
		int j = 2;
		while (trash->next and j <= i)
		{
			trash = trash->next;
			j++;
		}
		result = trash->data;
		if (trash->next)
			trash->next->prev = trash->prev;
		if (trash->prev)
			trash->prev->next = trash->next;
		trash->prev = nullptr;
		trash->next = nullptr;
		delete trash;
		count--;
	}
	return result;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const List<T> &li)
{
	if (li.firstPtr)
	{
		out << li.firstPtr->data;
		Node<T> *curr = li.firstPtr->next;
		while (curr)
		{
			out << ", " << curr->data;
			curr = curr->next;
		}
	}
	else
		out << "*No Cards Available";
	return out;
};

////
//  Stack<T>
////
//
//  Stack.  Inherits from List.  Default behavior is last in first out (LIFO).
//

template <typename T>
class Stack : public List<T>
{
public:
	void push(T ndata)
	{
		List<T>::push_back(ndata);
	}
	T pop()
	{
		return List<T>::pop_back();
	}
	T peek() const
	{
		return List<T>::last();
	}
};

////
//  Queue<T>
////
//
//  Queue.  Inherits from List.  Default behavior is first in first out (FIFO).
//

template <typename T>
class Queue : public List<T>
{
public:
	void push(T ndata)
	{
		List<T>::push_back(ndata);
	}
	T pop()
	{
		return List<T>::pop_front();
	}
	T peek() const
	{
		return List<T>::first();
	}
};

////
//	gin_rummy
////
//

enum Val
{
	START,
	ACE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};
enum Suit
{
	SPADE,
	HEART,
	CLUB,
	DIAMOND
};

struct Card
{
	Suit suit;
	Card(){};
	Val value;
	Card(string s)
	{
		parse(s);
	};
	void parse(string);
	string to_string() const;
	bool operator==(const Card &other) const;
	friend std::ostream &operator<<(std::ostream &out, const Card &c);
	friend std::istream &operator>>(std::istream &in, Card &c);
};

bool Card::operator==(const Card &other) const
{
	return (suit == other.suit and value == other.value);
};

string Card::to_string() const
{
	string sValue, sSuit;
	switch (this->value)
	{
	case START:
		sValue = "to_string Error";
		break;
	case ACE:
		sValue = "A";
		break;
	case JACK:
		sValue = "J";
		break;
	case QUEEN:
		sValue = "Q";
		break;
	case KING:
		sValue = "K";
		break;
	case TWO:
		sValue = "2";
		break;
	case THREE:
		sValue = "3";
		break;
	case FOUR:
		sValue = "4";
		break;
	case FIVE:
		sValue = "5";
		break;
	case SIX:
		sValue = "6";
		break;
	case SEVEN:
		sValue = "7";
		break;
	case EIGHT:
		sValue = "8";
		break;
	case NINE:
		sValue = "9";
		break;
	case TEN:
		sValue = "10";
		break;
	}

	switch (this->suit)
	{
	case SPADE:
		sSuit = "s";
		break;
	case HEART:
		sSuit = "h";
		break;
	case CLUB:
		sSuit = "c";
		break;
	case DIAMOND:
		sSuit = "d";
		break;
	}
	string sTotal = sValue + sSuit;
	return sTotal;
}

void Card::parse(string s)
{
	char first = s.at(0);
	char second = s.at(s.length() - 1);

	switch (first)
	{
	case '1':
		this->value = TEN;
		break;
	case '2':
		this->value = TWO;
		break;
	case '3':
		this->value = THREE;
		break;
	case '4':
		this->value = FOUR;
		break;
	case '5':
		this->value = FIVE;
		break;
	case '6':
		this->value = SIX;
		break;
	case '7':
		this->value = SEVEN;
		break;
	case '8':
		this->value = EIGHT;
		break;
	case '9':
		this->value = NINE;
		break;
	case 'A':
		this->value = ACE;
		break;
	case 'a':
		this->value = ACE;
		break;
	case 'J':
		this->value = JACK;
		break;
	case 'j':
		this->value = JACK;
		break;
	case 'Q':
		this->value = QUEEN;
		break;
	case 'q':
		this->value = QUEEN;
		break;
	case 'K':
		this->value = KING;
		break;
	case 'k':
		this->value = KING;
		break;
	}

	switch (second)
	{
	case 's':
		this->suit = SPADE;
		break;
	case 'S':
		this->suit = SPADE;
		break;
	case 'h':
		this->suit = HEART;
		break;
	case 'H':
		this->suit = HEART;
		break;
	case 'd':
		this->suit = DIAMOND;
		break;
	case 'D':
		this->suit = DIAMOND;
		break;
	case 'c':
		this->suit = CLUB;
		break;
	case 'C':
		this->suit = CLUB;
		break;
	}
};

std::ostream &operator<<(std::ostream &out, const Card &c)
{
	switch (c.value)
	{
	case ACE:
		out << "A";
		break;
	case JACK:
		out << "J";
		break;
	case QUEEN:
		out << "Q";
		break;
	case KING:
		out << "K";
		break;
	default:
		out << c.value;
		break;
	}

	switch (c.suit)
	{
	case SPADE:
		out << "s";
		break;
	case HEART:
		out << "h";
		break;
	case CLUB:
		out << "c";
		break;
	case DIAMOND:
		out << "d";
		break;
	default:
		out << "c.suit error*";
		break;
	}
	return out;
};

std::istream &operator>>(std::istream &in, Card &c)
{
	string s;
	in >> s;
	c.parse(s);
	return in;
};

#endif
