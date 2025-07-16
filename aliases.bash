# So I can easily copy paste these between computers (.bash_aliases)

alias problem='echo "#include <bits/stdc++.h>
using namespace std;

void solve() {

}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}"'

alias problemcf='echo "#include <bits/stdc++.h>
using namespace std;

void solve() {

}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}"'

mkcontest() {
  start=$1
  end=$2
  for ((i=$(printf "%d" "'$start"); i<=$(printf "%d" "'$end"); i++)); do
    letter=$(printf "\\$(printf '%03o' "$i")")
    mkdir "$letter" && cd "$letter"
    problem > "$letter.cpp"
    cd ..
  done
}

mkcontestcf() {
  start=$1
  end=$2
  for ((i=$(printf "%d" "'$start"); i<=$(printf "%d" "'$end"); i++)); do
    letter=$(printf "\\$(printf '%03o' "$i")")
    mkdir "$letter" && cd "$letter"
    problemcf > "$letter.cpp"
    cd ..
  done
}

alias comp="cd ~/Documents/comp_prog && code ."
alias cses="cd ~/Documents/comp_prog && code . && cd cses"
alias codeforces="cd ~/Documents/comp_prog && code . && cd codeforces"
alias atcoder="cd ~/Documents/comp_prog && code . && cd atcoder"
alias tsplib="code ~/Documents/TSP-lib"
