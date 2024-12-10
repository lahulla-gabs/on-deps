include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int isDir(const char *path){
	
	struct stat stats;
	if(stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
	{return 1;} return 0;
}

int main(){
	system("mkdir template239704")
	
}
