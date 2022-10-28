#include "archiver.h"

int main(int argc, char* argv[])
{
	Archiver arc;
	if (std::string(argv[1]) == "-Arc")
		arc.ProssedArchiving(argv[2], argv[3]);
	else if (std::string(argv[1]) == "-Dearc")
		arc.ProssedDearchiving(argv[2], argv[3]);
}