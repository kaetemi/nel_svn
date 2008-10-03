/** \file i18n.cpp
 * Internationalisation
 *
 * \todo ace: manage unicode format
 */

/* Copyright, 2000 Nevrax Ltd.
 *
 * This file is part of NEVRAX NEL.
 * NEVRAX NEL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * NEVRAX NEL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with NEVRAX NEL; see the file COPYING. If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */


#include "stdmisc.h"

#include "nel/misc/path.h"
#include "nel/misc/i18n.h"

using namespace std;

namespace NLMISC {

/*const std::string		CI18N::_LanguageFiles[] =
{
	std::string("english"),
	std::string("french")
};
*/
const std::string		CI18N::_LanguageCodes[] =
{
	std::string("en"),		// english
	std::string("de"),		// german
	std::string("fr"),		// french
	std::string("wk"),		// work translation
//	std::string("zh-TW"),	// traditional Chinese
//	std::string("zh-CN")	// simplified Chinese
};

const uint				CI18N::_NbLanguages = sizeof(CI18N::_LanguageCodes) / sizeof(std::string);
CI18N::StrMapContainer	CI18N::_StrMap;
bool					CI18N::_StrMapLoaded = false;
const ucstring			CI18N::_NotTranslatedValue("<Not Translated>");
bool					CI18N::_LanguagesNamesLoaded = false;
sint32					CI18N::_SelectedLanguage = -1;
CI18N::ILoadProxy		*CI18N::_LoadProxy = 0;


void CI18N::setLoadProxy(ILoadProxy *loadProxy)
{
	_LoadProxy = loadProxy;
}


void CI18N::load (const std::string &languageCode)
{
//	nlassert (lid < _NbLanguages);
//	nlassert (_LanguagesNamesLoaded);

	uint i;
	for (i=0; i<_NbLanguages; ++i)
	{
		if (_LanguageCodes[i] == languageCode)
			break;
	}

	if (i == _NbLanguages)
	{
		nlwarning("I18N: Unknown language code : %s, defaulting to %s", _LanguageCodes[0].c_str());
		i = 0;
	}

	std::string fileName  = _LanguageCodes[i] + ".uxt";

	_SelectedLanguage = i;

	if (_StrMapLoaded)	_StrMap.clear ();
	else				_StrMapLoaded = true;

	loadFileIntoMap(fileName, _StrMap);
}

bool CI18N::loadFileIntoMap(const std::string &fileName, StrMapContainer &destMap)
{
	ucstring text;
	// read in the text
	if (_LoadProxy)
		_LoadProxy->loadStringFile(fileName, text);
	else
		readTextFile(fileName, text);
	// remove any comment
	remove_C_Comment(text);

	ucstring::const_iterator first(text.begin()), last(text.end());
	std::string lastReadLabel("nothing");

	while (first != last)
	{
		skipWhiteSpace(first, last);
		std::string label;
		ucstring ucs;
		if (!parseLabel(first, last, label))
		{
			nlwarning("I18N: Error reading label field in %s. Stop reading after %s.", fileName.c_str(), lastReadLabel.c_str());
			return false;
		}
		lastReadLabel = label;
		skipWhiteSpace(first, last);
		if (!parseMarkedString('[', ']', first, last, ucs))
		{
			nlwarning("I18N: Error reading text for label %s in %s. Stop reading.", label.c_str(), fileName.c_str());
			return false;
		}

		// ok, a line read.
		std::pair<std::map<std::string, ucstring>::iterator, bool> ret;
		ret = destMap.insert(std::make_pair(label, ucs));
		if (!ret.second)
		{
			nlwarning("I18N: Error in %s, the label %s exist twice !", fileName.c_str(), label.c_str());
		}
		skipWhiteSpace(first, last);
	}

	// a little check to ensure that the lang name has been set.
	StrMapContainer::iterator it(destMap.find("LanguageName"));
	if (it == destMap.end())
	{
		nlwarning("I18N: In file %s, missing LanguageName translation (should be first in file)", fileName.c_str());
	}
	return true;
}


void CI18N::loadFromFilename(const std::string &filename, bool reload)
{
	StrMapContainer destMap;
	if (!loadFileIntoMap(filename, destMap))
	{
		return;
	}
	// merge with existing map
	for(StrMapContainer::iterator it = destMap.begin(); it != destMap.end(); ++it)
	{
		if (!reload)
		{
			if (_StrMap.count(it->first))
			{
				nlwarning("I18N: Error in %s, the label %s exist twice !", filename.c_str(), it->first.c_str());
			}
		}
		_StrMap[it->first] = it->second;
	}
}


const ucstring &CI18N::get (const std::string &label)
{
	if (label.empty())
	{
		static ucstring	emptyString;
		return emptyString;
	}

	StrMapContainer::iterator it(_StrMap.find(label));

	if (it != _StrMap.end())
		return it->second;

	static CHashSet<string>	missingStrings;
	if (missingStrings.find(label) == missingStrings.end())
	{
		sint32 nblang = sizeof(_LanguageCodes)/sizeof(_LanguageCodes[0]);
		if(_SelectedLanguage < 0 || _SelectedLanguage >= nblang)
		{
			nlwarning("I18N: _SelectedLanguage %d is not a valid language ID, out of array of size %d, can't display the message '%s'", _SelectedLanguage, nblang, label.c_str());
		}
		else
		{
			nlwarning("I18N: The string %s did not exist in language %s (display once)", label.c_str(), _LanguageCodes[_SelectedLanguage].c_str());
		}
		missingStrings.insert(label);
	}

	static ucstring	badString;

	badString = ucstring(std::string("<NotExist:")+label+">");

	return badString;
}

bool CI18N::hasTranslation(const std::string &label)
{
	if (label.empty()) return true;

	StrMapContainer::iterator it(_StrMap.find(label));
	return it != _StrMap.end();
}


ucstring CI18N::getCurrentLanguageName ()
{
	return get("LanguageName");
}


void CI18N::remove_C_Comment(ucstring &commentedString)
{
	{
		ucstring temp;
		temp.reserve(commentedString.size());
		ucstring::const_iterator first(commentedString.begin()), last(commentedString.end());
		for (;first != last; ++first)
		{
			temp.push_back(*first);
			if (*first == '[')
			{
				// no comment inside string literal
				while (++first != last)
				{
					temp.push_back(*first);
					if (*first == ']')
						break;
				}
			}
			else if (*first == '/')
			{
				// start of comment ?
				++first;
				if (first != last && *first == '/')
				{
					temp.resize(temp.size()-1);
					// one line comment, skip until end of line
					while (first != last && *first != '\n')
						++first;
				}
				else if (first != last && *first == '*')
				{
					temp.resize(temp.size()-1);
					// start of multiline comment, skip until we found '*/'
					while (first != last && !(*first == '*' && (first+1) != last && *(first+1) == '/'))
						++first;
					// skip the closing '/'
					if (first != last)
						++first;
				}
				else
				{
					temp.push_back(*first);
				}
			}
		}

		commentedString.swap(temp);
	}
}


void	CI18N::skipWhiteSpace(ucstring::const_iterator &it, ucstring::const_iterator &last, ucstring *storeComments, bool newLineAsWhiteSpace)
{
	while (it != last &&
			(
					(*it == 0xa && newLineAsWhiteSpace)
				||	(*it == 0xd && newLineAsWhiteSpace)
				||	*it == ' '
				||	*it == '\t'
				||	(storeComments && *it == '/' && it+1 != last && *(it+1) == '/')
				||	(storeComments && *it == '/' && it+1 != last && *(it+1) == '*')
			))
	{
		if (storeComments && *it == '/' && it+1 != last && *(it+1) == '/')
		{
			// found a one line C comment. Store it until end of line.
			while (it != last && *it != '\n')
				storeComments->push_back(*it++);
			// store the final '\n'
			if (it != last)
				storeComments->push_back(*it++);
		}
		else if (storeComments && *it == '/' && it+1 != last && *(it+1) == '*')
		{
			// found a multiline C++ comment. store until we found the closing '*/'
			while (it != last && !(*it == '*' && it+1 != last && *(it+1) == '/'))
				storeComments->push_back(*it++);
			// store the final '*'
			if (it != last)
				storeComments->push_back(*it++);
			// store the final '/'
			if (it != last)
				storeComments->push_back(*it++);
			// and a new line.
			storeComments->push_back('\r');
			storeComments->push_back('\n');
		}
		else
		{
			// just skip white space or don't store comments
			++it;
		}
	}
}

bool CI18N::parseLabel(ucstring::const_iterator &it, ucstring::const_iterator &last, std::string &label)
{
	ucstring::const_iterator rewind = it;
	label.erase();

	// first char must be A-Za-z@_
	if (it != last &&
			(
				(*it >= '0' && *it <= '9')
			||	(*it >= 'A' && *it <= 'Z')
			||	(*it >= 'a' && *it <= 'z')
			||	(*it == '_')
			||	(*it == '@')
			)
		)
		label.push_back(char(*it++));
	else
	{
		it = rewind;
		return false;
	}

	// other char must be [0-9A-Za-z@_]*
	while (it != last &&
			(
				(*it >= '0' && *it <= '9')
			||	(*it >= 'A' && *it <= 'Z')
			||	(*it >= 'a' && *it <= 'z')
			||	(*it == '_')
			||	(*it == '@')
			)
		)
		label.push_back(char(*it++));

	return true;
}

bool CI18N::parseMarkedString(ucchar openMark, ucchar closeMark, ucstring::const_iterator &it, ucstring::const_iterator &last, ucstring &result, uint32 *lineCounter, bool allowNewline)
{
//		ucstring ret;
	result.erase();
	// parse a string delimited by the specified opening and closing mark

	if (it != last && *it == openMark)
	{
		++it;

		while (it != last && *it != closeMark && (allowNewline || *it != '\n'))
		{
			// ignore tab, new lines and line feed
			if (*it == openMark)
			{
				nlwarning("I18N: Found a non escaped openmark %c in a delimited string (Delimiters : '%c' - '%c')", char(openMark), char(openMark), char(closeMark));
				return false;
			}
			if (*it == '\t'
				|| (*it == '\n' && allowNewline)
				|| *it == '\r')
				++it;
			else if (*it == '\\' && it+1 != last && *(it+1) != '\\')
			{
				++it;
				// this is an escape sequence !
				switch(*it)
				{
				case 't':
					result.push_back('\t');
					break;
				case 'n':
					result.push_back('\n');
					break;
				case 'd':
					// insert a delete
					result.push_back(8);
					break;
				default:
					// escape the close mark ?
					if(*it == closeMark)
						result.push_back(closeMark);
					// escape the open mark ?
					else if(*it == openMark)
						result.push_back(openMark);
					else
					{
						nlwarning("I18N: Ignoring unknown escape code \\%c (char value : %u)", char(*it), *it);
						return false;
					}
				}
				++it;
			}
			else if (*it == '\\' && it+1 != last && *(it+1) == '\\')
			{
				// escape the \ char
				++it;
				result.push_back(*it);
				++it;
			}
			else
			{
				if (*it == '\n' && lineCounter != NULL)
					// update line counter
					++(*lineCounter);

				result.push_back(*it++);
			}
		}

		if (it == last || *it != closeMark)
		{
			nlwarning("I18N: Missing end of delimited string (Delimiters : '%c' - '%c')", char(openMark), char(closeMark));
			return false;
		}
		else
			++it;
	}
	else
	{
		nlwarning("I18N: Malformed or non existent delimited string (Delimiters : '%c' - '%c')", char(openMark), char(closeMark));
		return false;
	}

	return true;
}


void CI18N::readTextFile(const std::string &filename,
						 ucstring &result,
						 bool forceUtf8,
						 bool fileLookup,
						 bool preprocess,
						 TLineFormat lineFmt,
						 bool warnIfIncludesNotFound)
{
	// create the read context
	TReadContext readContext;

	// call the inner function
	_readTextFile(filename, result, forceUtf8, fileLookup, preprocess, lineFmt, warnIfIncludesNotFound, readContext);

	if (!readContext.IfStack.empty())
	{
		nlwarning("Preprocess: Missing %u closing #endif after parsing %s", readContext.IfStack.size(), filename.c_str() );
	}
}


bool CI18N::matchToken(const char* token, ucstring::const_iterator &it, ucstring::const_iterator end)
{
	ucstring::const_iterator rewind = it;
	skipWhiteSpace(it, end, NULL, false);
	while (it != end && *token != 0 && *it == *token)
	{
		++it;
		++token;
	}

	if (*token == 0)
	{
		// we fund the token
		return true;
	}

	// not found
	it = rewind;
	return false;
}

void CI18N::skipLine(ucstring::const_iterator &it, ucstring::const_iterator end, uint32 &lineCounter)
{
	while (it != end && *it != '\n')
		++it;

	if (it != end)
	{
		++lineCounter;
		++it;
	}
}


void CI18N::_readTextFile(const std::string &filename,
						 ucstring &result,
						 bool forceUtf8,
						 bool fileLookup,
						 bool preprocess,
						 TLineFormat lineFmt,
						 bool warnIfIncludesNotFound,
						 TReadContext &readContext)
{
	std::string fullName;
	if (fileLookup)
		fullName = CPath::lookup(filename, false,warnIfIncludesNotFound);
	else
		fullName = filename;

	if (fullName.empty())
		return;

	// If ::lookup is used, the file can be in a bnp and CFile::fileExists fails.
	// \todo Boris
	bool isInBnp = fullName.find('@') != string::npos;
	if (!isInBnp && !CFile::fileExists(fullName))
	{
		nlwarning("CI18N::readTextFile : file '%s' does not exist, returning empty string", fullName.c_str());
		return;
	}

	NLMISC::CIFile	file(fullName);


	// Fast read all the text in binary mode.
	std::string text;
	text.resize(file.getFileSize());
	if (file.getFileSize() > 0)
		file.serialBuffer((uint8*)(&text[0]), text.size());

	// Transform the string in ucstring according to format header
	if (!text.empty())
		readTextBuffer((uint8*)&text[0], text.size(), result, forceUtf8);

	if (preprocess)
	{
		// a string to old the result of the preprocess
		ucstring final;
		// make rooms to reduce allocation cost
		final.reserve(raiseToNextPowerOf2(result.size()));

		// parse the file, looking for preprocessor command.
		ucstring::const_iterator it(result.begin()), end(result.end());

		// input line counter
		uint32 currentLine = 1;

		// set the current file and line info
		final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);

		while (it != end)
		{
			// remember the begin of the line
			ucstring::const_iterator beginOfLine = it;

			// advance in the line, looking for a preprocessor command
			skipWhiteSpace(it, end, NULL, false);

			if (it != end && *it == '#')
			{
				// skip the '#' symbol
				++it;
				// we found a preprocessor command !
				skipWhiteSpace(it, end, NULL, false);

				if (matchToken("include", it, end))
				{
					if (readContext.IfStack.empty() || readContext.IfStack.back())
					{
						// we have an include command
						skipWhiteSpace(it, end, NULL, false);

						// read the file name between quote
						ucstring str;
						breakable
						{
							if (!parseMarkedString(ucchar('\"'), ucchar('\"'), it, end, str, &currentLine, false))
							{
								nlwarning("Preprocess: In file %s(%u) : Error parsing include file command", filename.c_str(), currentLine);

								break;
							}
							else
							{
								// ok, read the subfile
								string subFilename = str.toString();

								// check is file exist
								if (!CFile::fileExists(subFilename))
								{
									// look for the file relative to current file
									subFilename = CFile::getPath(filename)+subFilename;
									if (!CFile::fileExists(subFilename))
									{
										// the include file is not found, issue a warning
										nlwarning("Preprocess: In file %s(%u) : Cannot include file '%s'",
											filename.c_str(), currentLine,
											str.toString().c_str());

										break;
									}
								}

								nlinfo("Preprocess: In file %s(%u) : Including '%s'",
									filename.c_str(), currentLine,
									subFilename.c_str());

								ucstring inserted;
								_readTextFile(subFilename, inserted, forceUtf8, fileLookup, preprocess, lineFmt, warnIfIncludesNotFound, readContext);
								final += inserted;
							}
						}
						// advance to next line
						skipLine(it, end, currentLine);
						// reset filename and line counter
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
				}
				else if (matchToken("optional", it, end))
				{
					if (readContext.IfStack.empty() || readContext.IfStack.back())
					{
						// we have an optional include command
						skipWhiteSpace(it, end, NULL, false);

						// read the file name between quote
						ucstring str;
						breakable
						{
							if (!parseMarkedString('\"', '\"', it, end, str, &currentLine, false))
							{
								nlwarning("Preprocess: In file %s(%u) : Error parsing optional file command", filename.c_str(), currentLine);

								break;
							}
							else
							{
								// ok, read the subfile
								string subFilename = str.toString();

								// check is file exist
								if (!CFile::fileExists(subFilename))
								{
									// look for the file relative to current file
									subFilename = CFile::getPath(filename)+subFilename;
									if (!CFile::fileExists(subFilename))
									{
										// not found but optionnal, only emit a debug log
										// the include file is not found, issue a warning
										nldebug("Preprocess: In file %s(%u) : Cannot include optional file '%s'",
											filename.c_str(), currentLine,
											str.toString().c_str());

										break;
									}
								}

								nlinfo("Preprocess: In file %s(%u) : Including optional '%s'",
									filename.c_str(), currentLine,
									subFilename.c_str());

								ucstring inserted;
								_readTextFile(subFilename, inserted, forceUtf8, fileLookup, preprocess, lineFmt, warnIfIncludesNotFound, readContext);
								final += inserted;
							}
						}
						// advance to next line
						skipLine(it, end, currentLine);
						// reset filename and line counter
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
				}
				else if (matchToken("define", it, end))
				{
					if (readContext.IfStack.empty() || readContext.IfStack.back())
					{
						skipWhiteSpace(it, end, NULL, false);

						string label;
						if (parseLabel(it, end, label))
						{
							if (readContext.Defines.find(label) != readContext.Defines.end())
							{
								nlinfo("Preprocess: In file %s(%u) : symbol '%s' already defined",
									filename.c_str(), currentLine,
									label.c_str());
							}
							else
							{
								readContext.Defines.insert(label);
							}
						}
						else
						{
							nlwarning("Preprocess: In file %s(%u) : Error parsing #define command", filename.c_str(), currentLine);
						}

						// advance to next line
						skipLine(it, end, currentLine);
						// update filename and line number
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
				}
				else if (matchToken("ifdef", it, end))
				{
					if (readContext.IfStack.empty() || readContext.IfStack.back())
					{
						skipWhiteSpace(it, end, NULL, false);
						string label;
						if (parseLabel(it, end, label))
						{
							if (readContext.Defines.find(label) != 	readContext.Defines.end())
							{
								// symbol defined, push a true
								readContext.IfStack.push_back(true);
							}
							else
							{
								// symbol not defines, push a false
								readContext.IfStack.push_back(false);
							}
						}
						else
						{
							nlwarning("Preprocess: In file %s(%u) : Error parsing #ifdef command", filename.c_str(), currentLine);
						}

						// advance to next line
						skipLine(it, end, currentLine);
						// update filename and line number
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
					else
					{
						// just push à false
						readContext.IfStack.push_back(false);

						skipLine(it, end, currentLine);
					}
				}
				else if (matchToken("ifndef", it, end))
				{
					if (readContext.IfStack.empty() || readContext.IfStack.back())
					{
						skipWhiteSpace(it, end, NULL, false);
						string label;
						if (parseLabel(it, end, label))
						{
							if (readContext.Defines.find(label) == 	readContext.Defines.end())
							{
								// symbol defined, push a true
								readContext.IfStack.push_back(true);
							}
							else
							{
								// symbol not defines, push a false
								readContext.IfStack.push_back(false);
							}
						}
						else
						{
							nlwarning("Preprocess: In file %s(%u) : Error parsing #ifndef command", filename.c_str(), currentLine);
						}

						// advance to next line
						skipLine(it, end, currentLine);
						// update filename and line number
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
					else
					{
						// just push à false
						readContext.IfStack.push_back(false);

						skipLine(it, end, currentLine);
					}
				}
				else if (matchToken("endif", it, end))
				{
					bool previous = false;
					if (readContext.IfStack.empty())
					{
						nlwarning("Preprocess: In file %s(%u) : Error found '#endif' without matching #if", filename.c_str(), currentLine);
					}
					else
					{
						previous = readContext.IfStack.back();

						readContext.IfStack.pop_back();
					}
					skipLine(it, end, currentLine);

					if (!previous && (readContext.IfStack.empty() || readContext.IfStack.back()))
					{
						// end of ignored file part, restore the file and line number
						final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
					}
					// update filename and line number
//					final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
				}
				else
				{
					// unrecognized command, ignore line
					nlwarning("Preprocess: In file %s(%u) : Error unrecognized preprocessor command",
						filename.c_str(), currentLine);

					skipLine(it, end, currentLine);
					// update filename and line number
					final += toString("#fileline \"%s\" %u\n", filename.c_str(), currentLine);
				}
			}
			else
			{
				// normal line
				skipLine(it, end, currentLine);

				if (readContext.IfStack.empty() || readContext.IfStack.back())
				{
					// copy the line to the final string
					final.append(beginOfLine, it);
				}
			}
		}

		// set the result with the preprocessed content
		result.swap(final);
	}

	// apply line delimiter conversion if needed
	if (lineFmt != LINE_FMT_NO_CARE)
	{
		if (lineFmt == LINE_FMT_LF)
		{
			// we only want \n
			// easy, just remove or replace any \r code
			string::size_type pos;
			string::size_type lastPos = 0;
			ucstring temp;
			// reserve some place to reduce re-allocation
			temp.reserve(result.size() +result.size()/10);

			// look for the first \r
			pos = result.find('\r');
			while (pos != string::npos)
			{
				if (pos < result.size()-1 && result[pos+1] == '\n')
				{
					temp.append(result.begin()+lastPos, result.begin()+pos);
					pos += 1;
				}
				else
				{
					temp.append(result.begin()+lastPos, result.begin()+pos);
					temp[temp.size()-1] = '\n';
				}

				lastPos = pos;
				// look for next \r
				pos = result.find('\r', pos);
			}

			// copy the rest
			temp.append(result.begin()+lastPos, result.end());

			result.swap(temp);
		}
		else if (lineFmt == LINE_FMT_CRLF)
		{
			// need to replace simple '\n' or '\r' with a '\r\n' double
			string::size_type pos = 0;
			string::size_type lastPos = 0;

			ucstring temp;
			// reserve some place to reduce re-allocation
			temp.reserve(result.size() +result.size()/10);


			// first loop with the '\r'
			pos = result.find('\r', pos);
			while (pos != string::npos)
			{
				if (pos >= result.size()-1 || result[pos+1] != '\n')
				{
					temp.append(result.begin()+lastPos, result.begin()+pos+1);
					temp += '\n';
					lastPos = pos+1;
				}
				// skip this char
				pos++;

				// look the next '\r'
				pos = result.find('\r', pos);
			}

			// copy the rest
			temp.append(result.begin()+lastPos, result.end());
			result.swap(temp);

			temp = "";

			// second loop with the '\n'
			pos = 0;
			lastPos = 0;
			pos = result.find('\n', pos);
			while (pos != string::npos)
			{
				if (pos == 0 || result[pos-1] != '\r')
				{
					temp.append(result.begin()+lastPos, result.begin()+pos);
					temp += '\r';
					temp += '\n';
					lastPos = pos+1;
				}
				// skip this char
				pos++;

				pos = result.find('\n', pos);
			}

			// copy the rest
			temp.append(result.begin()+lastPos, result.end());
			result.swap(temp);
		}
	}

}

void CI18N::readTextBuffer(uint8 *buffer, uint size, ucstring &result, bool forceUtf8)
{
	static uint8 utf16Header[] = {char(0xff), char(0xfe)};
	static uint8 utf16RevHeader[] = {char(0xfe), char(0xff)};
	static uint8 utf8Header[] = {char(0xef), char(0xbb), char(0xbf)};

	if (forceUtf8)
	{
		if (size>=3 &&
			buffer[0]==utf8Header[0] &&
			buffer[1]==utf8Header[1] &&
			buffer[2]==utf8Header[2]
			)
		{
			// remove utf8 header
			buffer+= 3;
			size-=3;
		}
		std::string text((char*)buffer, size);
		result.fromUtf8(text);
	}
	else if (size>=3 &&
			 buffer[0]==utf8Header[0] &&
			 buffer[1]==utf8Header[1] &&
			 buffer[2]==utf8Header[2]
			)
	{
		// remove utf8 header
		buffer+= 3;
		size-=3;
		std::string text((char*)buffer, size);
		result.fromUtf8(text);
	}
	else if (size>=2 &&
			 buffer[0]==utf16Header[0] &&
			 buffer[1]==utf16Header[1]
			)
	{
		// remove utf16 header
		buffer+= 2;
		size-= 2;
		// check pair number of bytes
		nlassert((size & 1) == 0);
		// and do manual conversion
		uint16 *src = (uint16*)(buffer);
		result.resize(size/2);
		for (uint j=0; j<result.size(); j++)
			result[j]= *src++;
	}
	else if (size>=2 &&
			 buffer[0]==utf16RevHeader[0] &&
			 buffer[1]==utf16RevHeader[1]
			)
	{
		// remove utf16 header
		buffer+= 2;
		size-= 2;
		// check pair number of bytes
		nlassert((size & 1) == 0);
		// and do manual conversion
		uint16 *src = (uint16*)(buffer);
		result.resize(size/2);
		uint j;
		for (j=0; j<result.size(); j++)
			result[j]= *src++;
		//  Reverse byte order
		for (j=0; j<result.size(); j++)
		{
			uint8 *pc = (uint8*) &result[j];
			std::swap(pc[0], pc[1]);
		}
	}
	else
	{
		// hum.. ascii read ?
		// so, just do a direct conversion
		std::string text((char*)buffer, size);
		result = text;
	}
}


void CI18N::writeTextFile(const std::string filename, const ucstring &content, bool utf8)
{
	COFile file(filename);

	if (!utf8)
	{
		// write the unicode 16 bits tag
		uint16 unicodeTag = 0xfeff;
		file.serial(unicodeTag);

		uint i;
		for (i=0; i<content.size(); ++i)
		{
			uint16 c = content[i];
			file.serial(c);
		}
	}
	else
	{
		static char utf8Header[] = {char(0xef), char(0xbb), char(0xbf), 0};

		std::string str = encodeUTF8(content);
		// add the UTF-8 'not official' header
		str = utf8Header + str;

		uint i;
		for (i=0; i<str.size(); ++i)
		{
			file.serial(str[i]);
		}
	}
}

ucstring CI18N::makeMarkedString(ucchar openMark, ucchar closeMark, const ucstring &text)
{
	ucstring ret;

	ret.push_back(openMark);

	ucstring::const_iterator first(text.begin()), last(text.end());
	for (; first != last; ++first)
	{
		if (*first == '\n')
		{
			ret += '\\';
			ret += 'n';
		}
		else if (*first == '\t')
		{
			ret += '\\';
			ret += 't';
		}
		else if (*first == closeMark)
		{
			// excape the embeded closing mark
			ret += '\\';
			ret += closeMark;
		}
		else
		{
			ret += *first;
		}
	}

	ret += closeMark;

	return ret;
}


string CI18N::encodeUTF8(const ucstring &str)
{
	return str.toUtf8();
	/*
	string	res;
	ucstring::const_iterator first(str.begin()), last(str.end());
	for (; first != last; ++first)
	{
	  //ucchar	c = *first;
		uint nbLoop = 0;
		if (*first < 0x80)
			res += char(*first);
		else if (*first < 0x800)
		{
			ucchar c = *first;
			c = c >> 6;
			c = c & 0x1F;
			res += c | 0xC0;
			nbLoop = 1;
		}
		else if (*first < 0x10000)
		{
			ucchar c = *first;
			c = c >> 12;
			c = c & 0x0F;
			res += c | 0xE0;
			nbLoop = 2;
		}

		for (uint i=0; i<nbLoop; ++i)
		{
			ucchar	c = *first;
			c = c >> ((nbLoop - i - 1) * 6);
			c = c & 0x3F;
			res += char(c) | 0x80;
		}
	}
	return res;
	*/
}

/* UTF-8 conversion table
U-00000000 - U-0000007F:  0xxxxxxx
U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
// not used as we convert from 16 bits unicode
U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
*/


uint64	CI18N::makeHash(const ucstring &str)
{
	// on passe au moins 8 fois sur chaque octet de resultat
	if (str.empty())
		return 0;
	const	uint32	MIN_TURN = 8*8;
	uint64	hash = 0;
	uint8	*ph = (uint8*)&hash;
	uint8	*pc = (uint8*)str.data();

	uint nbLoop = max(uint32(str.size()*2), MIN_TURN);
	uint roll = 0;

	for (uint i=0; i<nbLoop; ++i)
	{
		ph[(i/2) & 0x7] = uint8((ph[(i/2) & 0x7] + (pc[i%(str.size()*2)] << roll)) & 0xff);
		ph[(i/2) & 0x7] = uint8((ph[(i/2) & 0x7] + (pc[i%(str.size()*2)] >> (8-roll))) & 0xff);

		roll++;
		roll &= 0x7;
	}

	return hash;
}

// convert a hash value to a readable string
string CI18N::hashToString(uint64 hash)
{
	uint32 *ph = (uint32*)&hash;

	char temp[] = "0011223344556677";
	sprintf(temp, "%08X%08X", ph[0], ph[1]);

	return string(temp);
}

// fast convert a hash value to a ucstring
void	CI18N::hashToUCString(uint64 hash, ucstring &dst)
{
	static ucchar	cvtTable[]= {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	dst.resize(16);
	for(sint i=15;i>=0;i--)
	{
		// Must decal dest of 8, cause of hashToString code (Little Endian)
		dst[(i+8)&15]= cvtTable[hash&15];
		hash>>=4;
	}
}

// convert a readable string into a hash value.
uint64 CI18N::stringToHash(const std::string &str)
{
	nlassert(str.size() == 16);
	uint32	low, hight;

	string sl, sh;
	sh = str.substr(0, 8);
	sl = str.substr(8, 8);

	sscanf(sh.c_str(), "%08X", &hight);
	sscanf(sl.c_str(), "%08X", &low);

	uint64 hash;
	uint32 *ph = (uint32*)&hash;

	ph[0] = hight;
	ph[1] = low;

	return hash;
}

} // namespace NLMISC
