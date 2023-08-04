# Pong
A pong game made in C++ with SDL2

The build command for debugging mode is 

```g++ -std=c++17 src/*.cpp -I include -I SDL2/include -L SDL2/lib -g -Wall -m64 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o pong_debug```

The build command for release is 

```g++ -std=c++17 src/*.cpp -I include -I SDL2/include -L SDL2/lib -O3 -Wall -m64 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o pong_release -s```
