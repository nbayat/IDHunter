#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#define MAX_PATH_LEN 1024
#define MAX_BUF_LEN 1024

int main(int argc, char **argv) {
    char command[MAX_PATH_LEN + MAX_BUF_LEN];
    char buffer[MAX_BUF_LEN];
    char app_name[MAX_PATH_LEN];
    char bundle_id[MAX_BUF_LEN];
    int i, len, match_found = 0;

    if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--Help") == 0 || strcmp(argv[1], "-H") == 0)
    {
        printf("\033[33mUsage:\033[0m %s <app_name>\n", argv[0]);
        return 1;
    }

    // Get app name from command line argument
    strncpy(app_name, argv[1], MAX_PATH_LEN);

    // Check if app name starts with lowercase letter and convert to uppercase
    if (islower(app_name[0])) {
        app_name[0] = toupper(app_name[0]);
    }

    // If app name does not end with .app, append it
    if (strlen(app_name) < 4 || strcmp(app_name + strlen(app_name) - 4, ".app") != 0) {
        strcat(app_name, ".app");
    }

    // Get list of installed applications in /Applications and /System/Applications
    char *applications_paths[] = { "/Applications", "/System/Applications" };
    for (i = 0; i < 2; i++) {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(applications_paths[i])) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                    // Check if entered app name matches installed application name
                    if (strstr(ent->d_name, app_name) != NULL) {
                        match_found = 1;
                        strcpy(app_name, ent->d_name);
                        break;
                    }
                }
            }
            closedir(dir);
        } else {
            printf("\033[31mError:\033[0m failed to open directory %s\n", applications_paths[i]);
            return 1;
        }

        // If entered app name matches installed application name, retrieve its bundle ID
        if (match_found) {
            // Format the system command to retrieve bundle id
            snprintf(command, sizeof(command), "mdls -name kMDItemCFBundleIdentifier \"%s/%s\"", applications_paths[i], app_name);

            // Execute the system command and capture output
            FILE *fp = popen(command, "r");
            if (fp == NULL) {
                printf("\033[31mError:\033[0m failed to execute command.\n");
                return 1;
            }

            // Read the output and extract the bundle id
            while (fgets(buffer, sizeof(buffer), fp)) {
                len = strlen(buffer);
                for (i = 0; i < len; i++) {
                    if (buffer[i] == '"') {
                        strncpy(bundle_id, buffer+i+1, MAX_BUF_LEN);
                        bundle_id[strlen(bundle_id)-2] = '\0';
                        break;
                    }
                }
            }

            // Close the command output stream
            pclose(fp);

            // Check if bundle id was retrieved and print it
            if (strlen(bundle_id) > 0) {
                printf("Bundle ID for %s:\033[32m %s\n\033[0m", app_name, bundle_id);
                return 0;
            } else {
                printf("\033[31mError:\033[0m failed to retrieve bundle ID for %s.\n", app_name);
                return 1;
            }
        }
    }

    // If no match was found, print error message
    printf("\033[31mError:\033[0m %s is not an installed application.\n", app_name);
    return 1;
}
