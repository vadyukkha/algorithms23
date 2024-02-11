.PHONY: help

all: linSearch binSearch expSearch interpolationSearch # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

linSearch: linSearch.c 
	gcc linSearch.c -o linSearch

binSearch: binSearch.c 
	gcc binSearch.c -o binSearch

expSearch: expSearch.c 
	gcc expSearch.c -o expSearch

interpolationSearch: interpolationSearch.c 
	gcc interpolationSearch.c -o interpolationSearch

clean: # Delete all builded files
	rm -f linSearch binSearch expSearch interpolationSearch