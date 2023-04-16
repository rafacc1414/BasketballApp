#include "team.h"

#include <QStringList>

team::team()
{
}
team::~team()
{
}

void
team::configure_team(QString &line)
{
    QStringList list = line.split(",");
    m_team_name = list.at(M_TEAM_NAME_IDX);
    m_city_name = list.at(M_CITY_NAME_IDX);
    m_n_players = list.at(M_NUMBER_OF_PLAYERS_IDX).toInt();
    m_n_coachs = list.at(M_NUMBER_OF_COACHES_IDX).toInt();

    unsigned int start_coach_name_idx = M_NUMBER_OF_COACHES_IDX + 1;
    unsigned int last_coach_name_idx = start_coach_name_idx + m_n_coachs;
    for(unsigned int i = start_coach_name_idx; i < last_coach_name_idx; ++i) {
        m_coaches_name.append(list.at(i));
    }
}

QString
team::get_team_name()
{
    return m_team_name;
}

unsigned int
team::get_team_n_coachs()
{
    return m_n_coachs;
}

unsigned int
team::get_team_n_players()
{
    return m_n_players;
}

QString
team::get_team_city_name()
{
    return m_city_name;
}

QStringList
team::get_team_coaches_name()
{
    return m_coaches_name;
}
