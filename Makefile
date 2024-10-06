stat: pointcloud.c
	gcc pointcloud.c util.c -o pc

clean: 
	rm -f stat stat.exe pc.exe util.exe *~ core