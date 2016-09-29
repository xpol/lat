#include <archive.h>
#include <archive_entry.h>
#include <iconv.h>
#include <uchardet/uchardet.h>

#include <iostream>
#include <locale>
#include <memory>
#include <string>

struct Chardet {
    Chardet() : d(uchardet_new()) {}
    ~Chardet() {
        uchardet_delete(d);
    }
    Chardet& operator <<(const std::string& s) {
        uchardet_handle_data(d, s.data(), s.size());
        return *this;
    }
    std::string endoding() {
        uchardet_data_end(d);
        return uchardet_get_charset(d);
    }

    void reset() {
        uchardet_reset(d);
    }
private:
    uchardet_t d;
};



int main(int argc, char* argv[]) {
    if (argc < 2)
        return 1;

    setlocale(LC_ALL, "");
    struct archive *a = archive_read_new();
    std::unique_ptr<struct archive, decltype(&archive_read_free)> ar(a, archive_read_free);
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    int r = archive_read_open_filename(a, argv[1], 16384);

    if (r != ARCHIVE_OK) {
        std::cerr << archive_error_string(a) << std::endl;
        return 1;
    }

    Chardet cd;
    struct archive_entry * ae = nullptr;
    while ((r = archive_read_next_header(a, &ae)) == ARCHIVE_OK) {
        std::string s(archive_entry_pathname(ae));
        cd << s;
        std::cout << s << std::endl;
    }

    std::cout << cd.endoding() << std::endl;

    return 0;
}
