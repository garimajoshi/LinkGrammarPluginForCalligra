#ifndef LINKGRAMMARWRAPPER_H
#define LINKGRAMMARWRAPPER_H

class QString;
class QMap;

#define DEFAULT_LANGUAGE "en"

extern "C"
{
#include <link-grammar/link-includes.h>
}

class LinkGrammarWrapper
{
public:
    LinkGrammarWrapper();
    LinkGrammarWrapper(Dictionary dict, Parse_Options opts);
    ~LinkGrammarWrapper();
    bool parseSentence(const QString text) const;
    void cleanUp();
    bool isLanguageAvailable(QString language);
	int getMaxTimeToParseInNumberOfSeconds();
	void setMaxTimeToParseInNumberOfSeconds(int numberOfSeconds);
	int getMaxMemoryInMegaBytes;
	void setMaxMemoryInMegaBytes(int memoryInMegaBytes);
	int getDisjunctCount;
	void setDisjunctCount(int count);
	QString getLanguage();
	void setLanguage(QString language);
	void addLanguageToSetOfSupportedLanguages(QString language, QString dictionaryPath = 0);

private:
    void cleanUpDictionary();
    void cleanUpParseOptions();
    Dictionary m_dict;
    Parse_Options m_opts;
    int m_maxTimeToParseInNumberOfSeconds;
    int m_maxMemoryInMegaBytes;
	int m_disjunctCount;
	QString m_languagePreference;
    QString m_currentDictionaryLanguage;
	QMap<QString, QString> m_listOfAvailableLanguages;
};

#endif // LINKGRAMMARWRAPPER_H
