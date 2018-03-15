CC=g++ -std=c++11
SRCS=main.cpp Bitmap.cpp Mandelbrot.cpp ZoomList.cpp

frac:
	${CC} ${SRCS} -o main -Wall