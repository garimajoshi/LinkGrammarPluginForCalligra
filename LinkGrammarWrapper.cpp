#include "LinkGrammarWrapper.h"

#include <QTextDocument>
#include <QString>
#include <QMap>
#include <KDebug>

LinkGrammarWrapper::LinkGrammarWrapper()
{
    //add the default language to list of supported languages
	addLanguageToSetOfSupportedLanguagesWithDictionaryPath("en");
	m_Opts = parse_options_create();
	m_Dict = dictionary_create_lang("en");
	m_languagePreference = "en";
	// default max parsing time = 1
	m_maxTimeToParseInNumberOfSeconds = 1;	
	// default disjunct count = 2
	m_getDisjunctCount = 2;	
}

LinkGrammarWrapper::LinkGrammarWrapper(Dictionary dict, Parse_Options opts)
{
    m_Opts = opts;
    m_Dict = dict;
    // default max parsing time = 1
	m_maxTimeToParseInNumberOfSeconds = 1;	
	// default disjunct count = 2
	m_getDisjunctCount = 2;	
}

LinkGrammarWrapper::~LinkGrammarWrapper()
{
	cleanUp();
	m_listOfAvailableLanguages.clear();
}

void LinkGrammarWrapper::cleanUpDictionary()
{
    if(m_Dict)
		dictionary_delete(m_Dict);
    m_Dict = 0;
}

void LinkGrammarWrapper::cleanUpParseOptions()
{
    if(m_Opts)
		parse_options_delete(m_Opts);
    m_Opts = 0;
}

void LinkGrammarWrapper::cleanUp()
{
    cleanUpParseOptions();
    cleanUpDictionary();
}

int getMaxTimeToParseInNumberOfSeconds()
{
	return m_maxTimeToParseInNumberOfSeconds;
}

void setMaxTimeToParseInNumberOfSeconds(int numberOfSeconds)
{
	m_maxTimeToParseInNumberOfSeconds = numberOfSeconds;
}

int LinkGrammarWrapper::getDisjunctCount()
{
	return m_disjunctCount;
}

void LinkGrammarWrapper::setDisjunctCount(int count)
{
	m_disjunctCount = count;
}

QString getLanguage()
{
	return m_languagePreference;
}

bool setLanguage(QString language)
{
	m_languagePreference = language;
}

void addLanguageToSetOfSupportedLanguagesWitDictionaryPath(QString language, QString dictionaryPath)
{
	m_listOfAvailableLanguages[languages] = dictionaryPath;
}

bool isLanguageAvailable(QString language)
{
	return m_listOfAvailableLanguages.contains(language);
}

bool LinkGrammarWrapper::parseSentence(QString givenSentence)
{
	if(!m_Dict)
	{
		kDebug() << "No dictionary";
        return true; //no grammar checking
	}
	char *textChar = givenSentence.toUtf8().data();
	Sentence sent = sentence_create(textChar, m_Dict);
	if (!sent)
	{
		kDebug() << "Failed to create sentence";
		return true;
	}
	
	parse_options_set_max_parse_time(m_Opts, maxTimeToParseInNumberOfSeconds);
	parse_options_set_disjunct_cost(m_Opts, disjunctCount)
	
	parse_options_set_min_null_count(m_Opts, 0);
	parse_options_set_max_null_count(m_Opts, 0);
	parse_options_set_islands_ok(m_Opts, 0);
	parse_options_set_panic_mode(m_Opts, true);
	parse_options_reset_resources(m_Opts);
	
    quint32 num_linkages = sentence_parse(sent, m_Opts);
	bool res =  (num_linkages >= 1);
	
	if(parse_options_timer_expired(m_Opts))
	{
		kDebug() << "Timer expired!";
		res = true;
	}

    /*****
     * TODO: find out what actually went wrong by allowing null linkages.
    *******/
    sentence_delete(sent);
	return res;
}
