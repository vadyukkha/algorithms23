.PHONY: help

all: bubbleSort bucketSort countingSort insertionSort mergeSort quicksort selectionSort # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

bubbleSort: bubbleSort.c 
	gcc bubbleSort.c -o bubbleSort

bucketSort: bucketSort.c 
	gcc bucketSort.c -o bucketSort

countingSort: countingSort.c 
	gcc countingSort.c -o countingSort

insertionSort: insertionSort.c 
	gcc insertionSort.c -o insertionSort

mergeSort: mergeSort.c 
	gcc mergeSort.c -o mergeSort

quicksort: quicksort.c 
	gcc quicksort.c -o quicksort

selectionSort: selectionSort.c 
	gcc selectionSort.c -o selectionSort

clean: # Delete all builded files
	rm -f bubbleSort bucketSort countingSort insertionSort mergeSort quicksort selectionSort