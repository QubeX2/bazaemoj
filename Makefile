#
#

# extra
RM = rm -f

# compiler
CC = gcc

# compile-time flags
CFLAGS = -Wall -g

# includes
INCLUDES =

# libary paths
LFLAGS =

# libs
LIBS = -lm

# source files
SRCS = bazaemoj.c strb.c

# obj files
OBJS = $(SRCS:.c=.o)

# program
PROGRAM = bazaemoj

.PHONY: 	depend clean

all: 		$(PROGRAM)
			@echo bazaemoj compiled.

$(PROGRAM): $(OBJS)
			$(CC) $(CFLAGS) $(INLUDES) -o $(PROGRAM) $(OBJS) $(LFLAGS) $(LIBS)

.c.o: 		
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
			$(RM) *.o $(PROGRAM)

depend: 	$(SRCS)
			makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
