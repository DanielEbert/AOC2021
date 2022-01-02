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
    vector<string> line = split(input[0], ",");
    vector<int> line_i;
    for (auto i : line) {
        line_i.push_back(stoi(i));
    }

    uint32_t cur_min = UINT32_MAX;

    uint32_t max_elem = *max_element(line_i.begin(), line_i.end());

    for (int i = *min_element(line_i.begin(), line_i.end()); i < max_elem; i++) {
        uint32_t cost = 0;
        for (string j : line) {
            uint32_t diff = abs(i - stoi(j));
            for (int k = 0; k < diff; k++) {
                cost += k + 1;
            }
        }
        if (cost < cur_min) {
            cur_min = cost;
        }
    }

    return cur_min;

}

int main() {
    auto file_content = read_file(string("./input.txt"));

    cout << part1(file_content) << endl;
    //cout << part2(file_content) << endl;
}
