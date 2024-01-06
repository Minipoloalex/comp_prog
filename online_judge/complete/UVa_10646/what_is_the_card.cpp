#include <bits/stdc++.h>
using namespace std;

typedef pair<char, char> cc;
typedef vector<cc> vcc;


int get_value(cc &card) {
    if (card.first >= '2' && card.first <= '9') {
        return (int) (card.first - '0');
    }
    return 10;
}
// JC 3C 9H KC TH
// 2D AC 6D 2S TC
// 2H 6H 8C 5D 3S
// JH AS JS 4C 9S

// 9D 6S 8H 2C 8D
// 8S JD

//       5H QD 7D
// KH KD AD KS 3H
// 5S TD 6C 7C TS
// 9C 7H 4S QS QC
// AH 3D 5C 7S 4D
// QH 4H

int main() {
    int cases;
    cin >> cases;

    for (int c = 0; c < cases; c++) {
        vcc bottom27;
        vcc top25;
        // 52 cards from bottom to top
        for (int i = 0; i < 52; i++) {
            char first, second;
            cin >> first; cin >> second;
            if (i < 27) bottom27.emplace_back(first, second);
            else top25.emplace_back(first, second);
        }
        int y = 0;        
        for (int i = 0; i < 3; i++) {
            cc card = bottom27.back();
            int value = get_value(card);
            y += value;
            for (int k = 0; (k < 11 - value) && !bottom27.empty(); k++) {
                bottom27.pop_back();
            }
        }
        vcc &final_cards = bottom27;
        for (cc card: top25) {
            final_cards.emplace_back(card);
        }
        printf("Case %d: %c%c\n", c + 1, final_cards[y - 1].first, final_cards[y - 1].second);
    }
    return 0;
}
