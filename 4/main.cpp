#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <assert.h>
#include <set>

using namespace std;

vector<string> read_file(string s) {
    vector<string> ret;

    ifstream file(s);

    string line;
    while(getline(file, line)) {
        cout << "reading line " << line << endl;
        ret.push_back(line);
    }
    return ret;
}

vector<string> split(string& s, string delimiter = " ") {
    vector<string> ret;
    size_t start = 0;
    size_t end = s.find(delimiter);
    while (end != -1) {
        string sub = s.substr(start, end - start);
        if (sub.length() > 0) {
            ret.push_back(sub);
        }
        start = end + delimiter.size();
        end = s.find(delimiter, start);
    }
    if (start != s.length()) {
        ret.push_back(s.substr(start, string::npos));
    }
    return ret;
}

bool board_win(array<array<int, 5>, 5>& board_hits) {
    for (int i = 0; i < 5; i++) {
        bool line_hit = true;
        for (int j = 0; j < 5; j++) {
            if (board_hits[i][j] == 0) {
                line_hit = false;
                break;
            }
        }
        if (line_hit) return true;
    }

    for (int i = 0; i < 5; i++) {
        bool line_hit = true;
        for (int j = 0; j < 5; j++) {
            if (board_hits[j][i] == 0) {
                line_hit = false;
                break;
            }
        }
        if (line_hit) return true;
    }

    return false;
} 

uint32_t day1(vector<string>& input) {
    vector<array<array<int, 5>, 5>> boards;
    vector<array<array<int, 5>, 5>> boards_hit;
    
    vector<string> chosen_numbers = split(input[0], ",");
    for (string& i : chosen_numbers) {
        cout << i << endl;
    }

    int start = 2;
    for (int start = 2; start < input.size(); start += 6) {
        array<array<int, 5>, 5> board;
        array<array<int, 5>, 5> board_hits = {0};
        set<int> board_numbers;

        for (int i = start; i < start + 5; i++) {
            cout << input[i] << endl;
            vector<string> lines = split(input[i]);
            for (int j = 0; j < lines.size(); j++) {
                board[i - start][j] = stoi(lines[j]);
                board_numbers.insert(stoi(lines[j]));
            }
        }

        boards.push_back(board);
        boards_hit.push_back(board_hits);

        cout << endl;
    }

    for (string& chosen_number : chosen_numbers) {
        for (int b = 0; b < boards.size(); b++) {
            int chosen_number_int = stoi(chosen_number);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (boards[b][i][j] == chosen_number_int) {
                        boards_hit[b][i][j] = 1;
                    }
                }
            }
            cout << "chosen num " << chosen_number << endl;
            cout << "board win:" <<  (board_win(boards_hit[b]) ? "yea" : "no") << endl;
            if (board_win(boards_hit[b])) {
                int sum_not_hit = 0;
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (boards_hit[b][i][j] == 0) {
                            sum_not_hit += boards[b][i][j];
                            cout << "not hit " << boards[b][i][j] << endl;
                        }
                    }
                }
                cout << "score: " << sum_not_hit << " " << chosen_number_int << endl;
                exit(0);
            }
        }
    }



    // We can start with brute force.
    // Later we could assign each field a bitposition
    // and have precomputed winning bitpositions


    return 0;
}

uint32_t day2(vector<string>& input) {
    vector<array<array<int, 5>, 5>> boards;
    vector<array<array<int, 5>, 5>> boards_hit;
    
    vector<string> chosen_numbers = split(input[0], ",");
    for (string& i : chosen_numbers) {
        cout << i << endl;
    }

    int start = 2;
    for (int start = 2; start < input.size(); start += 6) {
        array<array<int, 5>, 5> board;
        array<array<int, 5>, 5> board_hits = {0};
        set<int> board_numbers;

        for (int i = start; i < start + 5; i++) {
            cout << input[i] << endl;
            vector<string> lines = split(input[i]);
            for (int j = 0; j < lines.size(); j++) {
                board[i - start][j] = stoi(lines[j]);
                board_numbers.insert(stoi(lines[j]));
            }
        }

        boards.push_back(board);
        boards_hit.push_back(board_hits);

        cout << endl;
    }

    set<int> boards_left;
    for (int i = 0; i < boards.size(); i++) {
        boards_left.insert(i);
    }

    int last_winning_board = -1;

    for (string& chosen_number : chosen_numbers) {
        for (int b = 0; b < boards.size(); b++) {
            if (boards_left.find(b) == boards_left.end()) {
                continue;
            }
            int chosen_number_int = stoi(chosen_number);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (boards[b][i][j] == chosen_number_int) {
                        boards_hit[b][i][j] = 1;
                    }
                }
            }
            cout << "chosen num " << chosen_number << endl;
            cout << "board win:" <<  (board_win(boards_hit[b]) ? "yea" : "no") << endl;
            if (board_win(boards_hit[b])) {
                boards_left.erase(b);
                if (boards_left.size() == 0) {
                    last_winning_board = b;
                    break;
                }
            }
        }
    }

    int sum_not_hit = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (boards_hit[last_winning_board][i][j] == 0) {
                sum_not_hit += boards[last_winning_board][i][j];
                cout << "not hit " << boards[last_winning_board][i][j] << endl;
            }
        }
    }
    cout << "score: " << sum_not_hit  << endl;



    // We can start with brute force.
    // Later we could assign each field a bitposition
    // and have precomputed winning bitpositions


    return 0;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    //cout << day1(file_content) << endl;
    cout << day2(file_content) << endl;
}
