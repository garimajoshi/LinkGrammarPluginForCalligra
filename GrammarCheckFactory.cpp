#include "GrammarCheckFactory.h"
#include "GrammarCheck.h"

#include <KLocale>

GrammarCheckFactory::GrammarCheckFactory()
    : KoTextEditingFactory("grammarcheck")
{
    setShowInMenu(true);
    setTitle(i18n("Check Grammar"));
}

KoTextEditingPlugin *GrammarCheckFactory::create() const
{
    return new GrammarCheck();
}
