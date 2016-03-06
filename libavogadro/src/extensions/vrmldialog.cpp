#include "vrmldialog.h"


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
