#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <locale>
#include <codecvt>

std::string toutf8(std::wstring str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    return utf8_conv.to_bytes(str);
}

int main(int argc, char* argv[]) {
    ssize_t size;
    int r;
    char buff[128] = {0};
    struct archive_entry * ae = NULL;
    struct archive *a = NULL;

    if (argc < 2)
        return 1;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    r = archive_read_open_filename(a, argv[1], 16384);

    if (r != ARCHIVE_OK) {
        printf("%s\n", archive_error_string(a));
        goto errexit;
    }
    {
        while ((r = archive_read_next_header(a, &ae)) == ARCHIVE_OK) {
            printf("%s\n", archive_entry_pathname(ae));
            printf("%d files\n", archive_file_count(a));
        }
        if (r != ARCHIVE_OK) {
            printf("%s\n", archive_error_string(a));
            goto errexit;
        }
    }
errexit:
    archive_read_close(a);
    archive_read_free(a);
    return 0;
}
