# So I can easily copy paste these between computers (.bash_aliases)

alias comp="cd ~/Documents/comp_prog && code ."
alias cses="cd ~/Documents/comp_prog && code . && cd cses"
alias codeforces="cd ~/Documents/comp_prog && code . && cd codeforces"
alias atcoder="cd ~/Documents/comp_prog && code . && cd atcoder"
alias tsplib="code ~/Documents/TSP-lib"

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

# By ChatGPT
# =========================================
# tsplib: open TSP‑lib in VS Code or cat a file
tsplib() {
  if [[ -z $1 ]]; then
    code "$HOME/Documents/TSP-lib"
  else
    # allow absolute or relative paths
    if [[ "$1" = /* ]]; then
      cat "$1"
    else
      cat "$HOME/Documents/TSP-lib/$1"
    fi
  fi
}

# Tab‑completion: always relative to ~/Documents/TSP‑lib,
# append “/” for directories, and no trailing space
_tsplib_completion() {
  local cur="${COMP_WORDS[COMP_CWORD]}"
  local base="$HOME/Documents/TSP-lib/"
  local -a fulls matches
  local IFS=$'\n'

  # find all matches under the base dir
  fulls=( $(compgen -f -- "${base}${cur}") )

  matches=()
  for f in "${fulls[@]}"; do
    # strip the prefix
    local rel="${f#"$base"}"
    # if it’s a directory, add a slash
    if [[ -d "$f" ]]; then
      matches+=( "$rel/" )
    else
      matches+=( "$rel" )
    fi
  done

  COMPREPLY=( "${matches[@]}" )

  # don’t insert a space after completion (so slash remains, and you can continue)
  compopt -o nospace
}

complete -F _tsplib_completion tsplib
# =========================================
