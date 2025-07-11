//random code


/*
const char *data = "Callback function called";
char *zErrMsg = 0;
int db_exec(sqlite3 *, const char *);
static int callback(void *data, int argc, char **argv, char **azColName);
*/

//serial prints query result
int db_exec(sqlite3 *db, const char *sql)
{
    Serial.println('\n');
    int rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        Serial.printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return rc;
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        Serial.printf("%s - %s ", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    globalArgv = argv;

    return 0;
}
