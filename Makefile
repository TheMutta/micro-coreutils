.POSIX:

XCFLAGS = -std=c99 -D_DEFAULT_SOURCE ${CFLAGS}

all: ls cp mv touch cat sleep stat grep du chroot uname

ls:
	gcc ${XCFLAGS} ls.c -o ls

cp:
	gcc ${XCFLAGS} cp.c -o cp

mv:
	gcc ${XCFLAGS} mv.c -o mv

touch:
	gcc ${XCFLAGS} touch.c -o touch

cat:
	gcc ${XCFLAGS} cat.c -o cat

sleep:
	gcc ${XCFLAGS} sleep.c -o sleep

stat:
	gcc ${XCFLAGS} stat.c -o stat

grep:
	gcc ${XCFLAGS} grep.c -o grep

du:
	gcc ${XCFLAGS} du.c -o du

chroot:
	gcc ${XCFLAGS} chroot.c -o chroot

uname:
	gcc ${XCFLAGS} uname.c -o uname

clean:
	rm -f ls cp mv touch cat sleep stat grep du chroot uname

.PHONY: all clean
