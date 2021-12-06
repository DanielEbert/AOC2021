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

struct Point {
    uint32_t x;
    uint32_t y;
};

bool operator<(const Point& p1, const Point& p2) {
	return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

uint32_t part1(vector<string>& input) {
    regex line_regex("(\\d+),(\\d+) -> (\\d+),(\\d+)");

    map<Point, int> map;

    for (auto& line : input) {
        smatch line_match;
        bool input_matches_regex = regex_search(line, line_match, line_regex);
        assert(input_matches_regex);
        uint32_t x1 = stoi(line_match[1]);
        uint32_t y1 = stoi(line_match[2]);
        uint32_t x2 = stoi(line_match[3]);
        uint32_t y2 = stoi(line_match[4]);
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);

        // from now one x1 < x2 and y1 < y2

        if (x1 == x2) {
            for (int i = y1; i <= y2; i++) {
                map[{x1, (uint32_t)i}]++;
            }
        }
        if (y1 == y2) {
            for (int i = x1; i <= x2; i++) {
                map[{uint32_t(i), y1}]++;
            }
        }
    }

    uint32_t num_overlaps = count_if(map.begin(), map.end(), [](auto& p) {
        return p.second >= 2;
    });

    return num_overlaps;
}

uint32_t part2(vector<string>& input) {
    regex line_regex("(\\d+),(\\d+) -> (\\d+),(\\d+)");

    array<array<int, 1000>, 1000> board;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            board[j][i] = 0;
        }
    }

    for (auto& line : input) {
        smatch line_match;
        bool input_matches_regex = regex_search(line, line_match, line_regex);
        assert(input_matches_regex);
        uint32_t x1 = stoi(line_match[1]);
        uint32_t y1 = stoi(line_match[2]);
        uint32_t x2 = stoi(line_match[3]);
        uint32_t y2 = stoi(line_match[4]);
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        
        uint32_t xmin = min(x1, x2);
        uint32_t xmax = max(x1, x2);

        uint32_t ymin = min(y1, y2);
        uint32_t ymax = max(y1, y2);

        if (x1 == x2) {
            for (int i = ymin; i <= ymax; i++) {
                board[x1][i]++;
            }
        }
        // TODO: does this count one pos twice?
        if (y1 == y2) {
            for (int i = xmin; i <= xmax; i++) {
                board[i][y1]++;
            }
        }

        uint32_t tmpx = xmax - xmin;
        uint32_t tmpy = ymax - ymin;

        if (tmpx == tmpy) {
            cout << "got vertical" << endl;
            if (x1 < x2 && y1 < y2) {
                int j = y1;
                for (int i = x1; i <= x2; i++) {
                    board[i][j]++;
                    j++;
                }
            } else if (x2 < x1 && y1 < y2) {
                int j = y2;
                for (int i = x2; i <= x1; i++) {
                    board[i][j]++;
                    j--;
                }
            } else if (x1 < x2 && y2 < y1) {
                int j = y1;
                for (int i = x1; i <= x2; i++) {
                    board[i][j]++;
                    j--;
                }
            } else if (x2 < x1 && y2 < y1) {
                int j = y2;
                for (int i = x2; i <= x1; i++) {
                    board[i][j]++;
                    j++;
                }
            } 
        }

        /*cout << endl;
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                cout << board[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl << endl;*/
    }

    uint32_t num_overlaps = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (board[j][i] > 1) num_overlaps++;
            cout << board[j][i] << " ";
        }
        cout << endl;
    }

    return num_overlaps;
}

int main() {
    auto file_content = read_file(string("./input.txt"));

    cout << part1(file_content) << endl;
    //cout << part2(file_content) << endl;
}
