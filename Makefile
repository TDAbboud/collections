CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LDFLAGS=
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

LIB_PREFIX=build/lib
INC_PREFIX=build/inc

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

EXAMPLES_SRC=$(wildcard examples/*.c)
EXAMPLES=$(patsubst %.c,%,$(EXAMPLES_SRC))

TARGET=libcollections.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $(LIB_PREFIX)/$@ $(OBJECTS)
	ranlib $(LIB_PREFIX)/$@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $(LIB_PREFIX)/$@ $(OBJECTS)

build:
	@mkdir -p $(LIB_PREFIX)
	@mkdir -p $(INC_PREFIX)
	cp src/*.h $(INC_PREFIX)

# The Unit Tests
.PHONY: tests
tests: LDFLAGS += -static $(LIB_PREFIX)/$(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# Compile the test files and link the library
$(TESTS): $(TEST_SRC)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(EXAMPLES)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install (Place header files and libraries into system path dirs)
install: all
	install -d $(PREFIX)/lib/
	install -d $(PREFIX)/include/
	install $(LIB_PREFIX)/$(TARGET) $(PREFIX)/lib/
	install $(LIB_PREFIX)/$(SO_TARGET) $(PREFIX)/lib/
	# Copy all header files
	install $(INC_PREFIX)/* $(PREFIX)/include/

# The Uninstall (Remove the libraries and header files)
uninstall:
	rm -rf $(PREFIX)/lib/$(TARGET)
	rm -rf $(PREFIX)/lib/$(SO_TARGET)

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

# The Examples
examples: $(EXAMPLES)
	@echo Compiled the examples

# Compile the test files and link the library
$(EXAMPLES): LDFLAGS += -static $(LIB_PREFIX)/$(TARGET)
$(EXAMPLES): $(EXAMPLES_SRC)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)

