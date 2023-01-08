On linux
```
g++ snake.cpp -std=c++17 -lGL -lglut
```

Might work on mac with
```
g++ snake.cpp -std=c++17 -L/usr/local/lib -framework OpenGL -framework GLUT
```