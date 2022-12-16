#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

ostream& print(ostream& out, const vector<string>& scan) {
    for(const string& i : scan) {
        out << i << endl;
    }
    return out;
}

bool abyss(const pair<int, int>& sand, const vector<string>& scan) {
    if(sand.second >= scan.size() || sand.first >= scan[0].size() || sand.first < 0) {
        return 1;
    }
    return 0;
}

bool fall(pair<int, int>& sand, const vector<string>& scan) {
    while(scan[sand.second][sand.first] != '#' && scan[sand.second][sand.first] != 'o') {
        sand.second++;
        if(abyss(sand, scan) == 1) {
            return 1;
        }
    }
    sand.second--;
    return 0;
}

int simulate(vector<string>& scan, const pair<int, int>& start) {
    int index = 0;

    pair<int, int> curr;
    //cout << "starting from " << start.first << ", " << start.second << endl;
    while(true){
        bool rest = false;
        curr = start;
        // fall down
        while(rest == false) {
            if(scan[curr.second+1][curr.first] == '.') {
                if(fall(curr, scan) == 1) return index;
                //cout << "sand fell to " << curr.first << ", " << curr.second << endl;
            }
            if(scan[curr.second+1][curr.first-1] != '#' && scan[curr.second+1][curr.first-1] != 'o') {
                curr.second++;
                curr.first--;
                //cout << "sand fell left to " << curr.first << ", " << curr.second << endl;
                if(abyss(curr, scan) == 1) { return index;}
            }
            else if(scan[curr.second+1][curr.first+1] != '#' && scan[curr.second+1][curr.first+1] != 'o') {
                curr.second++;
                curr.first++;
                //cout << "sand fell right to " << curr.first << ", " << curr.second << endl;
                if(abyss(curr, scan) == 1) { return index;}
            }
            else rest = true;
        }

        cout << "sand rested at " << curr.first << ", " << curr.second << endl;

        scan[curr.second][curr.first] = 'o';
        index++;

        // print(cout, scan);
        // cout << endl;
    }

    return 0;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;

    const pair<int, int> kStart(500, 0);

    pair<int, int> max(kStart);
    pair<int, int> min(kStart);

    while(getline(in, line)) {
        istringstream sin(line);
        int x, y;
        string trash;
        while(sin) {
            sin >> x;
            sin.get();
            sin >> y;
            if(x > max.first) max.first = x;
            else if(x < min.first) min.first = x;
            if(y > max.second) max.second = y;
            else if(y < min.second) min.second = y;
            
            sin >> trash;
        }
    }

    const int kWidth = max.first - min.first + 1;
    const int kHeight = max.second - min.second + 1;

    cout << "maximum coord: " << max.first << ", " << max.second << endl;
    cout << "minimum coord: " << min.first << ", " << min.second << endl;

    cout << "box with height " << kHeight << " and width " << kWidth << endl;

    string row = string(kWidth, '.');
    vector<string> scan(kHeight, row);

    // for(const string& i : scan) {
    //     cout << i << endl;
    // }

    in = ifstream("input.txt");

    // intialize scan
    while(getline(in, line)) {
        istringstream sin(line);
        int x1, y1;
        string trash;
        sin >> x1;
        sin.get();
        sin >> y1;
        sin >> trash;

        x1 -= min.first;
        y1-= min.second;

        while(sin) {
            int x2, y2;
            sin >> x2;
            sin.get();
            sin >> y2;

            x2 -= min.first;
            y2-= min.second;

            // if vertical line
            if(x1 == x2) {
                if(y1 < y2) {
                    for(int i = y1; i <= y2; ++i) {
                        scan[i][x1] = '#';
                    }
                }
                else {
                    for(int i = y2; i <= y1; ++i) {
                        scan[i][x1] = '#';
                    }
                }
            }
            // if horizontal line
            else if(y1 == y2) {
                if(x1 < x2) {
                    for(int i = x1; i <= x2; ++i) {
                        scan[y1][i] = '#';
                    }
                }
                else {
                    for(int i = x2; i <= x1; ++i) {
                        scan[y1][i] = '#';
                    }
                }
            }

            x1 = x2;
            y1 = y2;

            sin >> trash;
        }
    }


    const pair<int, int> start = make_pair(kStart.first - min.first, kStart.second - min.second);

    int result = simulate(scan, start);

    print(cout, scan);
    cout << endl;

    cout << "result: " << result << endl;

    return 0;
}