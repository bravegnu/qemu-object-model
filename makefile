
OBJDIR = build
VPATH  = demo qom qwt

CC = gcc
# need the -m32 option on 64bit machines?
CFLAGS = -fpic -DG_VA_COPY_AS_ARRAY $(shell pkg-config --cflags sdl2 SDL2_ttf) -Iqwt -Iqom
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf)

MAIN_CSOURCES = ${shell ls *.c }
MAIN_OBJECTS = ${shell for obj in ${MAIN_CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

DEMO_CSOURCES = ${shell find demo -name \*.c }
DEMO_OBJECTS = ${shell for obj in ${DEMO_CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

QOM_CSOURCES = ${shell find qom -name \*.c}
QOM_OBJECTS = ${shell for obj in ${QOM_CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

QWT_CSOURCES = ${shell find qwt -name \*.c}
QWT_OBJECTS = ${shell for obj in ${QWT_CSOURCES:.c=.o}; do echo ${OBJDIR}/`basename $$obj`;done}

main: ${MAIN_OBJECTS} build/libqom.so build/libqwt.so
	${CC} ${MAIN_OBJECTS} -o $@ -lqwt -lqom -L${OBJDIR} ${LDFLAGS}

${OBJDIR}/%.o: %.c
	${CC} -c ${CFLAGS} ${CPPFLAGS} $< -o $@

build/libqom.so: ${QOM_OBJECTS}
	${CC} --shared -o $@ $^

build/libqwt.so: ${QWT_OBJECTS}
	${CC} --shared -o $@ $^ -lqom -L${OBJDIR} ${LDFLAGS}

build/demo: ${DEMO_OBJECTS} build/libqom.so build/libqwt.so
	${CC} ${DEMO_OBJECTS} -o $@ -lqwt -lqom -L${OBJDIR} ${LDFLAGS}

clean:
	rm -f build/*.o
	rm -f build/libqom.so
	rm -f build/libqwt.so
	rm -f build/demo
	rm -f main.o

distclean: clean
	find . -name "*~" -delete
