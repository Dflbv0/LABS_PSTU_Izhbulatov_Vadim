#include <cstdio>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

struct Team {
    char name[100], city[100];
    int players, points;
};

const char* dataFile = "teams.bin";
const char* tempFile = "teams.tmp";
using File = unique_ptr<FILE, int (*)(FILE*)>;

File openFile(const char* path, const char* mode) {
    File file(fopen(path, mode), fclose);
    if (!file) throw runtime_error(string("Не открыть файл ") + path);
    return file;
}

Team inputTeam() {
    Team team{};
    cout << "Название и город (каждое с новой строки), игроки и очки:\n";
    if (!(cin >> ws).getline(team.name, sizeof team.name) ||
        !cin.getline(team.city, sizeof team.city) ||
        !(cin >> team.players >> team.points) || team.players < 0)
        throw runtime_error("Ошибка ввода команды.");
    return team;
}

void writeTeam(FILE* out, const Team& team) {
    if (fwrite(&team, sizeof team, 1, out) != 1)
        throw runtime_error("Ошибка записи.");
}

bool readTeam(FILE* in, Team& team) {
    size_t bytes = fread(&team, 1, sizeof team, in);
    if (bytes == sizeof team) return true;
    if (bytes == 0 && feof(in) && !ferror(in)) return false;
    throw runtime_error("Запись повреждена или файл не прочитан.");
}

void commit(File& out) {
    if (fclose(out.release()) != 0) throw runtime_error("Ошибка записи.");
    filesystem::rename(tempFile, dataFile);
}

void createFile(int count) {
    File out = openFile(tempFile, "wb");
    for (int i = 0; i < count; ++i) writeTeam(out.get(), inputTeam());
    commit(out);
}

void printFile() {
    File in = openFile(dataFile, "rb");
    Team team{};
    int number = 0;
    while (readTeam(in.get(), team))
        cout << ++number << ". " << team.name << " | " << team.city
             << " | " << team.players << " | " << team.points << '\n';
    if (number == 0) cout << "Файл пуст.\n";
}

bool belowLimit(const Team& team, int limit) {
    return team.points < limit;
}

void removeTeams(int limit) {
    File in = openFile(dataFile, "rb"), out = openFile(tempFile, "wb");
    Team team{};
    while (readTeam(in.get(), team))
        if (!belowLimit(team, limit)) writeTeam(out.get(), team);
    in.reset();
    commit(out);
}

void prependTeams(const Team& first, const Team& second) {
    File in = openFile(dataFile, "rb"), out = openFile(tempFile, "wb");
    writeTeam(out.get(), first);
    writeTeam(out.get(), second);
    Team team{};
    while (readTeam(in.get(), team)) writeTeam(out.get(), team);
    in.reset();
    commit(out);
}

int main() {
    try {
        int count, limit;
        cout << "Число исходных команд (не менее 5):\n";
        if (!(cin >> count) || count < 5) return 1;
        createFile(count);
        cout << "Исходный файл (команда | город | игроки | очки):\n";
        printFile();
        cout << "Минимальное число очков:\n";
        if (!(cin >> limit)) return 1;
        removeTeams(limit);
        cout << "После удаления:\n";
        printFile();
        cout << "Введите две команды для добавления в начало:\n";
        Team first = inputTeam();
        Team second = inputTeam();
        prependTeams(first, second);
        cout << "Итоговый файл:\n";
        printFile();
    } catch (const exception& error) {
        remove(tempFile);
        cerr << error.what() << '\n';
        return 1;
    }
}
