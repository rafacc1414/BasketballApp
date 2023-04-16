#ifndef TEAM_INFORMATION_H
#define TEAM_INFORMATION_H

#include <QWidget>
#include <QStandardItemModel>
#include <team.h>
#include <QVBoxLayout>

namespace Ui {
class team_information;
}

class team_information :  public QWidget
{
    Q_OBJECT;

public:
    explicit team_information(QWidget *parent, std::map<QString, team> &teams);
    ~team_information();

private:
    QWidget *m_widget;
    Ui::team_information *ui = NULL;

    QStandardItemModel *m_model = NULL;
    QVBoxLayout *m_team_information_layout;
    int m_search_counter;
    std::map<QString, team> m_teams;

public:
    void create_ui();

private:
    void generate_team_info_ui(team &team_info);
    void generate_player_info_ui(const QString &player_name);
    void refresh_panel_info(const QString &name);
    void refresh_team_info_tree_panel();

private slots:
    void on_SearchTeamButton_clicked();
    void on_TeamInfoTree_clicked(const QModelIndex &index);
};

#endif // TEAM_INFORMATION_H
