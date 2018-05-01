EXECS=helloworld
MPICC?=mpicc

all: ${EXECS}

helloworld: helloworld.c
	${MPICC} -o helloworld helloworld.c

clean:
	rm ${EXECS}
