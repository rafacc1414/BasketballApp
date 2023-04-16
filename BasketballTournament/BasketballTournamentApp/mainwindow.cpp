#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "team.h"
#include "tabs/best_players.h"

#include <QTextStream>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableWidgetItem>

#define JUMPING_PLAYER_IMAGE "../images/basketball-player_jumping.png"
#define DUNKING_PLAYER_IMAGE "../images/dunk_done.png"
#define TEAM_INFO 0
#define CLASIFICATION 1
#define TOURNAMENT_BRACKETS 2
#define BEST_PLAYERS 3
std::vector<bool> vf_is_layout_created = {false, false, false, false};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* Initialise all pointers */
    mtimer = NULL;
    m_load_teams = NULL;
    m_tournament_bracket = NULL;
    m_best_players = NULL;

     /* Set the icon of mainwindow */
     this->setWindowIcon((QIcon(JUMPING_PLAYER_IMAGE)));

    /* Get Start Time */
    auto start = std::chrono::system_clock::now();

    ui->setupUi(this);

    /* Create connection to update a tab in the UI */
    connect(this, SIGNAL(update_ui_signal(int)), this, SLOT(on_Basketball_currentChanged(int)));

    /* Load Teams */
    QAction *LoadTeams = ui->actionLoadTeams;
    connect(LoadTeams, SIGNAL(triggered()), this, SLOT(load_teams_action()));

    /* Get End Time */
    auto end = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast < std::chrono::milliseconds > (end - start).count();
    std::cout << "Total Time Taken = " << diff << " miliSeconds" << std::endl;
}

MainWindow::~MainWindow()
{
    if (NULL != m_team_information) {
        delete m_team_information;
    }

    if (NULL != m_tournament_bracket) {
        delete m_tournament_bracket;
    }

    if (NULL != m_tournament_bracket) {
        delete m_best_players;
    }

    delete ui;
}

int
MainWindow::load_game_stadistics(const QString &file)
{
    try {
        QFile f(file);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream input(&f);
            // Unused for now
            //int size = f.size();
            while (!input.atEnd()) {
                QString line = input.readLine();
                if (line.contains("type", Qt::CaseInsensitive)) {
                    continue;
                }
                if (line.contains("TEAM", Qt::CaseInsensitive)) {
                    /* Get the team information */
                    team team_info;
                    team_info.configure_team(line);

                    /* Store the team information */
                    QString team_name = team_info.get_team_name();

                    auto it = m_team.find(team_name);
                    if (it != m_team.end()) {
                        /* Do nothing */
                    } else {
                           m_team[team_name] = team_info;
                           /* Store the team names */
                           m_team_names.append(team_name);
                    }
                }
                if (line.contains("PLAYER", Qt::CaseInsensitive)) {
                    /* Get the player information of the team */
                    basketball_player player_info;
                    player_info.configure_player(line);

                    /* Store the player in the team */
                    QString team_name = player_info.m_team_name;
                    unsigned int shirt_number = player_info.m_shirt_number;

                    auto it = m_team.find(team_name);
                    if (it != m_team.end()) {
                        auto it2 = it->second.m_team_players.find(shirt_number);
                        if (it2 != it->second.m_team_players.end()) {
                            m_team[team_name].m_team_players[shirt_number] = m_team[team_name].m_team_players[shirt_number] + player_info;
                        } else {
                            m_team[team_name].m_team_players[shirt_number] = player_info;
                        }
                    } else {
                        m_team[team_name].m_team_players[shirt_number] = player_info;
                    }
                }
            }
            /* Fill the UI with information */
            emit update_ui_signal(TEAM_INFO);
        }
    }
    catch (...) {
        return -1;
    }
    return 0;
}

void
MainWindow::load_teams_action()
{
    m_load_teams = new load_teams();
    m_load_teams->setWindowIcon((QIcon(DUNKING_PLAYER_IMAGE)));
    m_load_teams->show();
    connect(m_load_teams, SIGNAL(button_clicked(QString)), this, SLOT(load_game_stadistics(QString)));
}

/* Callback when changing between tabs */
void
MainWindow::on_Basketball_currentChanged(int index)
{
    bool is_layout_created = vf_is_layout_created.at(index);

    /* Check if teams are loaded */
    if (m_team_names.size() < 1) {
        return;
    }

    /* Check if the layout is already created */
    if (is_layout_created) {
        return;
    }

    /* Create the layout which correspond */
    switch (index) {
        case TEAM_INFO: {
            if (m_team_names.size() < 1) {
                break;
            } else if (m_team_information != NULL) {
                delete m_team_information;
            }
            m_team_information = new team_information(ui->TeamInformation, m_team);
            m_team_information->create_ui();
            break;
        }
        case CLASIFICATION: {
            break;
        }
        case TOURNAMENT_BRACKETS: {
            if (m_team_names.size() < 1) {
                break;
            } else if (m_tournament_bracket != NULL) {
                delete m_tournament_bracket;
            }
            m_tournament_bracket = new tournament_bracket(ui->TournamentBracket, m_team_names);
            m_tournament_bracket->create_ui();
            break;
        }
        case BEST_PLAYERS: {
        if (m_team_names.size() < 1) {
            break;
        } else if (m_best_players != NULL) {
                delete m_best_players;
        }
            m_best_players = new best_players(ui->BestPlayers, m_team);
            m_best_players->create_ui();
            break;
        }
        default: {
            break;
        }
    }
    vf_is_layout_created[index] = true;

    return;
}

