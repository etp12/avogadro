#include "vrmlextension.h"
#include <avogadro/molecule.h>
#include <avogadro/toolgroup.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QCoreApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDebug>
namespace Avogadro
{
	VRMLExtension::VRMLExtension(QObject* parent) : Extension(parent) {
		QAction* action = new QAction(this);
		action->setText(tr("VRML..."));
		m_actions.append(action);
	}

	VRMLExtension::~VRMLExtension() {

	}
	QList<QAction *> VRMLExtension::actions() const
	{
		return m_actions;
	}

	QString VRMLExtension::menuPath(QAction*) const
	{
		return tr("&File") + '>' + tr("Export");
	}
	QUndoCommand* VRMLExtension::performAction(QAction *, GLWidget *widget)
	{
		m_glwidget = widget;
		if (!m_VRMLDialog)
		{
			m_VRMLDialog = new VRMLDialog(static_cast<QWidget*>(parent()), 0);
			//      m_POVRayDialog->setImageSize(m_glwidget->width(), m_glwidget->height());
			connect(m_VRMLDialog, SIGNAL(render()),
				this, SLOT(render()));
			connect(m_glwidget, SIGNAL(resized()),
				m_VRMLDialog, SLOT(resized()));
			m_VRMLDialog->show();
		}
		else {

			m_VRMLDialog->show();
		}
		return 0;
	}
	void VRMLExtension::render() {
	}
}
Q_EXPORT_PLUGIN2(vrmlextension, Avogadro::VRMLExtensionFactory)