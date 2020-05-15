# variables para el input
N=4
TYPE=NL
SEED=0

INPUT=$(TYPE)$(N).txt
RUN=./main $(SEED) $(N) < input/$(TYPE)/$(INPUT) > output/$(INPUT)

all: compile
	$(RUN)

compile:
	g++ src/main.cpp -o main -Wall

clean:
	rm -f main