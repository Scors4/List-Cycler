#include "ScLogger.h"
#include <ctime>
#include <chrono>

using namespace std::chrono;

ScLogger::ScLogger()
{
	//log->open("ScListCycler.log", fstream::in | fstream::out | fstream::app);
}


ScLogger::~ScLogger()
{
	//log->close();
}

fstream* ScLogger::log = new fstream;

void ScLogger::OpenLog()
{
	log->open("ScListCycler.log", fstream::in | fstream::out | fstream::app);
}

void ScLogger::CloseLog()
{
	log->close();
}

void ScLogger::PrintToConsole(string in, bool debug, bool toLog)
{
	string st;

	st = BuildTimestamp(debug);

	st.append(in);

	st.append("\n");
	
	cout << st;

	if (toLog)
	{
		ShortPrintToLog(st);
	}
}

void ScLogger::PrintToLog(string in, bool debug, bool toConsole)
{
	string st;

	st = BuildTimestamp(debug);

	st.append(in);
	
	st.append("\n");
	
	*log << st;

	if (toConsole)
	{
		ShortPrintToConsole(st);
	}
}

void ScLogger::execFail(string in, int code)
{
	string st = BuildTimestamp(false);

	st.append("Error code: ");
	st.append(to_string(code));
	st.append(" Error: (");
	st.append(in);
	st.append(")");

	ShortPrintToConsole(st);
	ShortPrintToLog(st);

	ShortPrintToConsole("\nPress ENTER to end.");

	cin.get();

	exit(code);
}

void ScLogger::ShortPrintToConsole(string in)
{
	cout << in;
}

void ScLogger::ShortPrintToLog(string in)
{
	*log << in;
}

string ScLogger::BuildTimestamp(bool debug)
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

	string msec;
	milliseconds ms = duration_cast<milliseconds> (
		system_clock::now().time_since_epoch()
	);
	ms %= 1000;
	if (ms.count() < 10)
		msec.append("00");
	else if (ms.count() < 100)
		msec.append("0");

	msec.append(to_string(ms.count()));
	st.append(".");
	st.append(msec);

	if (debug)
		st.append(" DEBUG]: ");
	else
		st.append("]: ");

	delete(now_tm);
	now_tm = nullptr;

	return st;
}