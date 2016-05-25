#include <stdio.h>
#include <unistd.h>

#include "../headers/tracer.h"
#include "../headers/communicator.h"

int main (int argc, char *argv[]){

    if (argc < 2){
        printf("Usage: %s -f filename_to_find | command_to_execute\n", argv[0]);
        return 1;
    }

	int opt;
	while ((opt = getopt (argc, argv, "f:")) != -1){
		switch (opt){
		case 'f':
			printf ("Finding the file: %s\n", optarg);
			break;
		default:
			break;
		}
	}

	FILE* fd = initiate_communication(argc, argv);

	trace(argc, argv, argv[1], fd);

    close_communication(fd);
    return 0;
}