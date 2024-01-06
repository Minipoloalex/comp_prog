#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ll;

char vowels[6] = "aeiou";

int is_vowel(char c) {
    for (int i = 0; i < 6; i++) {
        if (c == vowels[i]) return 1;
    }
    return 0;
}

int main() {
    string input = "I love CS3233 Competitive Programming. i also love AlGoRiThM";
    string r;
    int d = 0, v = 0, alphas = 0;

    for (ll i = 0; i < input.size(); i++) {
        char c = tolower(input[i]);
        r += tolower(c);
        d += isdigit(c) ? 1 : 0;
        alphas += isalpha(c) ? 1 : 0;
        v += is_vowel(c);
    }
    cout << "Vowels: " << v << endl;
    cout << "Consonants: " << alphas - v << endl;
    cout << "Digits: " << d << endl;
    cout << "String in lower case: " << r << endl;
    return 0;
}
