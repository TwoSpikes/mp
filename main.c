#if 0
	env bash ./build.sh;
	if [[ $? -ge 0 ]]; then
		install ./a.out $PREFIX/bin/playmusic;
		playmusic;
	fi;
	exit $?;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdarg.h>
#include <dirent.h>
#include <unistd.h>

#include <sys/types.h>

#define RESET_COLOR "\033[0m"
#define GRAY_COLOR "\033[90m"
#define RED_COLOR "\033[91m"
#define GREEN_COLOR "\033[92m"
#define YELLOW_COLOR "\033[93m"
#define BLUE_COLOR "\033[94m"
#define VIOLET_COLOR "\033[95m"
#define LIGHT_BLUE_COLOR "\033[96m"
#define WHITE_COLOR "\033[97m"
#define GRAY_BACK_COLOR "\033[100m"
#define RED_BACK_COLOR "\033[101m"
#define GREEN_BACK_COLOR "\033[102m"
#define YELLOW_BACK_COLOR "\033[103m"
#define BLUE_BACK_COLOR "\033[104m"
#define VIOLET_BACK_COLOR "\033[105m"
#define LIGHT_BLUE_BACK_COLOR "\033[106m"
#define WHITE_BACK_COLOR "\033[107m"
#define BOLD_COLOR "\033[1m"
#define NON_BOLD_COLOR "\033[22m"

#define ERROR_MESSAGE_TYPE BOLD_COLOR RED_COLOR"error"RESET_COLOR

#define MAX_STRING_SIZE 1000

void vsystem(char *format, ...) {
	char *command;
	{
		va_list vp;
		va_start(vp, format);
		vasprintf(&command, format, vp);
	}
	system(command);
}

void mp_common(char *message_type, char *message) {
	fprintf(stderr, "%s: %s", message_type, message);
}

void mp_error(char *format, ...) {
	char *message;
	{
		va_list vp;
		va_start(vp, format);
		vasprintf(&message, format, vp);
	}
	mp_common(ERROR_MESSAGE_TYPE, message);
}

int main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	char *command = malloc(sizeof(char)*MAX_STRING_SIZE);
	unsigned int tick = 0;
	(void) tick;
	bool to_exit = false;
	while (!to_exit) {
		printf("> ");
		scanf("%s", command);
		if (!strcmp(command, "c")) {
			system("clear");
			continue;
		}
		if (!strcmp(command, "l")) {
			DIR *dir;
			struct dirent *file;
			dir = opendir("./");
			if (!dir) {
				mp_error("cannot open directory: %s", getcwd("./", MAX_STRING_SIZE));
			}
			while ((file = readdir(dir))) {
				printf("%s [%d] %d\n", file->d_name, file->d_type, file->d_reclen);
			}
			continue;
		}
		if (!strcmp(command, "e")) {
			to_exit = true;
			continue;
		}
		if (!strcmp(command, "a")) {
			DIR *dir;
			struct dirent *file;
			dir = opendir("./");
			if (!dir) {
				mp_error("cannot open directory: %s", getcwd("./", MAX_STRING_SIZE));
			}
			while ((file = readdir(dir))) {
				printf("Playing %s...\n", file->d_name);
				if (file->d_type == 8) {
					vsystem("mpv '%s'", file->d_name);
				}
			}
			continue;
		}
		mp_error("not an mp command: %s\n", command);
		tick++;
	}
	return 0;
}
