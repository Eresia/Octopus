CC=gcc
headName=h
srcName=c

LIBRAIRIES=-lGL -lGLU -lglut -lm -lX11 #Linux
FRAMEWORK = #Linux

#LIBRARIES = -L\"/System/Library/Frameworks/OpenGL.framework/Libraries\" # MacOs
#FRAMEWORK = -framework GLUT   #Macos
#FRAMEWORK += -framework OpenGL #Macos

CFLAGS=-Wall -DDEBUG
EFLAGS=$(FRAMEWORK) -lpthread -g $(LIBRAIRIES)

server=server.out

nameObjectDir=bin
nameObjectSrc=src

objectDirServer=$(shell pwd)/server/$(nameObjectDir)
srcDirServer=$(shell pwd)/server/$(nameObjectSrc)

directoriesServer=$(wildcard $(srcDirServer)/*/)

srcFileServer=$(foreach dir, $(directoriesServer), $(wildcard $(dir)*.$(srcName)))

headersServer=$(wildcard $(directoriesServer)*.$(headName))

objectsServer=$(foreach file, $(srcFileServer:.$(srcName)=.o), $(objectDirServer)/$(notdir $(file)))

all: $(server) #$(client)

$(server): compilationServer
	@$(CC) -o $(server) $(objectsServer) $(objectsData) $(EFLAGS)

#$(client): compilationClient
#	@$(CC) -o $(client) $(objectsClient) $(objectsData) $(EFLAGS)

compilationServer:
	@mkdir $(objectDirServer) -p
	@for dir in $(directoriesServer); do \
		if [ ! -e $$dir/Makefile ]; then \
				cp Makefile_type $$dir/Makefile; \
		fi; \
		make --no-print-directory -C $$dir objectDir="../../$(nameObjectDir)" headers="$(headersServer)" CC="$(CC)" headName="$(headName)" srcName="$(srcName)" CFLAGS="$(CFLAGS)";	\
	done

clean_all: clean
	rm $(server)
	find server/ -name Makefile -exec rm {} +

clean:
	rm -R $(objectDirServer)
