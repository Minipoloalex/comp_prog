## Testing an interactive problem

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
