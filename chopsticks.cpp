//g++ -std=c++11 -O2 -Wall compprogtester.cpp -o compprogtester

//all positions are recorded as ABCD, A&B being the values of player hands and C&D being the values of ai's hands

#include <bits/stdc++.h> //basic nessecities for c++ programming including but not limited to iostream, vector, algorithm, etc.

using namespace std; //basic stuff

#define MAX_DEPTH 15

vector<int> position_5(int pos) {
    vector<int> out;
    for (int i = 0; i < 4; i++) {
        out.push_back((pos / (pow(10, i))) % 10);
    }
    return out;
}

vector<int> possible_moves(int pos, int turn) { //turns: 0 - ai, 1 - player
    vector<int> out;

    if (turn == 0) {
        out.push_back()
    }
}

int analyse_position(int pos, int turn, int depth) { //turns: 0 - ai, 1 - player
    if (depth > MAX_DEPTH) {return 0;}

    vector<int> all_digits = position_5(pos);

    if (all_digits[0] > 4 || all_digits[1] > 4) {
        return -999;
    } else if (all_digits[2] > 4 || all_digits[3] > 4) {
        return 999;
    }

    int best;
    if (turn == 1) {
        best = -999;
        for (auto p : possible_moves(pos, 1)) {
            best = max(best, analyse_position(p, 0, depth + 1));
        }
    } else {
        best = 999;
        for (auto p : possible_moves(pos, 0)) {
            best = min(best, analyse_position(p, 1, depth + 1));
        }
    }

    return best; //add function to respond with the best move too
}

int main() { //main function
    cout << "Starting chop-sticks game...";
    cout << "You go first...";

    int turn; //players turn will be the two values of your hands
    cin >> turn;

    
}