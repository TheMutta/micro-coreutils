all: ls cp mv touch cat sleep stat grep du chroot

ls:
	gcc ls.c -o ls

cp:
	gcc cp.c -o cp

mv:
	gcc mv.c -o mv

touch:
	gcc touch.c -o touch

cat:
	gcc cat.c -o cat

sleep:
	gcc sleep.c -o sleep

stat:
	gcc stat.c -o stat

grep:
	gcc grep.c -o grep

du:
	gcc du.c -o du

chroot:
	gcc chroot.c -o chroot
