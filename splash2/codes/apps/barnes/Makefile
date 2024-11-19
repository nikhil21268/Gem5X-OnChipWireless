# Makefile in barnes directory

# Include the global configuration
include ../../Makefile.config

# Target executable
TARGET = barnes

# Source files
SRCS = code.C code_io.C getparam.C grav.C load.C util.C

# Object files
OBJS = $(SRCS:.C=.o)

# Default rule
all: $(TARGET)

# Build rule for the target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

# Clean rule
clean:
	rm -rf *.c *.h *.o $(TARGET)

# Dependencies
stdinc.h: code.h defs.h util.h vectmath.h load.h code_io.h grav.h getparam.h stdinc.H
	$(M4) $(MACROS) stdinc.H > stdinc.h

# Explicit rules for .o files
code.o: code.c stdinc.h
code_io.o: code_io.c stdinc.h
getparam.o: getparam.c stdinc.h
grav.o: grav.c stdinc.h
load.o: load.c stdinc.h
util.o: util.c stdinc.h

# Ensure .c and .h files are generated from .C and .H files
code.c: code.C
	$(M4) $(MACROS) $< > $@

code_io.c: code_io.C
	$(M4) $(MACROS) $< > $@

getparam.c: getparam.C
	$(M4) $(MACROS) $< > $@

grav.c: grav.C
	$(M4) $(MACROS) $< > $@

load.c: load.C
	$(M4) $(MACROS) $< > $@

util.c: util.C
	$(M4) $(MACROS) $< > $@

# Similarly for header files
code.h: code.H
	$(M4) $(MACROS) $< > $@

defs.h: defs.H
	$(M4) $(MACROS) $< > $@

util.h: util.H
	$(M4) $(MACROS) $< > $@

vectmath.h: vectmath.H
	$(M4) $(MACROS) $< > $@

load.h: load.H
	$(M4) $(MACROS) $< > $@

code_io.h: code_io.H
	$(M4) $(MACROS) $< > $@

grav.h: grav.H
	$(M4) $(MACROS) $< > $@

getparam.h: getparam.H
	$(M4) $(MACROS) $< > $@

