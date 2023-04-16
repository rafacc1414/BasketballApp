#ifndef LOAD_TEAMS_H
#define LOAD_TEAMS_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class load_teams;
}

class load_teams : public QWidget
{
    Q_OBJECT

public:
    QString m_file_name;

public:
    explicit load_teams(QWidget *parent = 0);
    ~load_teams();

private:
    Ui::load_teams *ui;

public slots:
    void exit_button_clicked();
    void next_button_clicked();
    void load_button_clicked();

signals:
    void button_clicked(QString);
};

#endif // LOAD_TEAMS_H
