.PHONY: help

all: contest3_A contest3_B contest3_C # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest3_A: contest3_A.cpp 
	g++ -std=c++20 contest3_A.cpp -o contest3_A

contest3_B: contest3_B.cpp 
	g++ -std=c++20 contest3_B.cpp -o contest3_B

contest3_C: contest3_C.java 
	javac contest3_C.java

clean: # Delete all builded files
	rm -f contest3_A contest3_B contest3_C