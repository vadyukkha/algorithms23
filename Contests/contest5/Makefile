.PHONY: help

all: contest5_A contest5_B contest5_C contest5_D # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest5_A: contest5_A.cpp 
	g++ -std=c++20 contest5_A.cpp -o contest5_A

contest5_B: contest5_B.cpp 
	g++ -std=c++20 contest5_B.cpp -o contest5_B

contest5_C: contest5_C.cpp 
	g++ -std=c++20 contest5_C.cpp -o contest5_C

contest5_D: contest5_D.cpp 
	g++ -std=c++20 contest5_D.cpp -o contest5_D

clean: # Delete all builded files
	rm -f contest5_A contest5_B contest5_C contest5_D