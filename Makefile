file: lcs.o mainfile.o utility.o lps.o lts.o 
	gcc -Wall -std=c99 mainfile.o utility.o lcs.o lps.o lts.o -o file.out

mainfile.o: mainfile.c main.h
	gcc -Wall -std=c99 -c mainfile.c

utility.o: utility.c utility.h
	gcc -Wall -std=c99 -c utility.c

lcs.o: lcs.h lcs.c
	gcc -Wall -std=c99 -c lcs.c

lps.o: lps.h lps.c
	gcc -Wall -std=c99 -c lps.c

lts.o: lts.h lts.c
	gcc -Wall -std=c99 -c lts.c

clear: 
	rm -f *.out*.o
