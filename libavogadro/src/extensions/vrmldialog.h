#ifndef VRMLDIALOG_H
#define VRMLDIALOG_H
#include <QDialog>

#include "ui_vrmldialog.h"

namespace Avogadro {

	class VRMLDialog : public QDialog 
	{
		Q_OBJECT;
	public:
		explicit VRMLDialog(QWidget* parent, Qt::WindowFlags f);
		~VRMLDialog();
		/**
		* Set the file name of the POV-Ray file
		*/
		void setFileName(const QString& fileName);

	private:
		Ui::VRMLDialog ui;

	};
}
#endif
