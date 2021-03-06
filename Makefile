
BIN ?= csv-delim
PREFIX ?= /usr/local
CFLAGS = 
#CFLAGS = -L${JEMALLOC_PATH}/lib -Wl,-rpath,${JEMALLOC_PATH}/lib -ljemalloc 
DEPS = $(wildcard deps/*/*.c)

all: csv-delim

csv-delim: delim.c $(DEPS)
	$(CC) $(CFLAGS) -Ideps -o $@ $^

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	install $^ $(PREFIX)/bin

clean:
	rm -f csv-delim

