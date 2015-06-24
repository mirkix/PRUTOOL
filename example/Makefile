all: test.stripped test.lst

CC=clpru
LD=lnkpru
AR=arpru
OBJDUMP=dispru
STRIP=strippru
HEX=hexpru

CFLAGS= --endian=little -v3 -s -al --c99 --gcc -O3 --printf_support=minimal --symdebug:none

LDFLAGS=-cr --diag_warning=225 -lAM335x_PRU.cmd -x

STRIPFLAGS=-p

OBJS1:=test.obj

%.obj: %.c
	$(CC) $(CFLAGS) -c $< -ea=.s

%.obj: %.asm
	$(CC) $(CFLAGS) -c $<

test: $(OBJS1)
	$(CC) $(CFLAGS) $^ -q -z $(LDFLAGS) -o $@

test.stripped: test
	$(STRIP) $(STRIPFLAGS) $< -o $@
	size test.stripped
	$(HEX) test.stripped HexUtil_PRU.cmd

test.lst: test
	$(OBJDUMP) -1 $< > $@

clean:
	rm -f \
		test test.asm \
		*.bin *.obj *.lst *.out *.stripped \
