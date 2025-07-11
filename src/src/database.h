#ifndef database_h
#define database_h

#include "config.h"
#include "queries.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

sqlite3 *db;

char **globalArgv;

/*!
  @brief prepare and bind sql statement before step
    @param db reference to sqlite3 db
    @param sql char* sql statment with delmiter '?' for where to insert
    @param selection char* to insert into sql
*/
sqlite3_stmt *prepbindStmt(sqlite3 *db, const char *sql, char *selection)
{
    sqlite3_stmt *stmt;
    int result;

    //Serial.println(sql);

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        Serial.println("Prepare failed");
        Serial.println(result);
        return NULL;
    }
    else if (result == SQLITE_OK)
    {
       //Serial.println("Prepare succeeded");
    }

    result = sqlite3_bind_text(stmt, 1, selection, -1, SQLITE_STATIC);
    if (result != SQLITE_OK)
    {
        Serial.println("bind failed");
        Serial.println(result);
        return NULL;
    }
    else if (result == SQLITE_OK)
    {
        //Serial.println("boind succeeded");
    }

    return stmt;
}

sqlite3_stmt *prepStmt(sqlite3 *db, const char *sql)
{
    sqlite3_stmt *stmt;
    int result;

    Serial.println(sql);

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        Serial.println("Prepare failed");
        Serial.println(result);
        return NULL;
    }
    else if (result == SQLITE_OK)
    {
        Serial.println("Prepare Succeeded");
    }
    return stmt;
}

String execSimpleStmt(sqlite3_stmt *stmt)
{
    int stepRC = sqlite3_step(stmt);
    const unsigned char *stmtReturn;

    if (stepRC == SQLITE_ROW)
    {
        //Serial.println("Step succeeded");

        stmtReturn = sqlite3_column_text(stmt, 0);
        String dataToPrint(reinterpret_cast<const char *>(stmtReturn));
        //Serial.println(dataToPrint);
        return dataToPrint;
    }
    else
    {
        Serial.println("Step failure");
        Serial.println(stepRC);
        String failure = "step failure";
        return failure;
    }

    sqlite3_finalize(stmt);

}

std::vector<String> exec1byX(sqlite3_stmt *stmt)
{
    int count = 0;
    std::vector<String> argumentVECTOR;

    int columnCount = sqlite3_column_count(stmt);
    Serial.print("Columns: ");
    Serial.println(columnCount);

    while (1)
    {
        int RC = sqlite3_step(stmt);
        if (RC == SQLITE_ROW)
        {
            count = count + 1;
            //     char *stmtReturn = (char *)sqlite3_column_text(stmt, 0);
            // Serial.println(stmtReturn);
            String string = String((char *)sqlite3_column_text(stmt, 0));
            // Serial.println(string);
            argumentVECTOR.push_back(string);
        }
        else if (RC != SQLITE_ROW)
        {
            Serial.println(count);
            break;
        }
    }
    return argumentVECTOR;

    sqlite3_finalize(stmt);
}

std::vector<String> execXby1(sqlite3_stmt *stmt)
{
    std::vector<String> argumentVECTOR;
    int columnCount = sqlite3_column_count(stmt);

    int RC = sqlite3_step(stmt);
    if (RC == SQLITE_ROW)
    {
        for (int i = 0; i < columnCount; i++)
        {
            String string = String((char *)sqlite3_column_text(stmt, i));
            argumentVECTOR.push_back(string);
        }
    }
    else if (RC != SQLITE_ROW)
    {
    }

    return argumentVECTOR;

    sqlite3_finalize(stmt);
}

#endif
