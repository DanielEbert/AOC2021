#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <string>
#include <fstream>

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

TEST_CASE("one") {
    auto file_content = read_file(string("./input.txt"));

}
