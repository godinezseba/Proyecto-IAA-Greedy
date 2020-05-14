N?=4
INPUT=NL/NL$(N).txt
RUN=./main < input/$(INPUT) > output/$(INPUT)

all: compile
	$(RUN)

compile:
	g++ src/main.cpp -o main -Wall

clean:
	rm main