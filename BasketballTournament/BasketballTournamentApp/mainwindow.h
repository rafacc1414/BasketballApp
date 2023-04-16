#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "load_teams.h"
#include "team.h"
#include "tabs/team_information.h"
#include "tabs/tournament_bracket.h"
#include "tabs/best_players.h"

#include <iostream>
#include <unistd.h>
#include <chrono>

#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer *mtimer = NULL;
    load_teams *m_load_teams = NULL;
    QString csvFile;

    /* key = team_name */
    std::map<QString, team> m_team;
    QStringList m_team_names;

    QStandardItemModel *m_model = NULL;

private:
    Ui::MainWindow *ui = NULL;
    team_information *m_team_information = NULL;
    tournament_bracket *m_tournament_bracket = NULL;
    best_players *m_best_players = NULL;

private:
    void generate_team_info_ui(team &team_info);
    void generate_player_info_ui(const QString &player_name);
    void refresh_panel_info(const QString& name);
    void refresh_team_info_tree_panel(void);

signals:
    /* Signal to Update the UI */
    void update_ui_signal(int index);

public slots:
    void load_teams_action();
    int load_game_stadistics(const QString& file);

private slots:
    void on_Basketball_currentChanged(int index);

};

#endif // MAINWINDOW_H
