#include<iostream>
#include<random>
#include<algorithm>
#include<vector>
#include<bitset>
#include"gin_rummy.h"
using namespace std;

void whoseTurn();
void playerOptions(List<Card>*, Stack<Card>&);
void execute(List<Card>*, Queue<Card>&, Stack<Card>&);
void discardDecision(List<Card>*, Stack<Card>&);
//Globals for ease of use
Card takenFromDiscard;
bool boolTakenFromDiscard = false;
bool turnSwap = true;
bool wasDiscarded = false;
bool firstTurn = true;

int main(){
    bool winCondition = false;
    string input;
    Queue<Card> deck;// QUEUE = DECK
    Stack<Card> discard;// STACK = DISCARD
    List<Card> hands[2];// LIST = HAND
    vector<string> temp =  {
							"As", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "Js", "Qs", "Ks",
                            "Ah", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "Jh", "Qh", "Kh",
                            "Ac", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "10c", "Jc", "Qc", "Kc",
                            "Ad", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "10d", "Jd", "Qd", "Kd"
							};
    random_shuffle(temp.begin(), temp.end());   //Randomly shuffles deck;

    for(string s:temp){
        Card c(s);
        deck.push(c); 
    }

	for(int i = 0; i < 10; i++){
		hands[1].push_back(deck.pop());
		hands[0].push_back(deck.pop());
	}

	discard.push(deck.pop());

    cout<<"Gin Rummy CSCI 41 Assignment"<<endl<<endl;
	while(!winCondition){
		whoseTurn();
		playerOptions(hands, discard);
	   	execute(hands, deck, discard);
	   	discardDecision(hands, discard);
		turnSwap = !turnSwap;
	}
	return 0;
}

void whoseTurn(){
    for(int i = 0; i < 100; i++){
        cout<<endl;
	}
	cout<<"Player "<<turnSwap<<"'s Turn"<<endl;
	cout<<"Press ENTER to Continue"<<endl;
	cin.get();
}

void playerOptions(List<Card>* hands, Stack<Card>& discard){
	if(boolTakenFromDiscard)
		cout<<"Player "<<!turnSwap<<" took the "<<takenFromDiscard<<" from the discard pile and discarded the "<<discard.peek()<<"."<<endl<<endl;

	else if(!boolTakenFromDiscard)
		cout<<discard.peek()<<" was added to the discard pile."<<endl<<endl;

	cout<<"Discard: "<<discard<<endl;
    cout<<"Upcard: "<<discard.peek()<<endl;
	cout<<"\nPlayer "<<turnSwap<<"'s Hand: "<<hands[turnSwap]<<endl;
	cout<<"\nOptions:"<<endl;
	cout<<"Take From Stock [D] "<<endl;	//Take top of stock
	cout<<"Take Discard\t[U] "<<endl<<endl;	//Take top of discard
	boolTakenFromDiscard = false;
}

void execute(List<Card>* hands, Queue<Card>& deck, Stack<Card>& discard){
    string takeDeckDisc;
    cout<<"> ";
    cin>>takeDeckDisc;
	if(takeDeckDisc == "D" or takeDeckDisc == "d"){
		hands[turnSwap].push_front(deck.pop());
	}
	else if(takeDeckDisc == "U" or takeDeckDisc == "u"){
		takenFromDiscard = discard.pop();	//Global card
		hands[turnSwap].push_front(takenFromDiscard);
		wasDiscarded = true;
		boolTakenFromDiscard = true;	//Global bool`
	}	
	else{
		cout<<"Invalid Input - Please Input Either 'D' or 'U'"<<endl;
		execute(hands, deck, discard);
	}
}	

void discardDecision(List<Card>* hands, Stack<Card>& discard){
	string input;
	Card remove;
	int indexNum = -1;
	while(indexNum == -1){
		cout<<"Choose a card to discard: "<<hands[turnSwap]<<endl<<"> ";
        cin>>input;
        remove.parse(input);
        indexNum = hands[turnSwap].find(remove);
	    if(indexNum == 1 and wasDiscarded){
			cout<<"Invalid Input - Cannot Discard Card From Discard."<<endl;
			indexNum = -1;
		}
		else if(indexNum == -1){
			cout<<"Invalid Input - Card Not Found."<<endl;
		}
	}
	discard.push(hands[turnSwap].remove_at(indexNum));	//FIXED
	wasDiscarded = false;
	cin.ignore();
}
