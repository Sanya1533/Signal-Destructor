#pragma once
#include <sqlite3.h>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

class LanguagesManager
{
public:

	static const string LangsTableName;

	static const string CurrentLangTable;

	static const string CurLangField;
	class Properties
	{
	public:
		static const string INTERRUPTS;
		static const string NOISE;
		static const string CRACKLING;
		static const string BUZZING;
		static const string FREQUENCY;
		static const string DURATION;
		static const string RANDOM_FACTOR;
		static const string VOLUME;
		static const string CLIPPING_FACTOR;
		static const string DENSITY;
		static const string LOCAL_LANG_FIELD;
		static const string LANGFIELD;
	};

	static vector<wstring> getProperty(string property, string* language = nullptr, bool order = false);

	static wstring* getLocalLanguage(string language);

	static wstring* getCurrentLanguage();

	static void setCurrentLanguage(wstring localLanguage);
private:
	//static const string LangsTableName;

	//static const string CurrentLangTable;

	//static const string CurLangField;

	//static const string LangField;

	static wstring DBname;

	static bool setDBname();

	static string convertToString(const wstring& str);

	static wstring convertToUTF8(const string& str);

	static wstring getFileDir();

	static bool isNeeded(wstring fileName, wstring* outFile);
};