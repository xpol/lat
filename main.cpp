#include <archive.h>

int main(int argc, char* argv[]) {
    printf("%s\n", archive_version_string());
    return 0;
}
