#ifndef BEST_PLAYERS_H
#define BEST_PLAYERS_H

#include <QWidget>
#include "team.h"
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QVBoxLayout>

class best_players : QObject
{
public:
    best_players(QWidget *widget, std::map<QString, team> &teams);
    void create_ui();

public:
    static constexpr unsigned short M_BEST_PLAYERS_NAME_IDX = 0;
    static constexpr unsigned short M_BEST_PLAYERS_TEAM_NAME_IDX = 1;
    static constexpr unsigned short M_BEST_PLAYERS_POINT_IDX = 2;
    static constexpr unsigned short M_BEST_PLAYERS_STEAL_IDX = 3;
    static constexpr unsigned short M_BEST_PLAYERS_ASSIST_IDX = 4;
    static constexpr unsigned short M_BEST_PLAYERS_REBOUND_IDX = 5;
    static constexpr unsigned short M_BEST_PLAYERS_BLOCK_IDX = 6;
    /* Struct to store all the information to show */
    struct m_information {
        unsigned int points;
        unsigned int steals;
        unsigned int assist;
        unsigned int rebound;
        unsigned int blocks;
    };
    /* Contains all the team information */
    /* It stores as key (player name, team name) */
    std::map<std::pair<QString,QString>, m_information> m_data;
    std::vector<std::pair<std::pair<QString,QString>, m_information>> m_data_order;

    std::map<QString, team> m_team;

private:
    QWidget *m_widget;
    QVBoxLayout* m_rankingLayout;
    QTableWidget* m_rankingTable;

    std::vector<QTableWidgetItem*> m_nameItem;
    std::vector<QTableWidgetItem*> m_teamItem;
    std::vector<QTableWidgetItem*> m_pointItem;
    std::vector<QTableWidgetItem*> m_stealItem;
    std::vector<QTableWidgetItem*> m_assistItem;
    std::vector<QTableWidgetItem*> m_reboundItem;
    std::vector<QTableWidgetItem*> m_blockItem;

    /* Prepare all the data need to display in the table */
    void calculate_table();
    void update_table();

    void order_by_point();
    void order_by_steals();
    void order_by_assists();
    void order_by_rebounds();
    void order_by_blocks();


};

#endif // BEST_PLAYERS_H
