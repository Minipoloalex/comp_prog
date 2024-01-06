#include <bits/stdc++.h>
using namespace std;

typedef deque<int> di;

int main() {
    int n;
    scanf("%d", &n);
    
    char op[100];
    int val;
    di back, front;
    for (int ln = 0; ln < n; ln++) {
        scanf("%s %d", op, &val);
        if (strcmp(op, "push_back") == 0) {
            back.push_back(val);
        }
        else if (strcmp(op, "push_front") == 0) {
            front.push_front(val);
        }
        else if (strcmp(op, "push_middle") == 0) {
            if (back.size() > front.size()) {   // tested
                int diff = (back.size() - front.size() + 1) / 2;
                for (int i = 0; i < diff; i++) {
                    front.push_back(back.front());
                    back.pop_front();
                }
                back.push_front(val);
            }
            else if (front.size() > back.size()) {  // tested
                int diff = (front.size() - back.size()) / 2;
                for (int i = 0; i < diff; i++) {
                    back.push_front(front.back());
                    front.pop_back();
                }
                back.push_front(val);
            }
            else front.push_back(val);
        }
        else if (strcmp(op, "get") == 0) {
            if (val < (int)front.size()) {
                cout << front[val] << endl;
            }
            else {
                cout << back[val - (int)front.size()] << endl;
            }
        }
        else exit(1);
    }
    return 0;
}
