On linux
```
g++ -Wall -Wextra snake.cpp -std=c++17 -lGL -lglut -lm -o snake.out
```

Might work on mac with
```
g++ snake.cpp -std=c++17 -L/usr/local/lib -framework OpenGL -framework GLUT -o snake.out
```