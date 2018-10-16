#include "ScLogger.h"
#include <ctime>

ScLogger::ScLogger()
{
	log.open("ScListCyclerLog", fstream::in | fstream::out | fstream::app);
}


ScLogger::~ScLogger()
{
	log.close();
}

void ScLogger::PrintToConsole(string in, bool debug, bool toLog)
{
	time_t now = time(NULL);
	struct tm* now_tm = new tm;
	localtime_s(now_tm, &now);
	string st;

	string hr;
	st.append("[");
	if (now_tm->tm_hour < 10)
		hr.append("0");
	hr.append(to_string(now_tm->tm_hour));
	st.append(hr);
	st.append(":");
	string min;
	if (now_tm->tm_min < 10)
		min.append("0");
	min.append(to_string(now_tm->tm_min));
	st.append(min);
	st.append(":");
	string sec;
	if (now_tm->tm_sec < 10)
		sec.append("0");
	sec.append(to_string(now_tm->tm_sec));
	st.append(sec);
	if (debug)
		st.append(" DEBUG]: ");
	else
		st.append("]: ");

	st.append(in);

	st.append("\n");
	
	cout << st;

	if (toLog)
	{
		ShortPrintToLog(st);
	}


	delete(now_tm);
	now_tm = nullptr;
}

void ScLogger::PrintToLog(string in, bool debug, bool toConsole)
{

}

void ScLogger::ShortPrintToConsole(string in)
{
	cout << in;
}

void ScLogger::ShortPrintToLog(string in)
{

}