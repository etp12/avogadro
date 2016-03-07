#include "vrmldialog.h"
#include <QDialog>
#include <QList>
#include <QFileDialog>
#include <Eigen/Core>
#include <QMessageBox>
namespace Avogadro
{

	VRMLDialog::VRMLDialog(QWidget* parent, Qt::WindowFlags f)
		:QDialog(parent, f) {
		path = QDir::currentPath();
		ui.setupUi(this);
		ui.lineEdit->setText(path);
		connect(ui.pushButton, SIGNAL(pressed()), this,
			SLOT(selectDirectory()));
		
	}
	VRMLDialog::~VRMLDialog() {

	}
	void VRMLDialog::setFileName(const QString& fileName) {

	}
	void VRMLDialog::selectDirectory() {
		QString newPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
			path,
			QFileDialog::ShowDirsOnly
			| QFileDialog::DontResolveSymlinks);
		ui.lineEdit->setText(newPath);
	}

} // End namespace Avogadro
