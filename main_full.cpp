#include<iostream>
#include<random>
#include<algorithm>
#include<vector>
#include<bitset>
#include"gin_rummy.h"
using namespace std;

void whoseTurn();
void playerOptions(List<Card>*, Queue<Card>&, Stack<Card>&);
void execute(List<Card>*, Queue<Card>&, Stack<Card>&, bool&);
void discardDecision(List<Card>*, Stack<Card>&, bool&);
void checkWinCondition(List<Card>*, bool&);
//void checkWinCondition(List<Card>, bool&);
void endTurn();

Card takenFromDiscard;
bool boolTakenFromDiscard = false;
bool turnSwap = true;

int main(){
    	bool winCondition = false;
    	bool wasDiscarded = false;
   	string input;
    	Queue<Card> deck;// QUEUE = DECK
    	Stack<Card> discard;// STACK = DISCARD
    	List<Card> hands[2];// LIST = HAND
	List<Card> test;
    	vector<string> temp =  {
			"As", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "Js", "Qs", "Ks",
                       	"Ah", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "Jh", "Qh", "Kh",
                       	"Ac", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "10c", "Jc", "Qc", "Kc",
                       	"Ad", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "10d", "Jd", "Qd", "Kd",
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
	   	playerOptions(hands, deck, discard);
	   	execute(hands, deck, discard, wasDiscarded);
	   	discardDecision(hands, discard, wasDiscarded);
		checkWinCondition(hands, winCondition);
		turnSwap = !turnSwap;
	}
	return 0;
}

void whoseTurn(){	//couts simple statement, waits for user response
	for(int i = 0; i < 60; i++){
		 cout<<endl;
	}
	cout<<"Player "<<turnSwap<<"'s Turn"<<endl;
	cout<<"Press ENTER to Continue"<<endl;
	cin.get();
}

void playerOptions(List<Card>* hands, Queue<Card>& deck, Stack<Card>& discard){ //
	if(boolTakenFromDiscard)
        cout<<"Player "<<!turnSwap<<" took the "<<takenFromDiscard<<" from the discard pile and discarded the "<<discard.peek()<<"."<<endl<<endl;
    else if(!boolTakenFromDiscard)
        cout<<"Player "<<!turnSwap<<" took a card from stock and discarded "<<discard.peek()<<"."<<endl<<endl;
    cout<<"Discard: "<<discard<<endl;
    cout<<"Upcard: "<<discard.peek()<<endl;
    cout<<"\nPlayer "<<turnSwap<<"'s Hand: "<<hands[turnSwap]<<endl;
    cout<<"\nOptions:"<<endl;
    cout<<"Take From Stock [D] "<<endl; //Take top of stock
    cout<<"Take Discard\t[U] "<<endl<<endl; //Take top of discard
    boolTakenFromDiscard = false;

}

void execute(List<Card>* hands, Queue<Card>& deck, Stack<Card>& discard, bool& wasDiscarded){
	string takeDeckDisc;
	cout<<"> ";
	cin>>takeDeckDisc;
	if(takeDeckDisc == "D" or takeDeckDisc == "d"){
		hands[turnSwap].push_front(deck.pop());
	}
	else if(takeDeckDisc == "U" or takeDeckDisc == "u"){
		takenFromDiscard = discard.pop();	//global card
		hands[turnSwap].push_front(takenFromDiscard);
		wasDiscarded = true;
		boolTakenFromDiscard = true;	//global bool
	}
	else{	//recursively call execute if invalid input, might need to change to prevent stack overflow... 
		cout<<"Invalid Input - Please Input Either 'D' or 'U'"<<endl;
		execute(hands, deck, discard, wasDiscarded);
	}
}

void discardDecision(List<Card>* hands, Stack<Card>& discard, bool& wasDiscarded){
    string input;
    Card remove;
    int indexNum = -1;
    while(indexNum == -1){
        cout<<"Choose a card to discard: "<<hands[turnSwap]<<endl<<"> ";
        cin>>input;
        remove.parse(input);
        indexNum = hands[turnSwap].find(remove);
        if(indexNum == 1 and wasDiscarded){	//if player tries to discard card just pulled from discard pile
            cout<<"Invalid Input - Cannot Discard Card From Discard."<<endl;
            indexNum = -1;
        }
        else if(indexNum == -1){	//player attempts invalid input
            cout<<"Invalid Input - Card Not Found."<<endl;
        }
    }
    discard.push(hands[turnSwap].remove_at(indexNum));  //FIXED
    wasDiscarded = false;
    cin.ignore();
}


//EXTRA CREDIT ATTEMPT

//assigns binary value to card and puts into appropriate suit
void bitParser(string sTemp, bitset<13>& spades, bitset<13>& diamonds, bitset<13>& clubs, bitset<13>& hearts){
	bitset<13> tempValue;
	char cValue = sTemp.at(0);
	char cSuit = sTemp.at(sTemp.size() - 1);
    switch(cValue){
        case 'A':
            tempValue[0] = 1;
            break;
        case '2':
            tempValue[1] = 1;
            break;
        case '3':
            tempValue[2] = 1;
            break;
        case '4':
            tempValue[3] = 1;
            break;
        case '5':
		tempValue[4] = 1;
            break;
        case '6':
            tempValue[5] = 1;
            break;
        case '7':
            tempValue[6] = 1;
            break;
        case'8':
            tempValue[7] = 1;
            break;
        case '9':
            tempValue[8] = 1;
            break;
        case '1':
            tempValue[9] = 1;
            break;
        case 'J':
            tempValue[10] = 1;
            break;
		case 'Q':
            tempValue[11] = 1;
            break;
        case 'K':
            tempValue[12] = 1;
            break;
    }
	switch(cSuit){
		case 's':
			spades |= tempValue;
			break;
		case 'd':
			diamonds |= tempValue;
			break;
		case 'c':
			clubs |= tempValue;
			break;
		case 'h':
			hearts |= tempValue;
			break;
	}
	 cout<<sTemp<<": "<<tempValue<<endl;
	 tempValue.reset();
}

int check_runs(bitset<13>currSuit){
	int totalCardsUsed = 0;
	int i = 0;
	while(i < 13){
//all possible run combinations
	bitset<13> check7 = 7;	//111 b2 equiv
	bitset<13> check15 = 15;	//1111
	bitset<13> check31 = 31;	//11111
	bitset<13> check63 = 63;
	bitset<13> check127 = 127;
	bitset<13> check255 = 255;
	bitset<13> check511 = 511;
	bitset<13> check1023 = 1023;
//Compares the runs with current hand(spades, diam...)
	check7 &= currSuit;	
	check15 &= currSuit;
	check31 &= currSuit;
	check63 &= currSuit;
	check127 &= currSuit;
	check255 &= currSuit;
	check511 &= currSuit;
	check1023 &= currSuit;
		if(check1023 == 1023){
			currSuit >>= 10;
			i += 10;
			cout<<"a run of 10 found"<<endl;
			totalCardsUsed += 10;
		}
		else if(check511 == 511){
			currSuit >>= 9;
			i += 9;
			cout<<"a run of 9 found"<<endl;
			totalCardsUsed += 9;
		}
		else if(check255 == 255){
			currSuit >>= 8;
			i += 8;
			cout<<"a run of 8 found"<<endl;
			totalCardsUsed += 8;
		}
		else if(check127 == 127){
			currSuit >>= 7;
			i += 7;
			cout<<"a run of 7 found"<<endl;
			totalCardsUsed += 7;
		}
		else if(check63 == 63){
			currSuit >>= 6;
			i += 6;
			cout<<"a run of 6 found"<<endl;
			totalCardsUsed += 6;
		}
		else if(check31 == 31){
			currSuit >>= 5;
			i += 5;
			cout<<"a run of 5 found"<<endl;
			totalCardsUsed += 5;
		}
		else if(check15 == 15){
			currSuit >>= 4;
			i += 4;
			cout<<"a run of 4 found"<<endl;
			totalCardsUsed += 4;
		}
		else if(check7 == 7){
			currSuit >>= 3;
			i += 3;
			cout<<"a run of 3 found"<<endl;
			totalCardsUsed += 3;
		}
		else{
		currSuit >>= 1;
		i++;
		}
	}
	return totalCardsUsed;
}

int check_melds(bitset<13> s, bitset<13> d, bitset<13> c, bitset<13> h){	
//checks for melds by ANDing at least 3 suits together. 
//If a meld exists then a 1 will appear in set
//If no melds exists then the whole set will be 0s
	int totalCardsUsed = 0;
	bitset<13> firstDigitCheck = 1;	//need this bit to avoid bug of having multiple melds causing bug 
 	bitset<13> sdc = s & d & c;
        bitset<13> sdh = s & d & h;
        bitset<13> dch = d & c & h;
        bitset<13> sch = s & c & h;
        bitset<13> shcd = s & h & c & d;
	if(sdc == 0 && sdh == 0 && dch == 0 && sch == 0 && shcd == 0)
		return 0;
        for( int i = 0; i < 13; i++){
//ANDs the meld suit with bitset who only has nonzero digit at beggining 
//then shifts the bitset one by one checking all possible combinations for 1
//if 1 is found, add 3 or 4 to int totalCardsUsed
//		cout<<"i value: "<<i<<endl;
		bitset<13> sdc = s & d & c;
        	bitset<13> sdh = s & d & h;
	        bitset<13> dch = d & c & h;
        	bitset<13> sch = s & c & h;
	        bitset<13> shcd = s & h & c & d;
		bitset<13> m4shcd = shcd & firstDigitCheck;
		bitset<13> m3sdc = sdc & firstDigitCheck;
		bitset<13> m3sdh = sdh & firstDigitCheck;
		bitset<13> m3dch = dch & firstDigitCheck;
		bitset<13> m3sch = sch & firstDigitCheck;
	
/*
 * validating purposes
		cout<<"m4: "<<m4shcd<<endl;
		cout<<"sdc: "<<m3sdc<<endl;
		cout<<"sdh: "<<m3sdh<<endl;
		cout<<"dch: "<<m3dch<<endl;
		cout<<"sch: "<<m3sch<<endl;
*/
		if(m4shcd== 1){
			cout<<"meld of 4 found at bit "<<i<<endl;
			totalCardsUsed += 4;
		}
		else if(m3sdc == 1 or m3sdh == 1 or m3dch == 1 or m3sch == 1){
			totalCardsUsed += 3;
			cout<<"meld of 3 found at bit "<<i<<endl;
		}
		s >>= 1;
		d >>= 1;
		c >>= 1;
		h >>= 1;
	}
	return totalCardsUsed;
}

//does the condition statements for winning
void checkWinCondition(List<Card>* hands, bool& winCondition){
	int sumOfCards = 0;
	int i = 0;
	bitset<13> s, d, c, h;	
	Card currCard;
	Node<Card>* currCardPtr = hands[turnSwap].firstNode();
	while(i < 10){	//translates the card value into bitset values
 		currCard = currCardPtr->data;	//gets the value of the card i.e "Ks"
		bitParser(currCard.to_string(), s, d, c, h); //sends to funcion to be assigned bitset
		currCardPtr = currCardPtr->next;	//moves to next card in hand
		i++;
	}
	//removes any cards that aren't in a meld of at least three
	bitset<13> sdc = s & d & c;
	bitset<13> sdh = s & d & h;
	bitset<13> sch = s & c & h;
	bitset<13> dch = d & c & h;
	bitset<13> sdch = s & d & c & h;
	bitset<13>total = s|d|c|h;
//	cout<<"Combination of Melds"<<endl<<"sdc: "<<sdc<<endl<<"sdh: "<<sdh<<endl<<"sch: "<<sch<<endl<<"dch: "<<dch<<endl<<endl<<"sdch: "<<sdch<<endl;
	cout<<"The Binary Representation of Player Hand by Suit & Combined"<<endl<<"s: "<<s<<endl<<"d: "<<d<<endl<<"c: "<<c<<endl<<"h: "<<h<<endl<<endl<<"T: "<<total<<endl;

	sumOfCards += check_melds(s, d, c, h);
	//removes melds from runs to prevent double counting bug
	//does this by XORing the suit by bitset that contains only the melds
	h ^= sch;
	h ^= sdh;
	h ^= dch;
	s ^= sdc;
	s ^= sdh;
	s ^= sch;
	d ^= sdc;
        d ^= sdh;
        d ^= dch;
        c ^= sdc;
        c ^= sch;
        c ^= dch;
	sumOfCards += check_runs(s); 
	sumOfCards += check_runs(d);
	sumOfCards += check_runs(c);
	sumOfCards += check_runs(h);
	cout<<"Sum Of Cards: "<<sumOfCards<<endl<<endl;
    cout<<endl<<"The Binary Representation of Player Hand by Suit & Combined"<<endl<<"s: "<<s<<endl<<"d: "<<d<<endl<<"c: "<<c<<endl<<"h: "<<h<<endl<<endl<<"T: "<<total<<endl;
	if(sumOfCards >= 10){
		winCondition = true;
		cout<<"Player "<<turnSwap<<" Won!\n\nEnding Game."<<endl;
	}
	else winCondition = false;
}

