#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
    uint32_t number_of_increases = 0;

    auto it = input.begin() + 1;

    for(; it != input.end(); it++) {
        uint32_t previous_depth = stoi(*(it - 1));
        uint32_t current_depth = stoi(*it);
        if(previous_depth < current_depth) {
            number_of_increases++;
        }
    }
    return number_of_increases;
}

uint32_t day2(vector<string>& input) {
    uint32_t number_of_increases = 0;
    
    auto it = input.begin() + 3;

    while(it != input.end()) {
        uint32_t previous_depth = stoi(*(it - 3));
        uint32_t current_depth = stoi(*it);

        if(previous_depth < current_depth) {
            number_of_increases++;
        }

        it++;
    }

    return number_of_increases;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    //cout << day1(file_content) << endl;
    cout << day2(file_content) << endl;
}
