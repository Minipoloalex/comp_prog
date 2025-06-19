## Useful commands

### Testing an interactive problem

Create FIFOs:
```bash
mkfifo f1 f2
```

Run programs:
```bash
./a.out < f1 | tee f2
```

```bash
python3 interactor.py < f2 | tee f1
```

### For-loops
```bash
for p in A B C D E F; do mkdir $p && cd $p && problem > $p.cpp && cd ..; done
```

```bash
for i in {0..10}; do echo $i; done
```

```bash
for ((i=1;i<=10;i++)); do echo $i; done
```

### Running Python
```bash
python3 -c 'print("a" * 500)' > myin.txt
```
