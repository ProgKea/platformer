CC=gcc
CC_CROSS=x86_64-w64-mingw32-gcc
LIBS=-lraylib
CFLAGS=-Wall -pedantic -Wshadow -Werror
CFLAGS_CROSS=-mwindows
CFLAGS_O=-O3 -s
DEPENDENCIES=../src/*.c
PROJECT=Platformer

${PROJECT}: ${DEPENDENCIES}
	${CC} ${CFLAGS} ${DEPENDENCIES} -o ${PROJECT} ${LIBS}

cross: ${DEPENDENCIES}
	${CC_CROSS} ${CFLAGS} ${CFLAGS_CROSS} ${DEPENDENCIES} -o windows/${PROJECT} ${LIBS}

release: ${DEPENDENCIES}
	${CC} ${CFLAGS} ${CFLAGS_O} ../src/*.c -o ${PROJECT} ${LIBS} && ${CC_CROSS} ${CFLAGS} ${CFLAGS_CROSS} ${CFLAGS_O} ${DEPENDENCIES} -o windows/${PROJECT} ${LIBS}



run: 
	make && ./${PROJECT}

