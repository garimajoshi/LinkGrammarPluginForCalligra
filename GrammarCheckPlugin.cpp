#include "GrammarCheckPlugin.h"
#include "GrammarCheckFactory.h"

#include <KPluginFactory>
#include <KPluginLoader>

#include <KoTextEditingRegistry.h>

K_PLUGIN_FACTORY(GrammarCheckPluginFactory, registerPlugin<GrammarCheckPlugin>();)
K_EXPORT_PLUGIN(GrammarCheckPluginFactory("GrammarCheckPlugin"))

GrammarCheckPlugin::GrammarCheckPlugin(QObject *parent, const QVariantList&)
    : QObject(parent)
{
    KoTextEditingRegistry::instance()->add(new GrammarCheckFactory());
}

#include <GrammarCheckPlugin.moc>
