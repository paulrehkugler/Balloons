/*
 * balloons.cpp
 *
 *  Created on: Mar 30, 2011
 *      Author: Paul
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>

struct team{
	int dA;
	int dB;
	int diff;
	int balloons;
};

bool operator<(const team& A, const team& B){
	if (abs(A.diff) > abs(B.diff))		// if diff is large there is a strong preference to take from room A or B
		return true;					// therefore, sort from highest diffs to lowest
	else
		return false;
}

int solve(std::vector<team> teams, int A, int B){
	int retval = 0;
	std::sort(teams.begin(), teams.end());
	for (unsigned int i = 0; i < teams.size(); ++i){
		if (teams[i].diff < 0){		// then A is more advantageous to take balloons from
			int balloons_from_a = teams[i].balloons;
			int balloons_from_b = 0;
			A -= teams[i].balloons;
			teams[i].balloons = 0;
			if (A < 0){
				B += A;	// take balloons from B instead
				balloons_from_a += A;	// these balloons weren't taken from A
				balloons_from_b -= A;	// these balloons were taken from B
				A = 0;
			}
			retval += balloons_from_a * teams[i].dA + balloons_from_b * teams[i].dB;
		}
		else if (teams[i].diff > 0){		// then B is more advantageous to take balloons from
			int balloons_from_b = teams[i].balloons;
			int balloons_from_a = 0;
			B -= teams[i].balloons;
			teams[i].balloons = 0;
			if (B < 0){
				A += B;	// take balloons from A instead
				balloons_from_b += B;	// these balloons weren't taken from B
				balloons_from_a -= B;	// these balloons were taken from A
				B = 0;
			}
			retval += balloons_from_a * teams[i].dA + balloons_from_b * teams[i].dB;
		}
	}
	return retval;
}

int main(){
	int N, A, B;
	while(true){
		std::cin >> N >> A >> B;
		if (N == 0 && A == 0 && B == 0)
			return 0;
		std::vector<team> teams;
		for (int i = 0; i < N; ++i){
			team temp_team;
			std::cin >> temp_team.balloons >> temp_team.dA >> temp_team.dB;
			temp_team.diff = temp_team.dA - temp_team.dB;
			teams.push_back(temp_team);
		}
		std::cout << solve(teams, A, B) << std::endl;
	}
}
