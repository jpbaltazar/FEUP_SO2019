# Makefile #
#
all: ppa ppb ppc ppd ppe

ppa: ppa.c checker.o
	cc -Wall ppa.c checker.o -o ppa -pthread

ppb: ppb.c checker.o
	cc -Wall ppb.c checker.o -o ppb -pthread

ppc: ppc.c checker.o
	cc -Wall ppc.c checker.o -o ppc -pthread

ppd: ppd.c checker.o
	cc -Wall ppd.c checker.o -o ppd -pthread

ppe: ppe.c checker.o
	cc -Wall ppe.c checker.o -o ppe -pthread


clean:
	rm -f ppa ppb ppc ppd ppe

