/*
*  EngineLog.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "EngineLog.h"
#include <sstream>
#include <ctime>

using namespace std;

namespace small3d {

	EngineLog::EngineLog(ostream &stream) {
		logStream = &stream;
	}

	EngineLog::~EngineLog() {
		this->append(info, "Logger getting destroyed");

	}

	void EngineLog::append(const EngineLogLevel level, const string message) {

		ostringstream dateTimeOstringstream;

		time_t now;

		time(&now);

		tm *t;
#ifdef _WIN32
		t = new tm();
		localtime_s(t, &now);
#else
		t = localtime(&now);
#endif
		char buf[20];

		strftime(buf, 20,"%Y-%m-%d %H:%M:%S", t);

// localtime (used on Linux) does not allocate memory, but
// returns a pointer to a pre-existing location. Hence,
// we should not delete it.
#ifdef _WIN32
		delete t;
#endif

		dateTimeOstringstream << buf;

		string indicator;
		switch (level) {
		case info:
			indicator = "INFO";
			break;
		case debug:
			indicator = "DEBUG";
			break;
		case error:
			indicator = "ERROR";
			break;
		default:
			indicator = "";
			break;
		}

		*logStream << dateTimeOstringstream.str().c_str() << " - " << indicator << ": " << message.c_str() << endl;
	}

} 