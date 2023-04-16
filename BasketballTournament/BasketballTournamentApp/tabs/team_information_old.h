#ifndef TEAM_INFORMATION_OLD_H
#define TEAM_INFORMATION_OLD_H

#include <QWidget>

namespace Ui {
class team_information;
}

class team_information: public QWidget
{
    Q_OBJECT

public:
    team_information(QWidget *widget);
    void create_ui();
private:
    QWidget *m_widget;
    Ui::team_information *ui = NULL;
};

#endif // TEAM_INFORMATION_OLD_H
