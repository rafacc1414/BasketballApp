#include "best_players.h"
#include "QVBoxLayout"
#include "QLabel"
#include "QTableWidget"
#include "QTableWidgetItem"
#include "QHeaderView"

best_players::best_players(QWidget *widget, std::map<QString, team> &teams)
{
    m_widget = widget;
    m_team = teams;

    this->calculate_table();
}

void
best_players::calculate_table()
{
    for(auto &iter1: m_team) {
        for(auto &iter2: iter1.second.m_team_players) {
            auto key = std::make_pair(iter2.second.m_player_name, iter2.second.m_team_name);
            m_information information = {};
            information.points = iter2.second.m_points;
            information.steals = iter2.second.m_steals;
            information.assist = iter2.second.m_assists;
            information.rebound = iter2.second.m_offensive_rebound + iter2.second.m_defensive_rebound;
            information.blocks = iter2.second.m_blocked_done;

            /* Insert in the map */
            m_data[key] = information;
        }
    }

    for (auto const& pair : m_data) {
        m_data_order.push_back(pair);
    }
}

void best_players::create_ui()
{
    m_rankingLayout = new QVBoxLayout;
    m_rankingTable = new QTableWidget;
    m_rankingTable->setRowCount(m_data.size()); // Set the number of rows for the ranking
    m_rankingTable->setColumnCount(7); // Set the number of columns (rank and name)

    // Set the column headers
    m_rankingTable->setHorizontalHeaderLabels({"Name", "Team", "Points", "Steals", "Assists", "Rebounds", "Blocks"});
    // Set the column headers
    m_rankingTable->verticalHeader()->setVisible(false);

    /* Reserve memory for the arrays */
    m_nameItem.resize(m_data_order.size());
    m_teamItem.resize(m_data_order.size());
    m_pointItem.resize(m_data_order.size());
    m_stealItem.resize(m_data_order.size());
    m_assistItem.resize(m_data_order.size());
    m_reboundItem.resize(m_data_order.size());
    m_blockItem.resize(m_data_order.size());

    /* Initialize the pointers */
    for (unsigned int i = 0; i < m_data_order.size(); ++i) {
      m_nameItem[i] = nullptr;
      m_teamItem[i] = nullptr;
      m_pointItem[i] = nullptr;
      m_stealItem[i] = nullptr;
      m_assistItem[i] = nullptr;
      m_reboundItem[i] = nullptr;
      m_blockItem[i] = nullptr;
    }

    unsigned int i = 1;
    /* Populate the ranking items */
    for (auto &element:m_data_order) {
        // Create a name item
        QString player_name = element.first.first;
        m_nameItem[i] = new QTableWidgetItem(player_name);

        // Create a name item
        QString team_name = element.first.second;
        m_teamItem[i] = new QTableWidgetItem(team_name);

        // Create a name item
        QString points = QString::number(element.second.points);
        m_pointItem[i] = new QTableWidgetItem(points);

        // Create a name item
        QString steals = QString::number(element.second.steals);
        m_stealItem[i] = new QTableWidgetItem(steals);

        // Create a name item
        QString assists = QString::number(element.second.assist);
        m_assistItem[i] = new QTableWidgetItem(assists);

        // Create a name item
        QString rebounds = QString::number(element.second.rebound);
        m_reboundItem[i] = new QTableWidgetItem(rebounds);

        // Create a name item
        QString blocks = QString::number(element.second.blocks);
        m_blockItem[i] = new QTableWidgetItem(blocks);

        // Add all the items to the table
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_NAME_IDX, m_nameItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_TEAM_NAME_IDX, m_teamItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_POINT_IDX, m_pointItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_STEAL_IDX, m_stealItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_ASSIST_IDX, m_assistItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_REBOUND_IDX, m_reboundItem[i]);
        m_rankingTable->setItem(i-1, M_BEST_PLAYERS_BLOCK_IDX, m_blockItem[i]);

        ++i;
    }

    m_rankingLayout->addWidget(m_rankingTable);
    m_widget->setLayout(m_rankingLayout);

    // Get a pointer to the horizontal header of the table
    QHeaderView* horizontalHeader = m_rankingTable->horizontalHeader();
    // Connect a slot to the sectionClicked() signal of the horizontal header for each column
    connect(horizontalHeader, &QHeaderView::sectionClicked, this, [=](int index) {
        switch(index) {
            case M_BEST_PLAYERS_POINT_IDX: {
                this->order_by_point();
                this->update_table();
                break;
            }
            case M_BEST_PLAYERS_STEAL_IDX: {
                this->order_by_steals();
                this->update_table();
                break;
            }
            case M_BEST_PLAYERS_ASSIST_IDX: {
                this->order_by_assists();
                this->update_table();
                break;
            }
            case M_BEST_PLAYERS_REBOUND_IDX: {
                this->order_by_rebounds();
                this->update_table();
                break;
            }
            case M_BEST_PLAYERS_BLOCK_IDX: {
                this->order_by_blocks();
                this->update_table();
                break;
            }
        }
    });
}

void
best_players::update_table() {
    unsigned int i = 1;
    // Populate the ranking items
    for (auto &element:m_data_order) {
        // Create a name item
        QString player_name = element.first.first;
        m_nameItem[i]->setText(player_name);

        // Create a name item
        QString team_name = element.first.second;
        m_teamItem[i]->setText(team_name);

        // Create a name item
        QString points = QString::number(element.second.points);
        m_pointItem[i]->setText(points);

        // Create a name item
        QString steals = QString::number(element.second.steals);
        m_stealItem[i]->setText(steals);

        // Create a name item
        QString assists = QString::number(element.second.assist);
        m_assistItem[i]->setText(assists);

        // Create a name item
        QString rebounds = QString::number(element.second.rebound);
        m_reboundItem[i]->setText(rebounds);

        // Create a name item
        QString blocks = QString::number(element.second.blocks);
        m_blockItem[i]->setText(blocks);

        ++i;
    }
}

void
best_players::order_by_point() {
    std::sort(m_data_order.begin(), m_data_order.end(), [](auto const& a, auto const& b) {
        return a.second.points > b.second.points;
    });
}

void
best_players::order_by_steals() {
    std::sort(m_data_order.begin(), m_data_order.end(), [](auto const& a, auto const& b) {
        return a.second.steals > b.second.steals;
    });
}

void
best_players::order_by_assists() {
    std::sort(m_data_order.begin(), m_data_order.end(), [](auto const& a, auto const& b) {
        return a.second.assist > b.second.assist;
    });
}

void
best_players::order_by_rebounds() {
    std::sort(m_data_order.begin(), m_data_order.end(), [](auto const& a, auto const& b) {
        return a.second.rebound > b.second.rebound;
    });
}

void
best_players::order_by_blocks() {
    std::sort(m_data_order.begin(), m_data_order.end(), [](auto const& a, auto const& b) {
        return a.second.blocks > b.second.blocks;
    });
}
