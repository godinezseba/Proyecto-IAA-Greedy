INPUT?=NL/NL4.txt
RUN=./main < input/$(INPUT) > output/$(INPUT)

all: compile
	$(RUN)

compile:
	g++ src/main.cpp -o main -Wall