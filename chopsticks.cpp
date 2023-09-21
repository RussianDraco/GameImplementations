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
    vector<char> all_digits = chr_positions(pos);
    int player_hands[2] = {-1, -1};
    int ai_hands[2] = {-1, -1};

    if (isdigit(all_digits[0])) {
        player_hands[0] = all_digits[0] - '0';
    } else if (isdigit(all_digits[1])) {
        player_hands[1] = all_digits[1] - '0';
    } else if (isdigit(all_digits[2])) {
        ai_hands[0] = all_digits[2] - '0';
    } else if (isdigit(all_digits[3])) {
        ai_hands[1] = all_digits[3] - '0';
    }

    if (turn == 0) { //ai's turn
        //self moves
        int sum_of_hands = ai_hands[0] + ai_hands[1];

        for (int j = 0; j < floor(sum_of_hands / 2); j++) {
            if ((j > 4) || ((sum_of_hands - j) > 4)) {continue;}

            ostringstream oss;
            for (int num : {player_hands[0], player_hands[1], sum_of_hands - j, j}) {
                oss << num;
            }

            out.push_back(oss.str());
        }

        //attack moves
        out.push_back(to_string(player_hands[0] + ai_hands[0]) + to_string(player_hands[1]) + to_string(ai_hands[0]) + to_string(ai_hands[1]));
        out.push_back(to_string(player_hands[0] + ai_hands[1]) + to_string(player_hands[1]) + to_string(ai_hands[0]) + to_string(ai_hands[1]));
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1] + ai_hands[0]) + to_string(ai_hands[0]) + to_string(ai_hands[1]));
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1] + ai_hands[1]) + to_string(ai_hands[0]) + to_string(ai_hands[1]));
    } else {
        //self moves
        int sum_of_hands = player_hands[0] + player_hands[1];

        for (int j = 0; j < floor(sum_of_hands / 2); j++) {
            if ((j > 4) || ((sum_of_hands - j) > 4)) {continue;}

            ostringstream oss;
            for (int num : {sum_of_hands - j, j, ai_hands[0], ai_hands[1]}) {
                oss << num;
            }

            out.push_back(oss.str());
        }

        //attack moves
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1]) + to_string(ai_hands[0] + player_hands[0]) + to_string(ai_hands[1]));
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1]) + to_string(ai_hands[0] + player_hands[1]) + to_string(ai_hands[1]));
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1]) + to_string(ai_hands[0]) + to_string(ai_hands[1] + player_hands[0]));
        out.push_back(to_string(player_hands[0]) + to_string(player_hands[1]) + to_string(ai_hands[0]) + to_string(ai_hands[1] + player_hands[1]));
    }

    return out;
}

int hand_advantage(string pos, bool return_sum) { //returns `ai_lost_hands * 10 + player_lost_hands`
    int out = 0;

    if (pos[0] == '0') {
        out++;
    }
    if (pos[1] == '0') {
        out++;
    }
    if (pos[2] == '0') {
        out+=10;
    }
    if (pos[3] == '0') {
        out+=10;
    }

    if (return_sum) {
        return out - (out % 10);
    } else {
        return out;
    }
}

int analyse_position(string pos, int turn, int depth) { //turns: 0 - ai, 1 - player
    if (depth > MAX_DEPTH) {return hand_advantage(pos, true);}

    vector<char> all_digits = chr_positions(pos);

    if (all_digits[0] > 4 || all_digits[1] > 4) {
        return -99;
    } else if (all_digits[2] > 4 || all_digits[3] > 4) {
        return 99;
    }

    if (isdigit(all_digits[0])) {
        if ((all_digits[0] - '0') > 4) {
            pos[0] = '0';
        }
    } else if (isdigit(all_digits[1])) {
        if ((all_digits[1] - '0') > 4) {
            pos[1] = '0';
        }
    } else if (isdigit(all_digits[2])) {
        if ((all_digits[2] - '0') > 4) {
            pos[2] = '0';
        }
    } else if (isdigit(all_digits[3])) {
        if ((all_digits[3] - '0') > 4) {
            pos[3] = '0';
        }
    }

    int hnd_advs = hand_advantage(pos, false);
    if (hnd_advs % 10 == 2) {
        return -99;
    } else if (hnd_advs / 10 >= 2) {
        return 99;
    }

    int best;
    if (turn == 1) {
        best = -99;
        for (auto p : possible_moves(pos, 1)) {
            best = max(best, analyse_position(p, 0, depth + 1));
        }
    } else {
        best = 99;
        for (auto p : possible_moves(pos, 0)) {
            best = min(best, analyse_position(p, 1, depth + 1));
        }
    }

    return best; //add function to respond with the best move too
}

int main() { //main function
    cout << "Starting chop-sticks game...";
    cout << "\n";
    cout << "You go first...";
    cout << "\n";
    cout << "1111";
    cout << "\n";

    string turn; //players turn will be the two values of your hands
    cin >> turn;

    cout << analyse_position(turn, 0, 1);
}