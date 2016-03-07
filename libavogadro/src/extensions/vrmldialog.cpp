#include "vrmldialog.h"
#include <QDialog>
#include <QList>

#include <Eigen/Core>

namespace Avogadro
{

	VRMLDialog::VRMLDialog(QWidget* parent, Qt::WindowFlags f)
		:QDialog(parent, f) {
		ui.setupUi(this);
	}
	VRMLDialog::~VRMLDialog() {

	}
	void VRMLDialog::setFileName(const QString& fileName) {

	}


} // End namespace Avogadro
