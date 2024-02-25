.PHONY: help

all: contest6_A contest6_B contest6_C contest6_D # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest6_A: contest6_A.cpp 
	g++ -std=c++20 contest6_A.cpp -o contest6_A

contest6_B: contest6_B.cpp 
	g++ -std=c++20 contest6_B.cpp -o contest6_B

contest6_C: contest6_C.cpp 
	g++ -std=c++20 contest6_C.cpp -o contest6_C

contest6_D: contest6_D.cpp 
	g++ -std=c++20 contest6_D.cpp -o contest6_D

clean: # Delete all builded files
	rm -f contest6_A contest6_B contest6_C contest6_D