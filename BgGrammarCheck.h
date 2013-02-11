#ifndef BGGRAMMARCHECK_H
#define BGGRAMMARCHECK_H

#include "LinkGrammerWrapper.h"
#include <QTextCursor>
#include <kdecore_export.h>
#include <QtCore/QObject>

class QTextDocument;

class KDECORE_EXPORT BgGrammarCheck : public QObject
{
    Q_OBJECT
public:
    explicit BgGrammarCheck(const LinkGrammarWrapper &grammarChecker, QObject *parent = 0);
    explicit BgGrammarCheck(QObject *parent = 0);
    //input is just single sentence
    void startRun(QTextDocument *document, int startPosition, int endPosition);
    LinkGrammarWrapper grammarChecker();
    void setGrammarChecker(const LinkGrammarWrapper &grammarChecker);
    void checkCurrentSentence();
    void restore(KConfig *config);
    QString currentLanguage();

public slots:
    void setDefaultLanguage(const QString &language);
    void changeLanguage(const QString &lang);
    QString language();

signals:
    void grammaticallyIncorrectSegment(const QString &segment, int startPosition, int endPosition, bool incorrectGrammar);
    void done();
private:
    QTextDocument *m_document;
    LinkGrammarWrapper m_grammarChecker;
    QString m_currentLanguage;
    QString m_currentCountry;
    QString m_defaultLanguage;
    QString m_defaultCountry;
    int m_startPosition;
    int m_endPosition;
    QString m_currentSentence;
};
#endif
