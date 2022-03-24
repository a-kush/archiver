#include <iostream>
#include <cstring>
#include "lib/EncodeFiles.h"
#include "lib/DecodeArchive.h"
#include <iostream>

void Help() {
    std::cout << "\narchiver -c archive_name file1 [file2 ...] - заархивировать файлы fil1, file2, ... и сохранить результат в файл archive_name.\n"
       "archiver -d archive_name - разархивировать файлы из архива archive_name и положить в текущую директорию. Имена файлов должны сохраняться при архивации и разархивации.\n"
       "archiver -h - вывести справку по использованию программы.\n";
}


int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string archive_name(argv[2]);
        if (strcmp(argv[1], "-c") == 0) {
            std::vector<std::string> file_names;
            for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
                file_names.push_back(std::string(argv[i]));
            }
            EncodeFiles(archive_name, file_names);
            std::cout << "\nEncoded Successfully\n";
        } else if (strcmp(argv[1], "-d") == 0) {
            DecodeArchive(archive_name);
            std::cout << "\nDecoded Successfully\n";
        } else {
            Help();
        }

    } else {
        std::cout << "\nERROR\n";
        return -1;
    }
    return 0;
}




