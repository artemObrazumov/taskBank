#ifndef CONTROLWORKCONTENTDATABASE_H
#define CONTROLWORKCONTENTDATABASE_H

#include "databases/controlworkdatabase.h"
#include "models/Variant.h"
#include "models/taskgroup.h"

class ControlWorkContentDatabase
{
private:

    sqlite3* database;
    int createVariant();
    void addTasksToVariant(int id, std::vector<TaskGroup> taskGroups);

public:

    ControlWorkContentDatabase(ControlWork &work);
    ~ControlWorkContentDatabase();

    std::vector<TaskGroup> getTaskGroupsFromDatabase(int id);
    std::vector<Tag> getTaskTagsFromDatabase(int id);
    std::vector<Tag> getAllTagsFromDatabase();
    Task* getTaskFromDatabase(int id);
    Tag* getTagFromDatabase(int tagId);
    int addTaskGroupToDatabase();
    int addTaskToDatabase(int groupId);
    void deleteTaskFromDatabase(int id);
    void saveTaskToDatabase(int taskId, std::string content, std::string answer);
    int createTagInDatabase(std::string title);
    void deleteTaskTags(int taskId);
    void saveTaskTag(int taskId, int tagId);
    std::vector<TaskGroup> getNotEmptyTaskGroups();
    std::vector<Tag> getNotEmptyTaskTags();
    std::vector<TaskGroup> getRandomTasksFromGroups(std::vector<int> groups, std::vector<int> tags);
    int saveVariant(std::vector<TaskGroup> taskGroups);
    std::vector<Variant> getVariantsFromDatabase();
    std::vector<TaskGroup> getVariantTasks(int id);
};

#endif // CONTROLWORKCONTENTDATABASE_H
