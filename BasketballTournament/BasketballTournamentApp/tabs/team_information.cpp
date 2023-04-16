#include "team_information.h"
#include "ui_team_information.h"

team_information::team_information(QWidget *parent, std::map<QString, team> &teams)
{
    m_widget = parent;
    ui = new Ui::team_information;

    m_search_counter = 0;
    m_teams = teams;

    // Create a vertical layout for the parent widget
    m_team_information_layout = new QVBoxLayout ;
}

team_information::~team_information() {
    delete ui;
}

void
team_information::create_ui()
{
    ui->setupUi(this);

    /* Update the UI */
    this->refresh_team_info_tree_panel();

    // add the child widget to the layout
//    layout.setStretchFactor(this, 1);
    m_team_information_layout->addWidget(this);
    m_widget->setLayout(m_team_information_layout);
}

void
team_information::on_SearchTeamButton_clicked()
{
    QString text = ui->SearchTeamSearcher->text();
    if(text.isEmpty()) {
        return;
    }

    QAbstractItemModel *team_info_model = ui->TeamInfoTree->model();
    QModelIndexList indexes = team_info_model->match(team_info_model->index(0,0),Qt::EditRole,text,-1, Qt::MatchFlags(Qt::MatchRecursive));

    /* if we do not match with a team name, we search in the player names */
    if (indexes.length() > 0) {
        QModelIndex ix = indexes.at(0);
        ui->TeamInfoTree->setCurrentIndex(ix);
        ui->TeamInfoTree->scrollTo(ix);
        ui->TeamInfoTree->selectionModel()->select(ix , QItemSelectionModel::Rows | QItemSelectionModel::Select);
    }
    m_search_counter++;
}

void
team_information::generate_team_info_ui(team &team_info) {
    QStringList coaches_name = team_info.get_team_coaches_name();
    unsigned int n_players = team_info.get_team_n_players();

    /* Fill the UI information for a player */
    QStandardItem *city_name_item_name = new QStandardItem("City Name");
    QStandardItem *city_name_item = new QStandardItem(team_info.get_team_city_name());

    QStandardItem *coach_name_item_name = new QStandardItem("Coach");
    QStandardItem *coach_name_item = new QStandardItem(coaches_name[0]);

    QStandardItem *number_players_item_name = new QStandardItem("Number of players");
    QStandardItem *number_players_item = new QStandardItem(QString::number(n_players));

    m_model->setItem(0, 0, city_name_item_name);
    m_model->setItem(0, 1, city_name_item);

    m_model->setItem(1, 0, coach_name_item_name);
    m_model->setItem(1, 1, coach_name_item);

    m_model->setItem(2, 0, number_players_item_name);
    m_model->setItem(2, 1, number_players_item);

    return;
}

void
team_information::generate_player_info_ui(const QString &player_name) {
    /* Iterate over the configured teams */
    for (auto const &team: m_teams)
    {
        /* Iterate over each player of a team */
        for(auto const & player: team.second.m_team_players)
        {
            if (player.second.m_player_name.compare(player_name) == 0) {
                /* Fill the UI information for a player */
                QStandardItem *minutes_played_item_name = new QStandardItem("Minutes Played");
                QStandardItem *minutes_played_item = new QStandardItem(QString::number(player.second.m_minutes_played));

                QStandardItem *points_item_name = new QStandardItem("Points");
                QStandardItem *points_item = new QStandardItem(QString::number(player.second.m_points));

                QStandardItem *steals_item_name = new QStandardItem("Steals");
                QStandardItem *steals_item = new QStandardItem(QString::number(player.second.m_steals));

                QStandardItem *losts_item_name = new QStandardItem("Losts");
                QStandardItem *losts_item = new QStandardItem(QString::number(player.second.m_losts));

                QStandardItem *assists_item_name = new QStandardItem("Assists");
                QStandardItem *assists_item = new QStandardItem(QString::number(player.second.m_assists));

                QStandardItem *personal_faults_item_name = new QStandardItem("Personal Faults");
                QStandardItem *personal_faults_item = new QStandardItem(QString::number(player.second.m_personal_fault));

                QStandardItem *rebounds_item_name = new QStandardItem("Rebounds");
                QStandardItem *rebounds_item = new QStandardItem(QString::number(player.second.m_defensive_rebound + player.second.m_offensive_rebound));

                QStandardItem *n_matches_item_name = new QStandardItem("Number of matches");
                QStandardItem *n_matches_item = new QStandardItem(QString::number(player.second.m_n_matches));

                m_model->setItem(0, 0, minutes_played_item_name);
                m_model->setItem(0, 1, minutes_played_item);

                m_model->setItem(1, 0, points_item_name);
                m_model->setItem(1, 1, points_item);

                m_model->setItem(2, 0, steals_item_name);
                m_model->setItem(2, 1, steals_item);

                m_model->setItem(3, 0, losts_item_name);
                m_model->setItem(3, 1, losts_item);

                m_model->setItem(4, 0, assists_item_name);
                m_model->setItem(4, 1, assists_item);

                m_model->setItem(5, 0, personal_faults_item_name);
                m_model->setItem(5, 1, personal_faults_item);

                m_model->setItem(6, 0, rebounds_item_name);
                m_model->setItem(6, 1, rebounds_item);

                m_model->setItem(7, 0, n_matches_item_name);
                m_model->setItem(7, 1, n_matches_item);

                return;
            }
        }
    }
    return;
}

void
team_information::refresh_panel_info(const QString &name)
{
    m_model = new QStandardItemModel();

    /* Check if the name is for a team or for a player */
    if (m_teams.find(name) != m_teams.end()) {
        /* Key found */
        team team_info = m_teams[name];
        this->generate_team_info_ui(team_info);
    } else {
        this->generate_player_info_ui(name);
    }

    /* Set the model */
    ui->PlayerInformation->setModel(m_model);
    /* Stablish the style */
    ui->PlayerInformation->setStyleSheet("QTableView{border : 5px solid black}");
    /* Remove the numbers of the row and columns */
    ui->PlayerInformation->horizontalHeader()->setHidden(true);
    ui->PlayerInformation->verticalHeader()->setHidden(true);
    /* Resize the window to fill all the avaliable space */
    ui->PlayerInformation->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void
team_information::refresh_team_info_tree_panel()
{
    QStandardItemModel *model = new QStandardItemModel();
    for (auto const &team: m_teams)
    {
        QStandardItem *team_name = new QStandardItem(team.first);
        model->appendRow(team_name);
        for(auto const & player: team.second.m_team_players)
        {
            QStandardItem *player_name = new QStandardItem(player.second.m_player_name);
            team_name->appendRow(player_name);
        }
    }

    ui->TeamInfoTree->setModel(model);

    /* Remove the number */
    ui->TeamInfoTree->setHeaderHidden(true);

    /* Aply border style */
    ui->TeamInfoTree->setStyleSheet("QTreeView{border : 5px solid black}");
    /* Aply border style */
    ui->PlayerInformation->setStyleSheet("QTableView{border : 5px solid black}");
}

void
team_information::on_TeamInfoTree_clicked(const QModelIndex &index)
{
    QVariant data =index.data();
    QString name = data.toString();

    this->refresh_panel_info(name);
}
