for ((i=1;;i++)) do
    echo $i
    ./gen > intest.txt
    diff -w <(./a.out < intest.txt) <(./brute < intest.txt) || break
done
