//
//  main.cpp
//  DSFinalProject
//
//  Created by Mehrshid Fadaei Nejad on 3/25/1394 AP.
//  Copyright (c) 1394 Mehrshid Fadaei Nejad. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>


using namespace std;

typedef int value;
#define MAX (1+(1<<6))
value scoreArray [100];
value awardArray [100];
value sellArray [100];
value lazyMin[MAX];
value lazyMax[MAX];



struct cell {
	
	value award;
	value sell;
	value score;
	string name;
	long long sum;
};


cell arrayforQuery[MAX];
cell maxTree[MAX];
cell minTree[MAX];


class Node {
	
public:
	
	value indexData;
	
	Node *leftChild;
	Node *rightChild;
	
	Node(value);
	Node();
};



class SegmentTree {
	
public:
	
	Node* root;
	Node* key;
	
	
	
	void buildMinTree(value, value, value, cell[],char);
	void buildMaxTree(value, value, value, cell[],char);
	void updateMinTree(value, value, value, value, value, char);
	void updateMaxTree(value, value, value, value, value, char);
	value queryTreeforSell(value, value, value,value, value, cell[], string);
	value queryTreeforAwards(value, value, value,value, value, cell[], string);
	value queryTreeforScore(value, value, value,value, value, cell[], string);
	
	
	
};



void SegmentTree::buildMinTree(value data, int i, int j, cell arr[MAX], char command) {
	
	
	if (i > j)
		return;
	
	
	if (i == j) {
		
		minTree[data] = arr[i];
		return;
	}
	
	buildMinTree(data*2, i, (i+j)/2, arr,command);			// Init left child
	buildMinTree(data*2+1, 1+(i+j)/2, j, arr,command);		// Init right child
	
	if ( command == 's' )
		minTree[data].sell = min(minTree[data*2].sell, minTree[data*2+1].sell); // Init root value
	else if ( command == 'c' )
		minTree[data].score = min(minTree[data*2].score, minTree[data*2+1].score); // Init root value
	else if ( command == 'r' )
		minTree[data].award = min(minTree[data*2].award, minTree[data*2+1].award); // Init root value
}


void SegmentTree::buildMaxTree(value data, int i, int j, cell arr[MAX], char command) {
	
	
	if (i > j)
		return;
	
	
	if (i == j) {
		
		maxTree[data] = arr[i];
		return;
	}
	
	buildMaxTree(data*2, i, (i+j)/2, arr,command);			// Init left child
	buildMaxTree(data*2+1, 1+(i+j)/2, j, arr,command);		// Init right child
	
	if ( command == 's' )
		maxTree[data].sell = max(minTree[data*2].sell, minTree[data*2+1].sell);		// Init root value
	else if ( command == 'c' )
		maxTree[data].score = max(minTree[data*2].score, minTree[data*2+1].score);	// Init root value
	else if ( command == 'r' )
		maxTree[data].award = max(minTree[data*2].award, minTree[data*2+1].award);	// Init root value
	
	
}


void SegmentTree::updateMinTree(value newData, value node, value j, value a, value b, char command) {
	
	
	//	if(lazyMin[node] != 0) {			// This node needs to be updated
	//		minTree[node] += lazyMin[node]; // Update it
	
	//		if(a != b) {
	//			lazyMin[node*2] += lazyMin[node];	// Mark child as lazy
	//			lazyMin[node*2+1] += lazyMin[node]; // Mark child as lazy
	//		}
	//		lazyMin[node] = 0;				// Reset it
	//	}
	
	
	if (a == b) {
		if ( command == 's' )
			minTree[node].sell = newData;
		else if ( command == 'c' )
			minTree[node].score = newData;
		else if ( command == 'r' )
			minTree[node].award = newData;
		return;
	}
	
	
	else {
		
		value mid = (int)floor((double)(a+b)/2);
		if ( mid >= j)
			updateMinTree(newData,node*2, j, a, mid, command);		// Updating Left Child
		
		if ( mid < j)
			updateMinTree(newData,node*2+1, j, mid, b, command);	// Updating Right Child
		
	}
	
	if ( command == 's' )
		minTree[node].sell = min(minTree[2*node].sell, minTree[2*node+1].sell);
	if ( command == 'c' )
		minTree[node].score = min(minTree[2*node].score, minTree[2*node+1].score);
	if ( command == 'r' )
		minTree[node].award = min(minTree[2*node].award, minTree[2*node+1].award);
	
	
}


void SegmentTree::updateMaxTree(value newData, value node, value j, value a, value b, char command) {
	
	
	if (a == b) {
		if (newData == node) {
			if ( command == 's' )
				minTree[node].sell = newData;
			else if ( command == 'c' )
				minTree[node].score = newData;
			else if ( command == 'r' )
				minTree[node].award = newData;
			return;
		}
	}
	
	else {
		value mid = (int)floor((double)(a+b)/2);
		if ( mid >= j)
			updateMaxTree(newData,node*2, j, a, mid, command);
		
		if ( mid <= j)
			updateMaxTree(newData,node*2+1, j, mid, b, command);
		
	}
	
	if ( command == 's' )
		maxTree[node].sell = max(maxTree[2*node].sell, maxTree[2*node+1].sell);
	if ( command == 'c' )
		maxTree[node].score = max(maxTree[2*node].score, maxTree[2*node+1].score);
	if ( command == 'r' )
		maxTree[node].award = max(maxTree[2*node].award, maxTree[2*node+1].award);
}


value SegmentTree::queryTreeforSell(value i, value j, value a, value b, value node, cell arr[], string msg) {
	
	value result;
	
	if ( i >= a || j >= b)
		return 0;
	
	
	if ( msg == "max") {
		
		if (a >= i && b <= j) {
			cout << "Name of the Movie is: "<< arr[node].name;
			return arr[node].sell; // data is found
		}
		
		else {
			//value avg = a+b/2;
			value result = 0;
			//if (avg >= i && a <= j)
			result = max(result,queryTreeforSell(i, j, a, a+b/2, node*2, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = max(result,queryTreeforSell(i, j, a+b/2, b, node*2+1, arr, msg));
			
			
			return result;
		}
		
		
	}
	
	if ( msg == "min") {
		
		if (a >= i && b <= j) {
			cout << "Name of the Movie is: "<< arr[node].name;
			return arr[node].sell; // data is found
		}
		
		else {
			//value avg = a+b/2;
			value result = MAX;
			//if (avg >= i && a <= j)
			result = min(result,queryTreeforSell(i, j, a+b/2, b, node*2+1, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = min(result,queryTreeforSell(i, j, a+b/2, b, node*2+1, arr, msg));
			
		}
	}
	
	
	if ( msg == "sum" ) {
		
		if (a >= i && b <= j)
			return result;
		
		
		else {
			
			result = result + queryTreeforSell(i, j, a, a+b/2, node*2, arr, msg);
			result = result + queryTreeforSell(i, j, a+b/2, b, node*2+1, arr, msg);
			
			
		}
	}
	
	
	return result;
	
}


value SegmentTree::queryTreeforAwards(value i, value j, value a, value b, value node, cell arr[], string msg) {
	
	value result;
	
	if ( i >= a || j >= b)
		return 0;
	
	
	if ( msg == "max") {
		
		if (a >= i && b <= j) {
			cout << "Name of the Movie is: "<< arr[node].name;
			
			return arr[node].award; // data is found
		}
		
		else {
			//value avg = a+b/2;
			value result = 0;
			//if (avg >= i && a <= j)
			result = max(result, queryTreeforAwards(i, j, a, a+b/2, node*2, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = max(result, queryTreeforAwards(i, j, a+b/2, b, node*2+1, arr, msg));
			
			return result;
		}
	}
	
	if ( msg == "min") {
		
		if (a >= i && b <= j)
			return arr[node].award; // data is found
		
		
		else {
			//value avg = a+b/2;
			value result = MAX;
			//if (avg >= i && a <= j)
			result = min(result,queryTreeforAwards(i, j, a+b/2, b, node*2+1, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = min(result,queryTreeforAwards(i, j, a+b/2, b, node*2+1, arr, msg));
			
		}
	}
	
	if ( msg == "sum" ) {
		
		if (a >= i && b <= j) {
			cout << "Name of the Movie is: "<< arr[node].name;
			return result;
		}
		
		else {
			
			result = result + queryTreeforAwards(i, j, a, a+b/2, node*2, arr, msg);
			result = result + queryTreeforAwards(i, j, a+b/2, b, node*2+1, arr, msg);
		}
	}
	
	return result;
	
}


value SegmentTree::queryTreeforScore(value i, value j, value a, value b, value node, cell arr[], string msg) {
	
	value result;
	
	if ( i >= a || j >= b)
		return 0;
	
	
	if ( msg == "max") {
		
		if (a >= i && b <= j) {
			
			cout << "Name of the Movie is: "<< arr[node].name;
			return arr[node].score; // data is found
		}
		
		else {
			//value avg = a+b/2;
			value result = 0;
			//if (avg >= i && a <= j)
			result = max(result,queryTreeforScore(i, j, a, a+b/2, node*2, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = max(result,queryTreeforScore(i, j, a+b/2, b, node*2+1, arr, msg));
			
			return result;
		}
		
		
	}
	
	if ( msg == "min") {
		
		if (a >= i && b <= j) {
			cout << "Name of the Movie is: "<< arr[node].name;
			
			return arr[node].score; // data is found
		}
		
		else {
			//value avg = a+b/2;
			value result = MAX;
			//if (avg >= i && a <= j)
			result = min(result,queryTreeforScore(i, j, a, a+b/2, node*2, arr, msg));
			
			//if (avg+1 <= j && b >= i)
			result = min(result,queryTreeforScore(i, j, a+b/2, b, node*2+1, arr, msg));
			
		}
		
	}
	
	if ( msg == "sum" ) {
		
		if (a >= i && b <= j)
			return result;
		
		
		else {
			
			result = result + queryTreeforScore(i, j, a, a+b/2, node*2, arr, msg);
			result = result + queryTreeforScore(i, j, a+b/2, b, node*2+1, arr, msg);
			
			
		}
	}
	
	return result;
	
}




int main(int argc, const char * argv[]) {
	
	value numofMovies, numofAwards, scoreofMovie, sellofMovie;
	//string nameofMovie, input, query;
	string edit = "edit";
	string ask = "ask";
	string nameofMovie;
	
	SegmentTree genMinTree;
	SegmentTree genMaxTree;
	
	cout << endl << endl;
	
	cout << "How Many Movies Do You Wanna Add to IMDB Film Collection?" << endl;
	cin >> numofMovies;
	
	cout << "You Should Enter Your Inputs With THIS Order: " << endl;
	cout << " Name of the Movie, Score of the Movie, Number of Awards of the Movie and Sell of the Movie" << endl << endl;
	
	string line1;
	
	for (int i = 0; i < numofMovies; i++) {
		
		//std::getline(std::cin, line1);
		
		string input;
		istringstream ss ( input );
		cin >> nameofMovie;
		cin >> scoreofMovie >> numofAwards >> sellofMovie;
		arrayforQuery[i].name = nameofMovie;
		arrayforQuery[i].score = scoreofMovie;
		arrayforQuery[i].award = numofAwards;
		arrayforQuery[i].sell = sellofMovie;
	}
	
	genMinTree.buildMinTree(1, 1, numofMovies, arrayforQuery,'s');
	genMaxTree.buildMaxTree(1, 1, numofMovies, arrayforQuery, 's');
	
	genMinTree.buildMinTree(1, 1, numofMovies, arrayforQuery,'c');
	genMaxTree.buildMaxTree(1, 1, numofMovies, arrayforQuery, 'c');
	
	
	genMinTree.buildMinTree(1, 1, numofMovies, arrayforQuery, 'r');
	genMaxTree.buildMaxTree(1, 1, numofMovies, arrayforQuery, 'r');
	
	
	
	string input;
	istringstream ss ( input );
	string token;
	
	//while (true) {
	
	cout << "press e for exit" << endl;
	cout << "What Query Do You Wanna Edit? " << endl;
	cout << "Input Example: edit 1 score 8.3" << endl;
	
	
	value ask1, ask2, editWhich, newData;
	string msgscore;
	string maxmsg;
	string whichMsgQuery, msgQuery;
	string msg;
	cin >> msg;
	
	
	if ( msg == "edit" ) {
		cin >> editWhich;
		cin >> msgQuery;
		cin >> newData;
		
		if (msgQuery == "sell" || msgQuery == "Sell") {
			
			genMinTree.updateMinTree(newData, arrayforQuery[editWhich].sell, editWhich ,1 , numofMovies, 's');
			genMaxTree.updateMaxTree(newData, arrayforQuery[editWhich].sell, editWhich ,1 , numofMovies, 's');
		}
		
		if (msgQuery == "score" || msgQuery == "Score") {
			
			genMinTree.updateMinTree(newData, 1, editWhich ,1 , numofMovies, 'c');
			genMaxTree.updateMaxTree(newData, 1, editWhich ,1 , numofMovies, 'c');
		}
		
		if (msgQuery == "reward" || msgQuery == "Reward") {
			
			genMinTree.updateMinTree(newData, arrayforQuery[editWhich].award, editWhich ,1 , numofMovies, 'r');
			genMaxTree.updateMaxTree(newData, arrayforQuery[editWhich].award, editWhich ,1 , numofMovies, 'r');
		}
		
		
	}
	else if ( msg == "ask" ) {
		cin >> ask1 >> ask2 >> msgQuery >> whichMsgQuery;
		
		if (msgQuery == "sell" || msgQuery == "Sell") {
			genMinTree.queryTreeforSell(ask1, ask2, 1, numofMovies, 1, arrayforQuery, whichMsgQuery);
			genMaxTree.queryTreeforSell(ask1, ask2, 1, numofMovies, 1, arrayforQuery, whichMsgQuery);
		}
		
		if (msgQuery == "cost" || msgQuery == "Cost") {
			genMinTree.queryTreeforSell(ask1, ask2, 1, numofMovies, 1, arrayforQuery, whichMsgQuery);
			genMinTree.queryTreeforSell(ask1, ask2, 1, numofMovies, 1, arrayforQuery, whichMsgQuery);
		}
		
	}
	
	//}
	
	return 0;
}
