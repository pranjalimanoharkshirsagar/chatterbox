try: project.o
	cc project.o -o project
project.o: project.c
	cc -Wall -c project.c
