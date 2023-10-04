#pragma once
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>


using database = std::unique_ptr<sqlite3, decltype(&sqlite3_close)>;
using statement = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;
using stmt_callback = std::function<bool(sqlite3_stmt*)>;
class Database
{
public:
	static std::stringstream getResult;
	Database();
	Database(const std::string& name);
	statement CreateStatement(sqlite3* db, const std::string& sql);
	void Run(sqlite3_stmt* stmt, stmt_callback callback);
	sqlite3* GetDatabase();
	database OpenDatabase(const std::string& name);
	static bool DumpCurrentRow(sqlite3_stmt* stmt);

private:
	database db;
};

