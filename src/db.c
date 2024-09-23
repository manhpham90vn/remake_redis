#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

Database *create_database()
{
    Database *db = malloc(sizeof(Database));
    db->size = 0;
    db->capacity = 10;
    db->data = malloc(sizeof(KeyValue) * db->capacity);
    return db;
}

void set(Database *db, const char *key, const char *value)
{
    for (int i = 0; i < db->size; i++)
    {
        if (strcmp(db->data[i].key, key) == 0)
        {
            if (strcmp(db->data[i].value, value) != 0)
            {
                free(db->data[i].value);
                db->data[i].value = strdup(value);
            }
            return;
        }
    }

    if (db->size == db->capacity)
    {
        int new_capacity = db->capacity + db->capacity / 2;
        KeyValue *new_data = realloc(db->data, sizeof(KeyValue) * new_capacity);
        if (new_data == NULL)
        {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return;
        }
        db->data = new_data;
        db->capacity = new_capacity;
    }

    db->data[db->size].key = strdup(key);
    db->data[db->size].value = strdup(value);
    db->size++;
}

const char *get(Database *db, const char *key)
{
    if (db == NULL || key == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < db->size; i++)
    {
        if (strcmp(db->data[i].key, key) == 0)
        {
            return db->data[i].value;
        }
    }

    return NULL;
}

void delete(Database *db, const char *key)
{
    if (db == NULL || key == NULL)
    {
        return;
    }

    for (int i = 0; i < db->size; i++)
    {
        if (strcmp(db->data[i].key, key) == 0)
        {
            free(db->data[i].key);
            free(db->data[i].value);
            if (i < db->size - 1)
            {
                db->data[i] = db->data[db->size - 1];
            }
            db->size--;
            return;
        }
    }
}

void free_database(Database *db)
{
    for (int i = 0; i < db->size; i++)
    {
        free(db->data[i].key);
        free(db->data[i].value);
    }
    free(db->data);
    free(db);
}
