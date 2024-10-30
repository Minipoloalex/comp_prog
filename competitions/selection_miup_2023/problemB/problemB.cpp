#include <bits/stdc++.h>
using namespace std;

// morse code
string letters[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-",
".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
string nums[10] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

/*
A .-	B -... 	C -.-.	D -.. 	E .	F ..-. 	G --.	H .... 	I ..	J .--- 	K -.-	L .-..
M --	N -. 	O ---	P .--. 	Q --.-	R .-. 	S ...	T - 	U ..-	V ...- 	W .--	X -..-
Y -.--	Z --.. 	0 -----	1 .---- 	2 ..---	3 ...-- 	4 ....-	5 ..... 	6 -....	7 --... 	8 ---..	9 ----.
*/
int main() {
    string s;
    cin >> s;
    string res;
    for (int i = 0; i < (int) s.size(); i++) {
        s[i] = (char) tolower(s[i]);
        if (s[i] >= 'a' && s[i] <= 'z') {
            res += letters[s[i]-'a'];
        }
        else if (s[i] >= '0' && s[i] <= '9') {
            res += nums[s[i]-'0'];
        }
    }
    // cout << res << endl;
    bool is_palindrome = true;
    auto rev_itr = res.rbegin();
    for (auto itr = res.begin(); itr != res.end(); rev_itr++, itr++) {
    // for (int i = 0; i < (int) res.size(); i++) {
        // cout << *itr << " " << *rev_itr << endl;
        if (*itr != *rev_itr) {
            is_palindrome = false;
            break;
        }
    }
    if (res.empty() || !is_palindrome) {
            cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
    }

    return 0;
}
