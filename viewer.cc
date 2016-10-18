#include "viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent)
{
	// Setup UI
	ui.setupUi(this);

	// Add OpenGL widget
	glViewer = new GLViewer;
	ui.viewLayout->addWidget(glViewer);

	// Initial color value
	color = QColor(0.8 * 255.0, 0.8 * 255.0, 0.8 * 255.0);
	ui.colorPreviewLabel->setPalette(QPalette(color));
	ui.colorPreviewLabel->setAutoFillBackground(true);

	// Connections
	connect(glViewer, SIGNAL(changeCoords(double, double)), this, SLOT(setCoords(double, double)));

	// Connect Objects
	connect(ui.createPlaneButton, SIGNAL(clicked()), glViewer, SLOT(createPlane()));
	connect(ui.createCubeButton, SIGNAL(clicked()), glViewer, SLOT(createCube()));
	connect(ui.createSphereButton, SIGNAL(clicked()), glViewer, SLOT(createSphere()));
	connect(ui.createCylinderButton, SIGNAL(clicked()), glViewer, SLOT(createCylinder()));
	connect(ui.createConeButton, SIGNAL(clicked()), glViewer, SLOT(createCone()));
	connect(ui.createPyramidButton, SIGNAL(clicked()), glViewer, SLOT(createPyramid()));
	connect(ui.createWedgeButton, SIGNAL(clicked()), glViewer, SLOT(createWedge()));

	// Connect infoList
	connect(glViewer, SIGNAL(addToList(QString)), this, SLOT(addToList(QString)));

	// Connect translations
	connect(ui.translateXSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateTranslation()));
	connect(ui.translateYSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateTranslation()));
	connect(ui.translateZSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateTranslation()));
	connect(this, SIGNAL(sendTranslation(int, double, double, double)), glViewer, SLOT(receiveTranslation(int, double, double, double)));

	// Connect rotations
	connect(ui.rotateXSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateRotation()));
	connect(ui.rotateYSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateRotation()));
	connect(ui.rotateZSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateRotation()));
	connect(this, SIGNAL(sendRotation(int, double, double, double)), glViewer, SLOT(receiveRotation(int, double, double, double)));

	// Connect scale
	connect(ui.scaleXSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateScale()));
	connect(ui.scaleYSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateScale()));
	connect(ui.scaleZSpinbox, SIGNAL(valueChanged(double)), this, SLOT(updateScale()));
	connect(this, SIGNAL(sendScale(int, double, double, double)), glViewer, SLOT(receiveScale(int, double, double, double)));

	// Color signals
	connect(ui.editColorButton, SIGNAL(clicked()), this, SLOT(colorWheel()));
	connect(this, SIGNAL(sendColor(int, double, double, double)), glViewer, SLOT(receiveColor(int, double, double, double)));

	// Connect updates
	connect(ui.infoListWidget, SIGNAL(currentRowChanged(int)), glViewer, SLOT(answerInfo(int)));
	connect(this, SIGNAL(manualListUpdate(int)), glViewer, SLOT(answerInfo(int)));
	connect(this, SIGNAL(requestInfo(int)), glViewer, SLOT(answerInfo(int)));
	connect(glViewer, SIGNAL(sendInfo(std::vector<double>)), this, SLOT(receiveInfo(std::vector<double>)));

	// Connect menuBar
	//connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(loadProject()));
	connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionAbout_3, SIGNAL(triggered()), this, SLOT(aboutInfo()));
	connect(ui.actionHelp, SIGNAL(triggered()), this, SLOT(helpInfo()));

	// Connect remove signals
	connect(ui.removeButton, SIGNAL(clicked()), this, SLOT(removeObjectClicked()));
	connect(this, SIGNAL(removeObject(int)), glViewer, SLOT(removeObject(int)));

	// Connect save and load functionality
	connect(this, SIGNAL(callSave(QString)), glViewer, SLOT(saveFile(QString)));
	connect(this, SIGNAL(callLoad(QString)), glViewer, SLOT(loadFile(QString)));

	// Connect for populate list function
	connect(glViewer, SIGNAL(addToList()), this, SLOT(addToList()));
}

void Viewer::setCoords(double x, double y)
{
	QString xStr = QString::number(x);
	QString yStr = QString::number(y);
	ui.statusBar->showMessage("(x, y) : (" + xStr + ", " + yStr + ")", 5000);
}

void Viewer::addToList(QString str)
{
	ui.infoListWidget->addItem(str);
	QListWidgetItem * item = ui.infoListWidget->item(ui.infoListWidget->count() - 1); // Get last item
	item->setFlags (item->flags () | Qt::ItemIsEditable); // Make item editable
	ui.infoListWidget->setCurrentItem(item); // Set selection to last item
}

void Viewer::addToList()
{
	ui.infoListWidget->blockSignals(true);
	ui.infoListWidget->addItem("Nameless");
	QListWidgetItem * item = ui.infoListWidget->item(ui.infoListWidget->count() - 1);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	ui.infoListWidget->setCurrentItem(item);
	ui.infoListWidget->blockSignals(false);
}

void Viewer::updateTranslation()
{
	emit sendTranslation(ui.infoListWidget->currentRow(), ui.translateXSpinbox->value(), ui.translateYSpinbox->value(), ui.translateZSpinbox->value());
}

void Viewer::updateRotation()
{
	emit sendRotation(ui.infoListWidget->currentRow(), ui.rotateXSpinbox->value(), ui.rotateYSpinbox->value(), ui.rotateZSpinbox->value());
}

void Viewer::updateScale()
{
	emit sendScale(ui.infoListWidget->currentRow(), ui.scaleXSpinbox->value(), ui.scaleYSpinbox->value(), ui.scaleZSpinbox->value());
}

void Viewer::receiveInfo(std::vector<double> info)
{
	// Temporarily block signals
	ui.translateXSpinbox->blockSignals(true);
	ui.translateYSpinbox->blockSignals(true);
	ui.translateZSpinbox->blockSignals(true);
	ui.rotateXSpinbox->blockSignals(true);
	ui.rotateYSpinbox->blockSignals(true);
	ui.rotateZSpinbox->blockSignals(true);
	ui.scaleXSpinbox->blockSignals(true);
	ui.scaleXSpinbox->blockSignals(true);
	ui.scaleXSpinbox->blockSignals(true);

	ui.translateXSpinbox->setValue(info[0]);
	ui.translateYSpinbox->setValue(info[1]);
	ui.translateZSpinbox->setValue(info[2]);
	ui.rotateXSpinbox->setValue(info[3]);
	ui.rotateYSpinbox->setValue(info[4]);
	ui.rotateZSpinbox->setValue(info[5]);
	ui.scaleXSpinbox->setValue(info[6]);
	ui.scaleYSpinbox->setValue(info[7]);
	ui.scaleZSpinbox->setValue(info[8]);
	QColor tempColor = QColor(info[9] * 255.0, info[10] * 255.0, info[11] * 255.0);
	ui.colorPreviewLabel->setPalette(QPalette(tempColor));

	// Re-enable signals
	ui.translateXSpinbox->blockSignals(false);
	ui.translateYSpinbox->blockSignals(false);
	ui.translateZSpinbox->blockSignals(false);
	ui.rotateXSpinbox->blockSignals(false);
	ui.rotateYSpinbox->blockSignals(false);
	ui.rotateZSpinbox->blockSignals(false);
	ui.scaleXSpinbox->blockSignals(false);
	ui.scaleXSpinbox->blockSignals(false);
	ui.scaleXSpinbox->blockSignals(false);
}

void Viewer::newProject()
{
	//qDebug() << "newProject";
	// Remove old OpenGL widget
	ui.viewLayout->removeWidget(glViewer);
	delete glViewer;

	// Reset sidebar and all inputs
	ui.infoListWidget->clear();
	color = QColor(0.8 * 255.0, 0.8 * 255.0, 0.8 * 255.0);
	ui.colorPreviewLabel->setPalette(QPalette(color));

	ui.translateXSpinbox->setValue(0.0);
	ui.translateYSpinbox->setValue(0.0);
	ui.translateZSpinbox->setValue(0.0);
	ui.rotateXSpinbox->setValue(0.0);
	ui.rotateYSpinbox->setValue(0.0);
	ui.rotateZSpinbox->setValue(0.0);
	ui.scaleXSpinbox->setValue(0.0);
	ui.scaleYSpinbox->setValue(0.0);
	ui.scaleZSpinbox->setValue(0.0);

	// Add OpenGL widget
	glViewer = new GLViewer;
	ui.viewLayout->addWidget(glViewer);
}

void Viewer::saveProject()
{
	//qDebug() << "saveProject";
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Project"), "samples/untitled.vox", tr("VOX Files (*.vox)"));
	emit callSave(fileName);
}

void Viewer::loadProject()
{

	//qDebug() << "loadProject";
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "samples/", tr("VOX Files (*.vox)"));
	emit callLoad(fileName);
}

void Viewer::removeObjectClicked()
{
	int row = ui.infoListWidget->currentRow();
	emit removeObject(row);
	ui.infoListWidget->blockSignals(true);
	delete ui.infoListWidget->item(row);
	ui.infoListWidget->blockSignals(false);
	emit manualListUpdate(ui.infoListWidget->currentRow());
	;
}

void Viewer::colorWheel()
{
	QColor tempColor = QColorDialog::getColor(Qt::white, this);

	if (tempColor.isValid())
	{
		color = tempColor;
		ui.colorPreviewLabel->setPalette(QPalette(color));
		emit sendColor(ui.infoListWidget->currentRow(), color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0);
	}
}

void Viewer::aboutInfo()
{
	QMessageBox *aboutDialog = new QMessageBox;
	aboutDialog->setWindowTitle("About");
	QString str = "Voxel Playground is about letting your dreams become a reality. \n\nCopyright 2016 Voxel Incorporated";
	aboutDialog->setInformativeText(str);
	aboutDialog->exec();
}

void Viewer::helpInfo()
{
	QMessageBox *helpDialog = new QMessageBox;
	helpDialog->setWindowTitle("Help");
	QString str = "Inserting Objects:\n- Use the buttons under the create tab.\n\nDeleting Objects:\n- Use the delete button under the objects list.\n\nEdit Color:\n- Use Edit Color Button.\n\nEditting Objects:\n- Use the edit tab to control translation, rotation and scale of each object.\n\nCamera Movements:\n   - Move: Left click and drag.\n   - Zoom: Hold left and right mouse buttons and drag forward or back.\n   - Rotate: Right click and drag.\n\nLoad & Save: \n- Files are saved and loaded under a \"*.vox\" extension.\n- The Scene must be empty before perfoming a load operation.\n\nOther Notes: \n- Resizing window is possible.\n- Creating a new project was a buggy feature, so a program restart is required.\n\n";
	helpDialog->setInformativeText(str);
	helpDialog->exec();
}