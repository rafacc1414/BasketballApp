#include "load_teams.h"
#include "ui_load_teams.h"

load_teams::load_teams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::load_teams)
{
    ui->setupUi(this);
    ui->NextButton->setEnabled(false);

    connect(ui->ExitButton, SIGNAL(pressed()), this, SLOT(exit_button_clicked()));
    connect(ui->NextButton, SIGNAL(pressed()), this, SLOT(next_button_clicked()));
    connect(ui->LoadButton, SIGNAL(pressed()), this, SLOT(load_button_clicked()));
}

load_teams::~load_teams()
{
    delete ui;
}

/* -----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ------------------------------------------------- Buttons of load_teams -----------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void
load_teams::exit_button_clicked() {
    this->close();
}

void
load_teams::next_button_clicked() {
    if(m_file_name.isNull() == 0)
    {
        emit button_clicked(m_file_name);
        this->close();
    }
}

void
load_teams::load_button_clicked() {
    m_file_name = QFileDialog::getOpenFileName(this, tr("CSV File"), "", tr("CSV Files (*.csv)"), NULL, QFileDialog::DontUseNativeDialog);
    if (!m_file_name.isEmpty()) {
        ui->PathFile->setText(m_file_name);
    }
    ui->NextButton->setEnabled(true);
    ui->NextButton->setStyleSheet("background-color: rgb(0,255,0);");
}
