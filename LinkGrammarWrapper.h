#ifndef LINKGRAMMARWRAPPER_H
#define LINKGRAMMARWRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif

#include <link-grammar/link-includes.h>

#DEFINE DEFAULT_LANGUAGE "en"

class QString;
class QMap;

class LinkGrammarWrapper
{
public:
	LinkGrammarWrapper();
	~LinkGrammarWrapper();
	void cleanUp();
	bool parseSentence(QString givenText);
	bool isLanguageAvailable(QString language);
	int getMaxTimeToParseInNumberOfSeconds();
	void setMaxTimeToParseInNumberOfSeconds(int numberOfSeconds);
	int getMaxMemoryInMegaBytes;
	void setMaxMemoryInMegaBytes(int memoryInMegaBytes);
	int getDisjunctCount;
	void setDisjunctCount(int count);
	QString getLanguage();
	void setLanguage(QString language);
	void addLanguageToSetOfSupportedLanguagesWitDictionaryPath(QString language, QString dictionaryPath = 0)
private:
	Dictionary      m_Dict;
	Parse_Options   m_Opts;
	int m_maxTimeToParseInNumberOfSeconds;
	int m_maxMemoryInMegaBytes;
	int m_disjunctCount;
	QString m_languagePreference;
	QMap<QString, QString> m_listOfAvailableLanguages;
}

#ifdef __cplusplus
}
#endif

#endif // LINKGRAMMARWRAPPER_H
