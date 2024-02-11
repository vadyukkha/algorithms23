.PHONY: help

all: contest4_A contest4_B # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest4_A: contest4_A.cpp 
	g++ -std=c++20 contest4_A.cpp -o contest4_A

contest4_B: contest4_B.cpp 
	g++ -std=c++20 contest4_B.cpp -o contest4_B

clean: # Delete all builded files
	rm -f contest4_A contest4_B