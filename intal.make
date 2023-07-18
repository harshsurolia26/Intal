

a.out:	intal_client.o intal_function.o intal.h
		gcc intal_client.o intal_function.o intal.h


intal_client.o:intal_client.c intal.h
				gcc -c -Wall intal_client.c intal.h

intal_function.o:intal_function.c intal.h
				gcc -c -Wall intal_function.c intal.h