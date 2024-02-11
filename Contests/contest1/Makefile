.PHONY: help

all: contest1_A contest1_B contest1_C contest1_D contest1_E # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest1_A: contest1_A.c 
	gcc contest1_A.c -o contest1_A

contest1_B: contest1_B.c 
	gcc contest1_B.c -o contest1_B

contest1_C: contest1_C.c 
	gcc contest1_C.c -o contest1_C

contest1_D: contest1_D.c 
	gcc contest1_D.c -o contest1_D

contest1_E: contest1_E.c 
	gcc contest1_E.c -o contest1_E

clean: # Delete all builded files
	rm -f contest1_A contest1_B contest1_C contest1_D contest1_E