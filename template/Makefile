CC = g++
CFLAGS = -O3
SOURCES=$(wildcard *.cc)
EXECUTABLES=$(SOURCES:%.cc=%)

all: ${EXECUTABLES}

${EXECUTABLES}: ${SOURCES}
	$(CC) $(CFLAGS) $@.cc  -o $@
clean:
	rm -f $(EXECUTABLES)
