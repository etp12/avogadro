/**********************************************************************
  GaussianInputDialog - Dialog for generating Gaussian input decks

  Copyright (C) 2008 Marcus D. Hanwell

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.sourceforge.net/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#include "gaussianinputdialog.h"

#include <QString>
#include <QTextStream>
#include <QFileDialog>

using namespace OpenBabel;

namespace Avogadro
{

  GaussianInputDialog::GaussianInputDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f), m_molecule(0), m_title("Title"), m_calculationType(OPT),
    m_theoryType(B3LYP), m_basisType(B631Gd), m_multiplicity(1), m_charge(0),
    m_procs(1), m_output(""), m_chk(false)
  {
    ui.setupUi(this);
    // Connect the GUI elements to the correct slots
    connect(ui.titleLine, SIGNAL(editingFinished()),
        this, SLOT(setTitle()));
    connect(ui.calculationCombo, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setCalculation(int)));
    connect(ui.theoryCombo, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setTheory(int)));
    connect(ui.basisCombo, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setBasis(int)));
    connect(ui.multiplicitySpin, SIGNAL(valueChanged(int)),
        this, SLOT(setMultiplicity(int)));
    connect(ui.chargeSpin, SIGNAL(valueChanged(int)),
        this, SLOT(setCharge(int)));
    connect(ui.procSpin, SIGNAL(valueChanged(int)),
        this, SLOT(setProcs(int)));
    connect(ui.outputCombo, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setOutput(int)));
    connect(ui.checkpointCheck, SIGNAL(stateChanged(int)),
        this, SLOT(setChk(int)));
    connect(ui.generateButton, SIGNAL(clicked()),
        this, SLOT(generateClicked()));
    connect(ui.resetButton, SIGNAL(clicked()),
        this, SLOT(resetClicked()));

    // Generate an initial preview of the input deck
    updatePreviewText();
  }

  GaussianInputDialog::~GaussianInputDialog()
  {
  }

  void GaussianInputDialog::setMolecule(Molecule *molecule)
  {
    // Disconnect the old molecule first...
    if (m_molecule)
    {
      disconnect(m_molecule, 0, this, 0);
    }

    m_molecule = molecule;
    // Update the preview text whenever primitives are changed
    connect(m_molecule, SIGNAL(primitiveRemoved(Primitive *)),
            this, SLOT(updatePreviewText()));
    connect(m_molecule, SIGNAL(primitiveAdded(Primitive *)),
            this, SLOT(updatePreviewText()));
    connect(m_molecule, SIGNAL(primitiveUpdated(Primitive *)),
            this, SLOT(updatePreviewText()));
    // Add atom coordinates
    updatePreviewText();
  }

  void GaussianInputDialog::updatePreviewText()
  {
    // Generate the input deck and display it
    ui.previewText->setText(generateInputDeck());
  }

  void GaussianInputDialog::resetClicked()
  {
    // Reset the form to defaults
    ui.calculationCombo->setCurrentIndex(1);
    ui.theoryCombo->setCurrentIndex(3);
    ui.basisCombo->setCurrentIndex(2);
    ui.multiplicitySpin->setValue(0);
    ui.chargeSpin->setValue(0);
    ui.procSpin->setValue(1);
  }
  void GaussianInputDialog::generateClicked()
  {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Gaussian Input Deck"),
                                "", tr("Gaussian Input Deck (*.com)"));
    QFile file(fileName);
    // FIXME This really should pop up a warning if the file cannot be opened
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;

    QTextStream out(&file);
    out << generateInputDeck();
  }

  void GaussianInputDialog::setTitle()
  {
    m_title = ui.titleLine->text();
    updatePreviewText();
  }

  void GaussianInputDialog::setCalculation(int n)
  {
    switch (n)
    {
      case 0:
        m_calculationType = SP;
        break;
      case 1:
        m_calculationType = OPT;
        break;
      case 2:
        m_calculationType = FREQ;
        break;
      default:
        m_calculationType = SP;
    }
    updatePreviewText();
  }

  void GaussianInputDialog::setTheory(int n)
  {
    switch (n)
    {
      case 0:
        m_theoryType = AM1;
        break;
      case 1:
        m_theoryType = PM3;
        break;
      case 2:
        m_theoryType = RHF;
        break;
      case 3:
        m_theoryType = B3LYP;
        break;
      case 4:
        m_theoryType = MP2;
        break;
      case 5:
        m_theoryType = CCSD;
        break;
      default:
        m_theoryType = RHF;
    }
    
    if (m_theoryType == AM1 || m_theoryType == PM3)
      ui.basisCombo->setEnabled(false);
    else
      ui.basisCombo->setEnabled(true);
    
    updatePreviewText();
  }

  void GaussianInputDialog::setBasis(int n)
  {
    switch (n)
    {
      case 0:
        m_basisType = STO3G;
        break;
      case 1:
        m_basisType = B321G;
        break;
      case 2:
        m_basisType = B631Gd;
        break;
      case 3:
        m_basisType = B631Gdp;
        break;
      default:
        m_basisType = B631Gd;
    }
    updatePreviewText();
  }

  void GaussianInputDialog::setMultiplicity(int n)
  {
    m_multiplicity = n;
    updatePreviewText();
  }
  void GaussianInputDialog::setCharge(int n)
  {
    m_charge = n;
    updatePreviewText();
  }

  void GaussianInputDialog::setProcs(int n)
  {
    if (n > 0)
      m_procs = n;
    updatePreviewText();
  }

  void GaussianInputDialog::setOutput(int n)
  {
    switch (n)
    {
      case 1:
        m_output = " gfprint pop=full";
        break;
      case 2:
        m_output = " gfoldprint pop=full";
        break;
      default:
        m_output = "";
    }
    updatePreviewText();
  }

  void GaussianInputDialog::setChk(int n)
  {
    if (n) m_chk = true;
    else m_chk = false;
    updatePreviewText();
  }

  QString GaussianInputDialog::generateInputDeck()
  {
    // Generate an input deck based on the settings of the dialog
    QString buffer;
    QTextStream mol(&buffer);

    // These directives are required before the job specification
    if (m_procs > 1)
      mol << "%NProcShared=" << m_procs << "\n";
    if (m_chk)
      mol << "%Chk=checkpoint.chk\n";

    // Now specify the job type etc
    mol << "#p " << getTheoryType(m_theoryType);

    // Not all theories have a basis set
    if (m_theoryType != AM1 && m_theoryType != PM3)
      mol << "/" << getBasisType(m_basisType);

    // Now for the calculation type
    mol << " " << getCalculationType(m_calculationType);

    // Output parameters for some programs
    mol << m_output;

    // Title line
    mol << "\n\n " << m_title << "\n\n";

    // Now for the charge and multiplicity
    mol << m_charge << " " << m_multiplicity << "\n";

    // Now to output the actual molecular coordinates
    //Atom* atom;
    if (m_molecule)
    {
      QTextStream mol(&buffer);
      FOR_ATOMS_OF_MOL(atom, m_molecule)
      {
        mol << qSetFieldWidth(3) << left << QString(etab.GetSymbol(atom->GetAtomicNum()))
            << qSetFieldWidth(15) << qSetRealNumberPrecision(5) << forcepoint
            << fixed << right << atom->GetX() << atom->GetY() << atom->GetZ()
            << qSetFieldWidth(0) << "\n";
      }
      mol << "\n";
    }

    return buffer;
  }

  QString GaussianInputDialog::getCalculationType(calculationType t)
  {
    // Translate the enum to text for the output generation
    switch (t)
    {
      case SP:
        return "SP";
      case OPT:
        return "Opt";
      case FREQ:
        return "Opt Freq";
      default:
        return "SP";
    }
  }

  QString GaussianInputDialog::getTheoryType(theoryType t)
  {
    // Translate the enum to text for the output generation
    switch (t)
    {
      case AM1:
        return "AM1";
      case PM3:
        return "PM3";
      case RHF:
        return "RHF";
      case B3LYP:
        return "B3LYP";
      case MP2:
        return "MP2";
      case CCSD:
        return "CCSD";
      default:
        return "RHF";
    }
  }

  QString GaussianInputDialog::getBasisType(basisType t)
  {
    // Translate the enum to text for the output generation
    switch (t)
    {
      case STO3G:
        return "STO-3G";
      case B321G:
        return "3-21G";
      case B631Gd:
        return "6-31G(d)";
      case B631Gdp:
        return "6-31G(d,p)";
      default:
        return "6-31G(d)";
    }
  }

}

#include "gaussianinputdialog.moc"
