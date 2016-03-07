#ifndef VRMLDIALOG_H
#define VRMLDIALOG_H
#include "config.h"

#include <QDialog>
#include <QList>

#include <Eigen/Core>

#include "ui_vrmldialog.h"

namespace Avogadro {

	class VRMLDialog : public QDialog 
	{
	Q_OBJECT
	public:
		explicit VRMLDialog(QWidget* parent, Qt::WindowFlags f);
		~VRMLDialog();
		void setFileName(const QString& fileName);
	
	public Q_SLOTS:	
		void selectDirectory();

	private:
		Ui::VRMLDialog ui;
		QString path;

	};
}
#endif
