#ifndef VRMLEXTENSION_H
#define VRMLEXTENSION_H

#include "vrmldialog.h"

#include <avogadro/glwidget.h>
#include <avogadro/extension.h>

class QProcess;

namespace Avogadro
{
	class VRMLExtension : public Extension
	{
	Q_OBJECT
		AVOGADRO_EXTENSION("VRML", tr("VRML"),
			tr("Create VRML files"))
	public: 
		VRMLExtension(QObject * parent = 0);
		~VRMLExtension();
		virtual QList<QAction *> actions() const;
		virtual QString menuPath(QAction* action) const;
		virtual QUndoCommand* performAction(QAction *action, GLWidget *widget);

	private:
		QList<QAction *> m_actions;
		GLWidget* m_glwidget;
		VRMLDialog* m_VRMLDialog;

	private Q_SLOTS:
		void render();
	};
	class VRMLExtensionFactory : public QObject, public PluginFactory
	{
		Q_OBJECT
			Q_INTERFACES(Avogadro::PluginFactory)
			AVOGADRO_EXTENSION_FACTORY(VRMLExtension)
	};

}


#endif