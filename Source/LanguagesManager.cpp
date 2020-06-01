#include "LanguagesManager.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include <JuceHeader.h>

wstring LanguagesManager::DBname = L"";

const string LanguagesManager::LangsTableName = "Languages";
const string LanguagesManager::CurrentLangTable = "CurrentLanguage";
const string LanguagesManager::CurLangField = "Id";
const string LanguagesManager::LangField = "Language";

const string LanguagesManager::Properties::INTERRUPTS = "Interrupts";
const string LanguagesManager::Properties::NOISE = "Noise";
const string LanguagesManager::Properties::CRACKLING = "Crackling";
const string LanguagesManager::Properties::BUZZING = "Buzzing";
const string LanguagesManager::Properties::FREQUENCY = "Frequency";
const string LanguagesManager::Properties::DURATION = "Duration";
const string LanguagesManager::Properties::RANDOM_FACTOR ="Random";
const string LanguagesManager::Properties::VOLUME = "Volume";
const string LanguagesManager::Properties::CLIPPING_FACTOR = "Clipping";
const string LanguagesManager::Properties::DENSITY = "Density";
const string LanguagesManager::Properties::LOCAL_LANG_FIELD = "LocalLanguage";
const string LanguagesManager::Properties::MUTE = "Mute";
const string LanguagesManager::Properties::UNMUTE = "Unmute";
const string LanguagesManager::Properties::TURN_OFF = "Turn off";
const string LanguagesManager::Properties::TURN_ON = "Turn on";
const string LanguagesManager::Properties::DEFAULT = "DefaultValue";
const string LanguagesManager::Properties::ACTIVE = "Active";
const string LanguagesManager::Properties::ZEROIZE = "Zeroize";

vector<wstring> LanguagesManager::getProperty(string property, wstring *localLanguage, bool order)
{
	vector<wstring> answer = vector<wstring>(0);
	ifstream f(DBname);
	if (!f.good())
	{
		if (!setDBname())
		{
			return vector<wstring>(0);
		}
	}
	string* sql = new string("SELECT "+property +" FROM " + LangsTableName);
	if (localLanguage != nullptr)
		*sql += " WHERE " + LanguagesManager::Properties::LOCAL_LANG_FIELD + "=\""+ convertToString(*localLanguage) +"\"";
	if (order)
		*sql += " ORDER BY " + LangField + " ASC";
	sqlite3* DB = 0;
	if (sqlite3_open16(DBname.c_str(), &DB))
	{
		answer = vector<wstring>(0);
	}
	else
	{
		sqlite3_stmt* stmt;
		if (sqlite3_prepare(DB, sql->c_str(), -1, &stmt, 0) == SQLITE_OK)
		{
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				const unsigned char* lang = sqlite3_column_text(stmt, 0);
				string langStr = reinterpret_cast<char*>(const_cast<unsigned char*>(lang));
				answer.push_back(convertToUTF8(langStr));
			}
			sqlite3_finalize(stmt);
		}
	}

	sqlite3_close(DB);

	return answer;
}

void LanguagesManager::setCurrentLanguage(wstring localLanguage)
{
	ifstream f(DBname);
	if (!f.good())
	{
		if (!setDBname())
		{
			return;
		}
	}
	vector<wstring> vec= getProperty("Id", &localLanguage);
	if (vec.size() <= 0)
		return;
	int id = String(vec[0].c_str()).getIntValue();
	string sql = "UPDATE " + CurrentLangTable + " SET " + CurLangField + "="+to_string(id)+";";
	sqlite3* DB = 0;
	if (!sqlite3_open16(DBname.c_str(), &DB))
	{
		sqlite3_stmt* stmt;
		if (sqlite3_prepare(DB, sql.c_str(),-1, &stmt, nullptr) == SQLITE_OK)
		{
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
	}
	sqlite3_close(DB);

	return;
}

wstring* LanguagesManager::getCurrentLanguage()
{
	wstring* answer;
	ifstream f(DBname);
	if (!f.good())
	{
		if (!setDBname())
		{
			return nullptr;
		}
	}
	const string sql = string("SELECT " + Properties::LOCAL_LANG_FIELD + " FROM " + LangsTableName + " INNER JOIN "+ CurrentLangTable +" ON "+ LangsTableName+".[Id]="+ CurrentLangTable+".["+CurLangField+"];");
	sqlite3* DB = 0;
	if (sqlite3_open16(DBname.c_str(), &DB))
	{
		answer = nullptr;
	}
	else
	{
		sqlite3_stmt* stmt;
		if (sqlite3_prepare(DB, sql.c_str(), sql.size(), &stmt, nullptr)==SQLITE_OK)
		{
			if (sqlite3_step(stmt) == SQLITE_ROW)
			{
				const unsigned char* lang = sqlite3_column_text(stmt, 0);
				String langStr = string(reinterpret_cast<char*>(const_cast<unsigned char*>(lang)));
				answer= new wstring(langStr.toWideCharPointer());
				sqlite3_finalize(stmt);
			}
		}
	}

	sqlite3_close(DB);

	return answer;
}

bool LanguagesManager::setDBname()
{
	DBname = getFileDir() + L"\\/" + L"sqlite.db";
	if (DBname[0] == '?')
		DBname = DBname.substr(1, DBname.length() - 1);
	ifstream f(DBname);
	return f.good();
}

string LanguagesManager::convertToString(const wstring& str)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(str);
}

wstring LanguagesManager::convertToUTF8(const string& str)
{
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

wstring LanguagesManager::getFileDir()
{
	wstring *outFile =new wstring(L"");
	if (isNeeded(L"Year Project.dll", outFile))
	{
		return outFile->substr(0, outFile->find_last_of(L"\\/"));
	}
	else
	{
		isNeeded(L"Year Project.vst3", outFile);
		return outFile->substr(0, outFile->find_last_of(L"\\/"));
	}

	return L"";
}

bool LanguagesManager::isNeeded(wstring fileName, wstring* outFile)
{
	HINSTANCE hm = GetModuleHandleW(fileName.c_str()); // get the handle to the module
	WCHAR* path = new WCHAR[MAX_PATH];
	GetModuleFileNameW(hm, path, MAX_PATH); // get the full path
	*outFile =wstring(path);

	return outFile->substr(outFile->find_last_of(L"\\/")+1) == fileName;
}