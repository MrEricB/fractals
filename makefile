CC=g++ -std=c++11
SRCS=main.cpp Bitmap.cpp Mandelbrot.cpp

frac:
	${CC} ${SRCS} -o main