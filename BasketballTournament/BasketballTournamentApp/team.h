#ifndef TEAM_H
#define TEAM_H

#include <map>

#include <QString>
#include <QStringList>
#include <basketball_player.h>

class team : public basketball_player
{
private:
    QString m_team_name;
    unsigned int m_n_coachs;
    unsigned int m_n_players;
    QString m_city_name;
    QStringList m_coaches_name;

    /* line identificator of each attributes */
    static constexpr unsigned short M_TEAM_NAME_IDX = 1;
    static constexpr unsigned short M_CITY_NAME_IDX = 2;
    static constexpr unsigned short M_NUMBER_OF_PLAYERS_IDX = 3;
    static constexpr unsigned short M_NUMBER_OF_COACHES_IDX = 4;

public:
    /* Data structure to store the team information (key = shirt_name, value the class) */
    std::map<unsigned int, basketball_player> m_team_players;

public:

    team();
    ~team();
    void configure_team(QString &line);
    QString get_team_name();
    unsigned int get_team_n_coachs();
    unsigned int get_team_n_players();
    QString get_team_city_name();
    QStringList get_team_coaches_name();
};

#endif // TEAM_H
