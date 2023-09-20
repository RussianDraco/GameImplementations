//g++ -std=c++11 -O2 -Wall compprogtester.cpp -o compprogtester

//all positions are recorded as ABCD, A&B being the values of player hands and C&D being the values of ai's hands

#include <bits/stdc++.h> //basic nessecities for c++ programming including but not limited to iostream, vector, algorithm, etc.

using namespace std; //basic stuff

#define MAX_DEPTH 15

vector<char> chr_positions(string pos) {
    vector<char> out;
    for (char c : pos) {
        out.push_back(c);
    }
    return out;
}

vector<string> possible_moves(string pos, int turn) { //turns: 0 - ai, 1 - player
    vector<string> out;

    if (turn == 0) {
        out.push_back()
    }
}

int hand_advantage(string pos, bool return_sum) { //returns `ai_lost_hands * 10 + player_lost_hands`
    int out = 0;

    if (pos[0] == '-') {
        out++;
    }
    if (pos[1] == '-') {
        out++;
    }
    if (pos[2] == '-') {
        out+=10;
    }
    if (pos[3] == '-') {
        out+=10;
    }

    if (return_sum) {
        return out + (out % 10);
    } else {
        return out;
    }
}

int analyse_position(string pos, int turn, int depth) { //turns: 0 - ai, 1 - player
    if (depth > MAX_DEPTH) {return hand_advantage(pos, true);}

    vector<char> all_digits = chr_positions(pos);

    if (all_digits[0] > 4 || all_digits[1] > 4) {
        return -999;
    } else if (all_digits[2] > 4 || all_digits[3] > 4) {
        return 999;
    }

    if (isdigit(all_digits[0])) {
        if ((all_digits[0] - '0') > 4) {
            pos[0] = '-';
        }
    } else if (isdigit(all_digits[1])) {
        if ((all_digits[1] - '0') > 4) {
            pos[1] = '-';
        }
    } else if (isdigit(all_digits[2])) {
        if ((all_digits[2] - '0') > 4) {
            pos[2] = '-';
        }
    } else if (isdigit(all_digits[3])) {
        if ((all_digits[3] - '0') > 4) {
            pos[3] = '-';
        }
    }

    int hnd_advs = hand_advantage(pos, false);

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