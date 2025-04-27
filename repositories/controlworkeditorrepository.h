#ifndef CONTROLWORKEDITORREPOSITORY_H
#define CONTROLWORKEDITORREPOSITORY_H

#include <sqlite3.h>
#include "../models/controlwork.h"
#include "databases/controlworkcontentdatabase.h"
#include "databases/controlworkdatabase.h"
#include "models/taskgroup.h"
#include "utils/controlworkmetadataeditor.h"
#include "utils/controlworkpdfexporter.h"

class controlWorkEditorRepository
{
private:

    ControlWorkDatabase database;
    ControlWorkContentDatabase* content = nullptr;
    ControlWorkMetadataEditor metadataEditor;
    ControlWorkPdfExporter* controlWorkPdfExporter = nullptr;
    ControlWork* work;
    std::vector<TaskGroup> groups;
    std::vector<Tag> tags;
    int workId;

    void loadControlWork();
public:

    controlWorkEditorRepository(int workId);
    ~controlWorkEditorRepository();

    int addTaskGroup();
    int addTask(int groupId);
    Task* getTaskById(int id);
    ControlWork* getControlWork() {
        return work;
    }
    std::vector<TaskGroup> getTaskGroups() {
        return groups;
    }
    std::vector<Tag> getTags() {
        return tags;
    }
    void deleteTask(int id);
    void saveTask(int taskId, std::string content, std::string answer);
    Tag* getTagById(int tagId);
    int createTag(std::string title);
    void deleteTaskTags(int taskId);
    void saveTaskTag(int taskId, int tagId);
    std::vector<Tag> getTaskTags(int taskId);
    std::vector<TaskGroup> getNotEmptyTaskGroups();
    std::vector<Tag> getNotEmptyTaskTags();
    int generateAndSaveVariants(std::vector<int> groups, std::vector<int> tags, int variants, std::string title);
    std::vector<Variant> getVariants();
};

#endif // CONTROLWORKEDITORREPOSITORY_H
