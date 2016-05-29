#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../headers/tracer.h"
#include "../headers/communicator.h"
#include "../headers/finder.h"


void traceme(int argc, char* argv[]){
	FILE* fd = initiate_communication(argc, argv);

    int pn_size = 0;
    for(int i=1; i<argc; i++){
        pn_size += strlen(argv[i]) + 1;
    }
    pn_size+=1;

    char* pn = malloc( sizeof(char)*pn_size);

    strcpy(pn, argv[1]);
    for(int i=2; i < argc; i++){
        strcat(pn, " ");
        strcat(pn, argv[i]);
    }

	trace(argc, argv, pn, fd);

    close_communication(fd, pn);
    free(pn);
}

int main (int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s -f filename_to_find | -m md5_of_file | command_to_execute\n", argv[0]);
        return 1;
    }

	int opt;
	while ((opt = getopt (argc, argv, "f:m:")) != -1){
		switch (opt){
		case 'f':
			printf ("Finding the file: %s\n", optarg);
			return find_recipe_by_name(optarg);
		case 'm':
		    printf ("Looking for md5 of the file %s\n", optarg);
		    return find_recipe_by_md5(optarg);
	    }
    }
	traceme(argc, argv);
    return 0;
}
