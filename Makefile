display: display.o bmp.o pointcloud.o util.o
	gcc display.o bmp.o pointcloud.o util.o -o stat -lm

display.o: display.c pointcloud.h util.h bmp.h
	gcc -c display.c -o display.o

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -o bmp.o

pointcloud.o: pointcloud.c pointcloud.h util.h bmp.h
	gcc -c pointcloud.c -o pointcloud.o

util.o: util.c util.h
	gcc -c util.c -o util.o

clean:
	rm -f stat stat.exe *.o