#include <iostream>

#include "GraphNode.h"
#include "common.h"

int main()
{
	std::cout << "Welcome to the A* and NavMesh POC for Ubisoft Graduate Program at Annecy." << std::endl;

	auto n = GraphNode<Vec2f>(0);
	Vec2f pos(3.0, 4.0);
	n.setInfo(&pos);

	std::cout << "GraphNode correctly constructed and having position=(" << n.getInfo()->x << ", " << n.getInfo()->y << ")." << std::endl;

	char stop;
	std::cin >> stop;
	return 0;
}