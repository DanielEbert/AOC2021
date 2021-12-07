#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <assert.h>
#include <set>
#include <map>

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

uint32_t part1(vector<string>& input) {
    vector<string> timers_s = split(input[0], ",");
    vector<int> current_day;
    for (auto s : timers_s) {
        //cout << s << endl;
        current_day.push_back(stoi(s));
    }

    for (int i = 0; i < 80; i++) {
        vector<int> next_day;
        for (auto timer : current_day) {
            if (timer == 0) {
                next_day.push_back(6);
                next_day.push_back(8);
            } else {
                next_day.push_back(timer-1);
            }
        }
        current_day = next_day;
        cout << current_day.size() << endl;
    }

    return current_day.size();
}

uint32_t part2(vector<string>& input) {
    vector<string> timers_s = split(input[0], ",");

    array<uint64_t, 9> current_day = {0};
    for (int i =0; i < 9; i++) current_day[i] = 0;

    for (auto& timer : timers_s) {
        current_day[stoi(timer)]++;
    }

    for (int d = 0; d < 256; d++) {
        array<uint64_t, 9> next_day = {0};
        for (int i = 0; i < 9; i++) next_day[i] = 0;

        for (int i = 0; i < 8; i++) {
            next_day[i] = current_day[i+1];
        }

        next_day[6] += current_day[0];
        next_day[8] += current_day[0];

        current_day = next_day;

        uint64_t sum = 0;
        for (auto i : current_day) sum += i;
        cout << d << " " << sum << endl;
    }

    return 0;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    //cout << part1(file_content) << endl;
    cout << part2(file_content) << endl;
}
