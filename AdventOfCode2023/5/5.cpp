#include <bits/stdc++.h>
using namespace std;


typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<string> vs;
vu seeds;
vu soils;
vu fertilizers;
vu waters;
vu lights;
vu temperatures;
vu humidities;
vu locations;

vs lines;

void handle_lines(const vector<ull> &from, vector<ull> &v) {
    string line;

    getline(cin, line);

    while (getline(cin, line)) {    // seed-to-soil
        if (line == "") break;
        lines.push_back(line);
    }
    for (int i = 0; i < (int) seeds.size(); i++) {
        ull s = from[i];
        ull r = s;
        for (string l: lines) {
            istringstream iss_line(l);
            ull dst_range, src_range, range;
            iss_line >> dst_range >> src_range >> range;
            if (s >= src_range && s < src_range + range) {
                r = dst_range + s - src_range;
            }
        }
        v.push_back(r);
    }
    lines.clear();
}

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    string trash;
    iss >> trash;

    ull seed;
    while (iss >> seed) {
        seeds.push_back(seed);
    }
    getline(cin, line);
    handle_lines(seeds, soils);
    handle_lines(soils, fertilizers);
    handle_lines(fertilizers, waters);
    handle_lines(waters, lights);
    handle_lines(lights, temperatures);
    handle_lines(temperatures, humidities);
    handle_lines(humidities, locations);
    ull min_idx = -1;
    ull min_location = ULLONG_MAX;
    for (ull i = 0; i < locations.size(); i++) {
        cout << locations[i] << " ";
        if (locations[i] < min_location) {
            min_location = locations[i];
            min_idx = i;
        }
    }
    cout << endl;
    cout << "Min location: " << min_location << ", seed: " << seeds[min_idx] << endl;

    return 0;
}
