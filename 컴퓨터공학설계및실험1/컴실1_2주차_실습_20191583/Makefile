cc=gcc
cflags = -W -g
target = fmt

objects = main.c String_Manipulation.c Output.c

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.c String_manipulation.o Output.o : Header.h

.PHONY : clean
clean :
	rm $(target) $(objects)
