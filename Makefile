all : octopus.out oc_client


VERSION = 0.3

DIR_NET = ./oc_network
DIR_GRAPHICS = ./oc_graphics
DIR_KERNEL = ./oc_kernel
DIR_OBJ = ./objs
DIR_EXEC = ./


LIBRARIES = -lGL -lGLU -lglut -lm -lX11   # LINUX
#LIBRARIES = -L"/System/Library/Frameworks/OpenGL.framework/Libraries" # MacOs

#FRAMEWORK = -framework GLUT   #Macos
#FRAMEWORK += -framework OpenGL #Macos

LIBPATH += $(LIBRARIES)


COMPILERFLAGS = -Wall


CFLAGS = $(COMPILERFLAGS)





oc_graphics.o : $(DIR_GRAPHICS)/oc_graphics.c
	gcc -Wall -c $(DIR_GRAPHICS)/oc_graphics.c -o $(DIR_OBJ)/oc_graphics.o

client.o : $(DIR_NET)/client.c
	gcc -Wall -c  $(DIR_NET)/client.c -o $(DIR_OBJ)/client.o

oc_server.o :  $(DIR_NET)/oc_server.c
	gcc -Wall -c  $(DIR_NET)/oc_server.c  -o $(DIR_OBJ)/oc_server.o

oc_kernel.o : $(DIR_KERNEL)/oc_kernel.c
	gcc -Wall -c $(DIR_KERNEL)/oc_kernel.c  -o $(DIR_OBJ)/oc_kernel.o

main.o :  $(DIR_KERNEL)/main.c
	gcc -Wall -c $(DIR_KERNEL)/main.c  -o $(DIR_OBJ)/main.o

oc_client.out :  client.o
	gcc -o  $(DIR_EXEC)/oc_client.out  $(DIR_OBJ)/client.o



octopus.out :  oc_graphics.o oc_kernel.o  main.o  oc_server.o
	gcc -D_REENTRANT  $(FRAMEWORK) $(CFLAGS) -o $(DIR_EXEC)/octopus.out $(DIR_OBJ)/oc_kernel.o $(DIR_OBJ)/oc_server.o $(DIR_OBJ)/oc_graphics.o $(DIR_OBJ)/main.o -pthread $(LIBPATH)



clean :
	rm  $(DIR_OBJ)/*.o ; rm octopus.out ; rm *~ ; rm oc_client.out
