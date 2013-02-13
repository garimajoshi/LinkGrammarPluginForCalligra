#ifndef LINKGRAMMARWRAPPER_H
#define LINKGRAMMARWRAPPER_H

class QString;
class QMap;

#ifdef __cplusplus
extern "C"
{
#include <link-grammar/link-includes.h>
#endif
    
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
		int getDisjunctCount;
		void setDisjunctCount(int count);
		QString getLanguage();
		void setLanguage(QString language);
		void addLanguageToSetOfSupportedLanguages(QString language, QString dictionaryPath = QString());
		
	private:
		void cleanUpDictionary();
		void cleanUpParseOptions();
		Dictionary m_Dict;
		Parse_Options m_Opts;
		int m_maxTimeToParseInNumberOfSeconds;
		int m_disjunctCount;
		QString m_languagePreference;
		QString m_currentDictionaryLanguage;
		QMap<QString, QString> m_listOfAvailableLanguages;
	};
	
#ifdef __cplusplus
}
#endif

#endif // LINKGRAMMARWRAPPER_H
