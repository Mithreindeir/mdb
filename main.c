#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "db.h"
#include "disk.h"
#include "ser.h"

int main(int argc, char ** argv)
{
	if (argc < 2) {
		printf("Usage: %s filename\n", argv[0]);
		return 1;
	}
	struct disk *d = disk_open(argv[1]);

	struct db_node *rt = deserialize(d);
	char input[256];
	struct db_key ink;
	while (1) {
		printf(">");
		fgets(input, 256, stdin);
		char * cmd = strtok(input, " \n");
		if (!cmd) continue;
		char *args[3] = { NULL, NULL, NULL };
		int iter = 0;
		while (iter < 3 && (args[iter++]=strtok(NULL, " \n")));
		//printf("command: %s, %s %s %s\n", cmd, args[0], args[1], args[2]);
		if (!strcmp(cmd, "set") && args[0] && args[1]) {
			ink.key = args[0];
			ink.ksize = strlen(args[0]);
			ink.psize = strlen(args[1])+1;
			ink.ptr = malloc(ink.psize);
			memcpy(ink.ptr, args[1], ink.psize-1);
			((char*)ink.ptr)[ink.psize-1] = 0;
			rt = db_insert(rt, ink);
			printf("%s -> %s\n", args[0], args[1]);
		} else if (!strcmp(cmd, "get") && args[0]) {
			ink.key = args[0];
			ink.ksize = strlen(args[0]);
			ink.ptr = NULL;
			char * str = db_lookup_value(rt, ink);
			printf("%s -> %s\n", args[0], str);
		} else if (!strcmp(cmd, "dump")) {
			db_node_print(rt, 0);
		} else if (!strcmp(cmd, "quit")) {
			break;
		} else {
			printf("Invalid command\n");
			break;
		}
	}
	db_node_print(rt, 0);

	serialize(rt, d);
	disk_write(d);

	db_node_destroy(rt);
	disk_destroy(d);
	return 0;
}
