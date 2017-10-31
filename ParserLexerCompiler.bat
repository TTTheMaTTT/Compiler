win_flex -o lexer1.cpp lexer1.l
win_bison -o parser1.cpp parser1.y
g++ parser1.cpp lexer1.cpp -o myapp.exe