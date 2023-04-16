#include "team_information.h"

team_information::team_information(QWidget *widget):
    ui(new Ui::team_information)
{
    m_widget = widget;
    ui->setupUi(this);
}

void
team_information::create_ui()
{

}
