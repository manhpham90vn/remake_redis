#ifndef DB_H
#define DB_H

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *data;
    int size;
    int capacity;
} Database;

Database* create_database();
void set(Database *db, const char *key, const char *value);
const char* get(Database *db, const char *key);
void free_database(Database *db);

#endif
