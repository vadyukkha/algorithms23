.PHONY: help

all: contest2_A contest2_B contest2_C # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

contest2_A: contest2_A.c 
	gcc contest2_A.c -o contest2_A

contest2_B: contest2_B.c 
	gcc contest2_B.c -o contest2_B

contest2_C: contest2_C.c 
	gcc contest2_C.c -o contest2_C

clean: # Delete all builded files
	rm -f contest2_A contest2_B contest2_C