#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <assert.h>

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

uint32_t day1(vector<string>& input) {
    regex line_regex("([a-z]+) (\\d+)");
    
    uint32_t horizontal_position = 0;
    uint32_t depth = 0;

    for(auto line : input) {
        smatch line_match;

        bool input_matches_regex = regex_search(line, line_match, line_regex);
        if(!input_matches_regex) {
            cerr << "Failed to parse " << line << endl;
            exit(1);
        }

        string instruction = line_match[1];
        uint32_t operand = stoi(line_match[2]);

        cout << instruction << " " << operand << endl;

        if(instruction == "forward") {
            horizontal_position += operand; 
        }
        else if(instruction == "down") {
                depth += operand;
        }
        else if(instruction == "up") {
                depth -= operand;
        }

        cout << "hp " << horizontal_position << " " << "depth " << depth << endl;
    }

    return horizontal_position * depth;
}

uint32_t day2(vector<string>& input) {
    regex line_regex("([a-z]+) (\\d+)");
    
    uint32_t horizontal_position = 0;
    uint32_t depth = 0;
    uint32_t aim = 0;

    for(auto line : input) {
        smatch line_match;

        bool input_matches_regex = regex_search(line, line_match, line_regex);
        if(!input_matches_regex) {
            cerr << "Failed to parse " << line << endl;
        }

        string instruction = line_match[1];
        uint32_t operand = stoi(line_match[2]);

        cout << instruction << " " << operand << endl;

        if(instruction == "forward") {
            horizontal_position += operand; 
            depth += aim * operand;
        }
        else if(instruction == "down") {
                aim += operand;
        }
        else if(instruction == "up") {
                aim -= operand;
        }

        cout << "hp " << horizontal_position << " " << "depth " << depth << endl;
    }

    return horizontal_position * depth;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    // cout << day1(file_content) << endl;
    cout << day2(file_content) << endl;
}
