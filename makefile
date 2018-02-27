CC=g++ -std=c++11
SRCS=main.cpp Bitmap.cpp Fractal.cpp

frac:
	${CC} ${SRCS} -o main