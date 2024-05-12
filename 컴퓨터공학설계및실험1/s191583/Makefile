cc=gcc
cflags = -W -g
target = starwars

objects = main.c Count.c Output.c

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o Count.o Output.o : Header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
