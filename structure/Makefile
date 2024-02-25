.PHONY: help

all: DisjointSet Hashmap Heap LinkedList PriorityQueue Queue Stack_array Stack_linkedList Graph # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

DisjointSet: DisjointSet.cpp 
	g++ -std=c++20 DisjointSet.cpp -o DisjointSet

Hashmap: Hashmap.cpp 
	g++ -std=c++20 Hashmap.cpp -o Hashmap

Heap: Heap.cpp 
	g++ -std=c++20 Heap.cpp -o Heap

LinkedList: LinkedList.cpp 
	g++ -std=c++20 LinkedList.cpp -o LinkedList

PriorityQueue: PriorityQueue.cpp 
	g++ -std=c++20 PriorityQueue.cpp -o PriorityQueue

Queue: Queue.cpp 
	g++ -std=c++20 Queue.cpp -o Queue

Stack_array: Stack_array.cpp 
	g++ -std=c++20 Stack_array.cpp -o Stack_array

Stack_linkedList: Stack_linkedList.cpp 
	g++ -std=c++20 Stack_linkedList.cpp -o Stack_linkedList

Graph: Graph.cpp
	g++ -std=c++20 Graph.cpp -o Graph

clean: # Delete all builded files
	rm -f DisjointSet Hashmap Heap LinkedList PriorityQueue Queue Stack_array Stack_linkedList Graph