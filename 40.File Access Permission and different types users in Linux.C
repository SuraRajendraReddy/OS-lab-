#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to print the permissions in symbolic notation
void printPermissions(mode_t mode) {
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    // File path
    char filename[] = "example.txt";

    // Get file permissions
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("Error getting file status");
        return 1;
    }

    // Print file permissions
    printf("File Permissions: ");
    printPermissions(fileStat.st_mode);
    printf("\n");

    // Get file owner's username
    struct passwd *pw = getpwuid(fileStat.st_uid);
    if (pw == NULL) {
        perror("Error getting user");
        return 1;
    }
    printf("Owner: %s\n", pw->pw_name);

    // Get file owner's group name
    struct group *gr = getgrgid(fileStat.st_gid);
    if (gr == NULL) {
        perror("Error getting group");
        return 1;
    }
    printf("Group: %s\n", gr->gr_name);

    return 0;
}

