#include "Database.h"
std::stringstream Database::getResult;
Database::Database():db(database(nullptr, sqlite3_close))
{
}

Database::Database(const std::string& name) :db(OpenDatabase(name))
{
}

statement Database::CreateStatement(sqlite3* db, const std::string& sql)
{
	if (db)
	{
		sqlite3_stmt* stmt = nullptr;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);
		if (rc != SQLITE_OK)
		{
			std::cerr << "Unable to create statement: " << sql << " : " << sqlite3_errmsg(db);
			std::exit(EXIT_FAILURE);
		}
		return statement(stmt, sqlite3_finalize);
	}
}

void Database::Run(sqlite3_stmt* stmt, stmt_callback callback = stmt_callback())
{
	if (stmt)
	{
		using reset_guard = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_reset)>;
		auto reset = reset_guard(stmt, &sqlite3_reset);
		auto next_step = [&](int rc) {
			if (rc == SQLITE_OK || rc == SQLITE_DONE)
			{
				return false;
			}
			else if (rc == SQLITE_ROW)
			{
				if (callback) return callback(stmt);
			}
			return false;
		};
		while (next_step(sqlite3_step(stmt)));
	}
}

sqlite3* Database::GetDatabase()
{
	return db.get();
}

database Database::OpenDatabase(const std::string& name)
{
	const char* databaseName = name.c_str();
	sqlite3* db = nullptr;
	auto rc = sqlite3_open(databaseName, &db);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Unable to open database " << name << " : " << sqlite3_errmsg(db);
		sqlite3_close(db);
		std::exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Opened database " << name << " with succes"<<std::endl;
	}
	if (sqlite3_enable_load_extension(db, 1) != SQLITE_OK)
	{
		std::cerr << "Error in enabling extension loading";
	}
	if (sqlite3_load_extension(db, "spellfix.dll", "sqlite3_spellfix_init", NULL) != SQLITE_OK)
	{
		std::cerr << "Error in loading extension";
	}
	if (sqlite3_enable_load_extension(db, 0) != SQLITE_OK)
	{
		std::cerr << "Error in disabling extension loading";
	}
	return database(db, sqlite3_close);
}

bool Database::DumpCurrentRow(sqlite3_stmt* stmt)
{
	if (stmt)
	{
		for (int i = 0; i < sqlite3_column_count(stmt); ++i)
		{
			auto columntype = sqlite3_column_type(stmt, i);
			if (columntype == SQLITE_NULL)
			{
				//std::cout << "<NULL>";
			}
			else if (columntype == SQLITE_INTEGER)
			{
				getResult << sqlite3_column_int64(stmt, i);
			}
			else if (columntype == SQLITE_FLOAT)
			{
				getResult << sqlite3_column_double(stmt, i);
			}
			else if (columntype == SQLITE_TEXT)
			{
				auto first = sqlite3_column_text(stmt, i);
				std::size_t s = sqlite3_column_bytes(stmt, i);
				getResult << (s > 0 ? std::string((const char*)first, s) : "");
			}
			else if (columntype == SQLITE_BLOB)
			{
				//std::cout << "<BLOOOB>";
			}
			getResult << "|";
		}
		getResult << std::endl;
		return true;
	}
	return false;
}
