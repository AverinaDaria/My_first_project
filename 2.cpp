#include <algorithm>
#include <array>
#include <complex>
#include <iomanip>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

string find(const string &s, const vector<string> &a) {
  const string s1 = s.substr(0, s.length() - 1);
  for (const auto &str : a) {
    string first = str.substr(0, str.length() - 1);
    reverse(first.begin(), first.end());
    if (s1 == first) {
      return str;
    }
  }
  return "-1";
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cerr << "Wrong args, specify only the name of the input and output file\n";
    return 1;
  }
  ifstream in(argv[1]);
  if (!in.is_open()) {
    cerr << "Failed to open input file\n";
    return 2;
  }
  vector<string> firstNucleotides;
  string next;
  while (in >> next) {
    firstNucleotides.push_back(next);
  }
  in.close();
  vector<pair<string, string>> result;
  ifstream in2(argv[2]);
  if (!in2.is_open()) {
    cerr << "Failed to open input file\n";
    return 2;
  }
  while (in2 >> next) {
    auto res = find(next, firstNucleotides);
    if (res == "-1") {
      continue;
    }
    result.emplace_back(make_pair(next, res));
  }
  for (const auto &entry : result) {
    cout << entry.first << ' ' << entry.second << '\n';
  }
  in2.close();
  return 0;
}
