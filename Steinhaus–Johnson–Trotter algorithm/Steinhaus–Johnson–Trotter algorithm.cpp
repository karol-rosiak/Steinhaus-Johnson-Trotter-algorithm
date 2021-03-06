// Permutacja Heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>
#include <algorithm>

#define left 0
#define right 1

std::vector<int> createVector(int size) {
	std::vector<int> vec(size);
	//fills the vector with increasing numbers from 1 to vectors end
	std::iota(vec.begin(), vec.end(), 1);
	return vec;
}

void printVector(static std::vector<int>& tab) {
	for (auto e : tab) std::cout << e << " ";
	std::cout << std::endl;
}

void printDirections(static std::vector<int>& tab2) {
	for (auto e : tab2) e == left ? std::cout << "<" << " " : std::cout << ">" << " ";
	std::cout << std::endl;
}

int findMobile(static std::vector<int>& tab, static std::vector<int>& direction) {
	int maxIndex = -1;
	int maxValue = -1;

	for (int i = 0; i < tab.size(); i++) {
		//skip if the leftmost or rightmost elements are immobile
		if ((i == 0 && direction[i] == left) || (i == tab.size() - 1 && direction[i] == right))
			continue;
		else {
			if (direction[i] == left) {
				//check if the current element is greater than the left element and if it is largest mobile number
				if ((tab[i - 1] < tab[i]) && (maxValue <= tab[i])) {
					maxIndex = i;
					maxValue = tab[i];
				}
			}
			else { //if direction equals right
				//check if the current element is greater than the right element and if it is largest mobile number
				if ((tab[i + 1] < tab[i]) && (maxValue <= tab[i])) {
					maxIndex = i;
					maxValue = tab[i];
				}
			}
		}
	}
	//return currently highest mobile number, returns -1 if every number is immobile
	return maxIndex;
}

void calculatePermutations(int size, bool directions) {
	//create the base vector with increasing numbers
	std::vector<int> vec = createVector(size);

	//fill the vector with left directions
	std::vector<int> direction;
	direction.resize(size, left);

	//find first movable number
	int mobile = findMobile(vec, direction);

	while (mobile != -1) {
		directions == true ? printVector(vec), printDirections(direction) : printVector(vec);

		if (direction[mobile] == left) {
			//swap the movable number with left neighbour
			std::swap(vec[mobile - 1], vec[mobile]);
			std::swap(direction[mobile - 1], direction[mobile]);
			mobile--; //the movable number was moved one element to the left
		}
		else {
			//swap the mobile number with right neighbour
			std::swap(vec[mobile + 1], vec[mobile]);
			std::swap(direction[mobile + 1], direction[mobile]);
			mobile++; //the movable number was moved one element to the right
		}

		//change direction of every number that is greater than the current movable number
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] > vec[mobile])direction[i] = (!direction[i]);
		}

		//find new movable number
		mobile = findMobile(vec, direction);
	} //-1 equals no movable numbers left

	//show last permutation
	directions == true ? printVector(vec), printDirections(direction) : printVector(vec);

}

int main(int argc, char * argv[])
{
	int n = 0;
	char directions = 'n';
	std::cout << "How many numbers?" << std::endl;
	std::cin >> n;
	
	std::cout << "With directions? (y/n)" << std::endl;
	std::cin >> directions;
	
	directions == 'y' ? calculatePermutations(n, true) : calculatePermutations(n, false);
	
	system("pause");
	return 0;
}