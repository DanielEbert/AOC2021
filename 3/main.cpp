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

uint32_t day1(vector<string>& input) {
    /* Idea:
        
    */
    size_t line_length = input[0].length();
    uint64_t gamma = 0;
    uint64_t epsilon = 0;
    for (int i = 0; i < line_length; i++) {
        gamma <<= 1;
        epsilon <<= 1;
        uint32_t ones = 0;
        for (string& line : input) {
            if (line[i] == '1') ones++;
        }
        if (ones > input.size() / 2) {
            cout << "i: " << i << " ones: " << ones << endl;
            gamma += 1;
        } else {
            epsilon += 1;
        }
    }

    return gamma * epsilon;
}

uint64_t day2(vector<string>& input) {
    size_t line_length = input[0].length();

    set<string> lines;
    for (string& line : input) {
        lines.insert(line);
    }

    for (int i = 0; i < line_length; i++) {
        if (lines.size() == 1) {
            break;
        }
        uint32_t ones = 0;
        for (const string& line : lines) {
            if (line[i] == '1') ones++;
        }
        if (
                (lines.size() % 2 == 0 && ones == lines.size() / 2) ||
                (ones > lines.size() / 2)
        ) {
            cout << "i: " << i << " ones: " << ones << endl;
            for (const string& line : lines) {
                if (line[i] == '0') lines.erase(line);
            }
        } else {
            for (const string& line : lines) {
                if (line[i] == '1') lines.erase(line);
            }
        }

        cout << "i: " << i << endl;
        for (auto x : lines) cout << x << endl;
    }

    cout << lines.size() << endl;

    assert(lines.size() == 1);
    string ones_target = *(lines.begin());

    set<string> lines2;
    for (string& line : input) {
        lines2.insert(line);
    }

    for (int i = 0; i < line_length; i++) {
        if (lines2.size() == 1) {
            break;
        }

        uint32_t zeroes = 0;
        for (const string& line : lines2) {
            if (line[i] == '0') zeroes++;
        }
        if (
                (lines2.size() % 2 == 0 && zeroes == lines2.size() / 2) ||
                (zeroes < lines2.size() / 2)
        ) {
            cout << "i: " << i << " zeroes: " << zeroes << endl;
            for (const string& line : lines2) {
                if (line[i] == '1') lines2.erase(line);
            }
        } else {
            for (const string& line : lines2) {
                if (line[i] == '0') lines2.erase(line);
            }
        }

        cout << "i: " << i << endl;
        for (auto x : lines2) cout << x << endl;
    }

    cout << lines2.size() << endl;

    assert(lines2.size() == 1);
    string zero_target = *(lines2.begin());

    cout << "ones target: " << ones_target << " zero target: " << zero_target << endl;

    uint64_t ones_dec = 0;
    uint64_t zeroes_dec = 0;

    for (auto it = ones_target.begin(); it != ones_target.end(); it++) {
        ones_dec <<= 1;
        if (*it == '1') ones_dec += 1;
    }

    for (auto it = zero_target.begin(); it != zero_target.end(); it++) {
        zeroes_dec <<= 1;
        if (*it == '1') zeroes_dec += 1;
    }

    return ones_dec * zeroes_dec;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    //cout << day1(file_content) << endl;
    cout << day2(file_content) << endl;
}
