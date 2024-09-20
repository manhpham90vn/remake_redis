#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

Database* create_database() {
    Database *db = malloc(sizeof(Database));
    db->size = 0;
    db->capacity = 10;
    db->data = malloc(sizeof(KeyValue) * db->capacity);
    return db;
}

void set(Database *db, const char *key, const char *value) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->data[i].key, key) == 0) {
            free(db->data[i].value);
            db->data[i].value = strdup(value);
            return;
        }
    }

    if (db->size == db->capacity) {
        db->capacity *= 2;
        db->data = realloc(db->data, sizeof(KeyValue) * db->capacity);
    }

    db->data[db->size].key = strdup(key);
    db->data[db->size].value = strdup(value);
    db->size++;
}

const char* get(Database *db, const char *key) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->data[i].key, key) == 0) {
            return db->data[i].value;
        }
    }
    return NULL;
}

void free_database(Database *db) {
    for (int i = 0; i < db->size; i++) {
        free(db->data[i].key);
        free(db->data[i].value);
    }
    free(db->data);
    free(db);
}
