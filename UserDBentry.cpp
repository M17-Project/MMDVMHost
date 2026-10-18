/*
 *   Copyright (C) 2020 by SASANO Takayoshi JG1UAA
 *   Copyright (C) 2023 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include "UserDBentry.h"

#if defined(USE_DMR) || defined(USE_P25) || defined(USE_NXDN)

#include <algorithm>

CUserDBentry::CUserDBentry() :
m_db()
{
}

CUserDBentry::~CUserDBentry()
{
}

const std::vector<std::string> CUserDBentry::keyList {
	keyRADIO_ID, keyCALLSIGN, keyFIRST_NAME, keyLAST_NAME,
	keyCITY, keySTATE, keyCOUNTRY,
};

bool CUserDBentry::isValidKey(const std::string key)
{
	auto it = std::find(keyList.begin(), keyList.end(), key);
	return it != keyList.end();
}

// The field separator: ASCII's unit separator, never in a lookup file.
static const char SEPARATOR = '\x1f';

int CUserDBentry::slot(const std::string& key)
{
	auto it = std::find(keyList.begin(), keyList.end(), key);
	return it == keyList.end() ? -1 : int(it - keyList.begin());
}

void CUserDBentry::set(const std::string key, const std::string value)
{
	int n = slot(key);
	if (value.empty() || n < 0 || value.find(SEPARATOR) != std::string::npos)
		return;

	// Split into the fields, put this one in, join again.
	std::vector<std::string> fields;
	std::string::size_type start = 0U;
	for (std::string::size_type end; (end = m_db.find(SEPARATOR, start)) != std::string::npos; start = end + 1U)
		fields.push_back(m_db.substr(start, end - start));
	if (fields.size() <= (unsigned int)n)
		fields.resize(n + 1);
	fields[n] = value;

	while (!fields.empty() && fields.back().empty())
		fields.pop_back();

	std::string db;
	for (const auto& f : fields) {
		db += f;
		db += SEPARATOR;
	}
	db.shrink_to_fit();
	m_db.swap(db);
}

const std::string CUserDBentry::get(const std::string key) const
{
	int n = slot(key);
	if (n < 0)
		return "";

	std::string::size_type start = 0U;
	for (int i = 0; i < n; i++) {
		start = m_db.find(SEPARATOR, start);
		if (start == std::string::npos)
			return "";
		start++;
	}

	std::string::size_type end = m_db.find(SEPARATOR, start);
	if (end == std::string::npos)
		return "";

	return m_db.substr(start, end - start);
}

void CUserDBentry::clear(void)
{
	m_db.clear();
}

#endif

