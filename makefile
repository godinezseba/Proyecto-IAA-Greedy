# variables para el input
N=4
TIPO=NL
SEMILLA=0

INPUT=$(TIPO)$(N).txt
RUN=./main $(SEMILLA) $(N) < input/$(TIPO)/$(INPUT) > output/$(INPUT)

all: compile
	$(RUN)

compile:
	g++ src/main.cpp -o main -Wall

clean:
	rm -f main