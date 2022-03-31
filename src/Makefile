CC=gcc
CC_CROSS=x86_64-w64-mingw32-gcc
LIBS=-lraylib -lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp
CFLAGS=-Wall -pedantic -Wshadow -Werror
CFLAGS_CROSS=-mwindows
CFLAGS_O=-O3 -s
DEPENDENCIES=*.c
PROJECT=Platformer
DIR_BUILD=../build/

${PROJECT}: ${DEPENDENCIES}
	${CC} ${CFLAGS} ${DEPENDENCIES} -o ${DIR_BUILD}${PROJECT} ${LIBS}

debug: ${PROJECT}
	${CC} ${CFLAGS} -g ${DEPENDENCIES} -o ${DIR_BUILD}${PROJECT} ${LIBS}

cross: ${DEPENDENCIES}
	${CC_CROSS} ${CFLAGS} ${CFLAGS_CROSS} ${DEPENDENCIES} -o ${DIR_BUILD}windows/${PROJECT} ${LIBS}

release: ${DEPENDENCIES}
	${CC} ${CFLAGS} ${CFLAGS_O} ../src/*.c -o ${DIR_BUILD}${PROJECT} ${LIBS} && ${CC_CROSS} ${CFLAGS} ${CFLAGS_CROSS} ${CFLAGS_O} ${DEPENDENCIES} -o ${DIR_BUILD}windows/${PROJECT} ${LIBS}

run: 
	make && cd ${DIR_BUILD} && ./${PROJECT}

