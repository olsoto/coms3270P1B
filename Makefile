stat: display.c
	gcc bmp.c pointcloud.c display.c util.c -o pc

clean: 
	rm -f stat stat.exe pc.exe util.exe *~ core