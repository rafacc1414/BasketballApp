#include "basketball_player.h"

basketball_player::basketball_player()
{
    m_n_matches = 0;
}

basketball_player::~basketball_player()
{

}

void
basketball_player::configure_player(QString &line)
{
    QStringList list = line.split(",");

    m_team_name = list.at(M_TEAM_NAME_IDX);
    m_shirt_number = list.at(M_SHIRT_NUMBER_IDX).toInt();
    m_player_name = list.at(M_PLAYER_NAME_IDX);
    m_minutes_played = list.at(M_MINUTES_PLAYED_IDX).toInt();
    m_points = list.at(M_POINTS_IDX).toInt();

    m_t1_s = list.at(M_T1_S_IDX).toInt();
    m_t2_s = list.at(M_T2_S_IDX).toInt();
    m_t3_s = list.at(M_T3_S_IDX).toInt();

    m_t1_f = list.at(M_T1_F_IDX).toInt();
    m_t2_f = list.at(M_T2_F_IDX).toInt();
    m_t3_f = list.at(M_T3_F_IDX).toInt();

    m_dunks = list.at(M_DUNKS_IDX).toInt();

    m_received_fault = list.at(M_RECEIVED_FAULT_IDX).toInt();
    m_personal_fault = list.at(M_PERSONAL_FAULT_IDX).toInt();

    m_defensive_rebound = list.at(M_DEFENSIVE_REBOUND_IDX).toInt();
    m_offensive_rebound = list.at(M_OFFENSIVE_REBOUND_IDX).toInt();

    m_steals = list.at(M_STEALS_IDX).toInt();
    m_losts = list.at(M_LOSTS_IDX).toInt();
    m_assists = list.at(M_ASSISTS_IDX).toInt();

    m_blocked_received = list.at(M_BLOCKED_RECEIVED_IDX).toInt();
    m_blocked_done = list.at(M_BLOCKED_DONE_IDX).toInt();

    m_n_matches = 1;
}

int
basketball_player::calculate_valoration()
{
    int valoration = 0;
    int positive_actions = 0;
    int negative_actions = 0;

    positive_actions = m_points + m_dunks + m_steals + m_assists + m_blocked_done + m_received_fault + m_defensive_rebound + m_offensive_rebound;
    negative_actions = m_t1_f + m_t2_f + m_t3_f + m_losts + m_blocked_received + m_personal_fault;

    valoration = positive_actions - negative_actions;
    return valoration;
}
basketball_player
basketball_player::operator+(const basketball_player& other) const {
            basketball_player player_update;

            player_update.m_team_name = other.m_team_name;
            player_update.m_shirt_number = other.m_shirt_number;
            player_update.m_player_name = other.m_player_name;
            player_update.m_n_matches = m_n_matches;

            player_update.m_minutes_played = ((m_minutes_played * m_n_matches) + other.m_minutes_played)/ (m_n_matches + 1);
            player_update.m_points = ((m_points * m_n_matches)+ other.m_points) / (m_n_matches + 1);

            player_update.m_t1_s = ((m_t1_s * m_n_matches) + other.m_t1_s) / (m_n_matches + 1);
            player_update.m_t2_s = ((m_t2_s * m_n_matches) + other.m_t2_s) / (m_n_matches + 1);
            player_update.m_t3_s = ((m_t3_s * m_n_matches) + other.m_t3_s) / (m_n_matches + 1);

            player_update.m_t1_f = ((m_t1_f * m_n_matches) + other.m_t1_f) / (m_n_matches + 1);
            player_update.m_t2_f = ((m_t2_f * m_n_matches) + other.m_t2_f) / (m_n_matches + 1);
            player_update.m_t3_f = ((m_t3_f * m_n_matches) + other.m_t3_f) / (m_n_matches + 1);

            player_update.m_dunks = ((m_dunks * m_n_matches) + other.m_dunks) / (m_n_matches + 1);

            player_update.m_received_fault = ((m_received_fault * m_n_matches) + other.m_received_fault) / (m_n_matches + 1);
            player_update.m_personal_fault = ((m_personal_fault * m_n_matches) + other.m_personal_fault) / (m_n_matches + 1);

            player_update.m_defensive_rebound = ((m_defensive_rebound * m_n_matches) + other.m_defensive_rebound) / (m_n_matches + 1);
            player_update.m_offensive_rebound = ((m_offensive_rebound * m_n_matches) + other.m_offensive_rebound) / (m_n_matches + 1);

            player_update.m_steals = ((m_steals * m_n_matches) + other.m_steals) / (m_n_matches + 1);
            player_update.m_losts = ((m_losts * m_n_matches) + other.m_losts) / (m_n_matches + 1);
            player_update.m_assists = ((m_assists * m_n_matches) + other.m_assists) / (m_n_matches + 1);

            player_update.m_blocked_received = ((m_blocked_received * m_n_matches) + other.m_blocked_received) / (m_n_matches + 1);
            player_update.m_blocked_done = ((m_blocked_done * m_n_matches) + other.m_blocked_done) / (m_n_matches + 1);

            ++player_update.m_n_matches;

        return player_update;
    }
