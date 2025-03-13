#include "controlworkeditorrepository.h"

controlWorkEditorRepository::controlWorkEditorRepository(int workId): workId(workId) {
    loadControlWork();
}

void controlWorkEditorRepository::loadMetadata() {
}

void controlWorkEditorRepository::loadControlWork() {

    loadMetadata();
}

std::string controlWorkEditorRepository::loadControlWorkPath() {
    const char* sql = "SELECT * FROM control_works;";
    sqlite3_stmt* stmt;
}
