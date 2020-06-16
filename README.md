# rainbow-compiler
There are something about compiler.

## Something implemented
- [X] Lexical analysis scanner
- [X] recursive descent parser
- [X] operator first analysis

## Build & Run
1. To build
```bash
cd rainbow-complier/
make
```

2. To run
```bash
cd test/
./test_lex
./test_rec
./test_ope
```
where:
- **test_lex** is the **Lexical analysis scanner's test**
- **test_rec** is the **Recursive descent parser's test**
- **test_ope** is the **Operator first analysis's test**

*noted:* you can modify the content of the files that named **pl0_XX** according to grammar to get different results.
