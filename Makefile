CC = g++
CFLAGS = -Wall
PROG = assign_openglpipeline

SRCS = assign_openglpipeline.cpp
LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
