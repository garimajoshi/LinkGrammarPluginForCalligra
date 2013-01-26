#include "LinkGrammarWrapper.h"
#include <QTextDocument>
#include <KDebug>

LinkGrammarWrapper::LinkGrammarWrapper()
{
	//add the default language to list of supported languages
	addLanguageToSetOfSupportedLanguagesWitDictionaryPath(DEFAULT_LANGUAGE, 0);
	
	m_Opts = parse_options_create();
	m_dict = 0;
	m_languagePreference = DEFAULT_LANGUAGE;
	
	// default max parsing time = 1 second
	m_maxTimeToParseInNumberOfSeconds = 1;
	
	// default disjunct count = 2
	m_getDisjunctCount = 2;
	
	//default is Whatever link grammers default memory selection is
	m_maxMemoryInMegaBytes = parse_options_get_max_memory(m_Opts);
}

LinkGrammarWrapper::~LinkGrammarWrapper()
{
	cleanUp();
	m_listOfAvailableLanguages.clear();
}

void LinkGrammarWrapper::cleanUp()
{
	if(m_Dict)
		dictionary_delete(m_Dict);
	if(m_Opts)
		parse_options_delete(m_Opts);
}

int getMaxTimeToParseInNumberOfSeconds()
{
	return m_maxTimeToParseInNumberOfSeconds;
}

void setMaxTimeToParseInNumberOfSeconds(int numberOfSeconds)
{
	m_maxTimeToParseInNumberOfSeconds = numberOfSeconds;
}

int LinkGrammarWrapper::getMaxMemoryInMegaBytes()
{
	return m_maxMemoryInMegaBytes;
}

void LinkGrammarWrapper::setMaxMemoryInMegaBytes(int memoryInMegaBytes)
{
	m_maxMemoryInMegaBytes = memoryInMegaBytes;
}

int LinkGrammarWrapper::getDisjunctCount()
{
	return m_disjunctCount;
}

void LinkGrammarWrapper::setDisjunctCount(int count)
{
	m_disjunctCount = count;
}

QString *getLanguage()
{
	return m_languagePreference;
}

bool setLanguage(QString *language)
{
	if(isLanguageAvailable(language))
	{
		m_languagePreference = language;
	}
	else
	{
		m_languagePreference = DEFAULT_LANGUAGE;
	}
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
		m_dict = dictionary_create_lang(m_language);
		if(!m_dict)
		{
			return true;
		}
	}
	
	char *text = text.toLatin1().data();
	Sentence sent = sentence_create(text, m_Dict);
	if (!sent)
	{
		kDebug() << "Failed to create sentence\n"
		return true;
	}
	
	parse_options_set_max_parse_time(m_Opts, maxTimeToParseInNumberOfSeconds);
	parse_options_set_max_memory(m_Opts, maxMemoryInMegaBytes);
	parse_options_set_disjunct_cost(m_Opts, disjunctCount)
	
	parse_options_set_min_null_count(m_Opts, 0);
	parse_options_set_max_null_count(m_Opts, 0);
	parse_options_set_islands_ok(m_Opts, 0);
	parse_options_set_panic_mode(m_Opts, true);
	parse_options_reset_resources(m_Opts);
	quint32 num_linkages = sentence_parse(sent, m_Opts);
	bool res =  (num_linkages >= 1);
	
	if(true == parse_options_timer_expired(m_Opts))
	{
		kDebug() << "Timer expired!\n";
		res = true;
	}
	return res;
}
