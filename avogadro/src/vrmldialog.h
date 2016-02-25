#ifndef VRMLDIALOG_H
#define VRMLDIALOG_H


//#include "ui_vrmldialog.h"
class QDialog;
namespace Avogadro {

	class MainWindow;
	class VRMLDialog : public QDialog 
	{
	public:
		VRMLDialog(MainWindow *mainWindow);

	private:
		Ui::VRMLDialog ui;

		MainWindow *m_mainWindow;

	};
}
#endif
