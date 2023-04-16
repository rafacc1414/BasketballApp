#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>

class basketball_player
{

private:
    /* line identificator of each attributes */
    static constexpr unsigned short M_TEAM_NAME_IDX = 1;
    static constexpr unsigned short M_SHIRT_NUMBER_IDX = 2;
    static constexpr unsigned short M_PLAYER_NAME_IDX = 3;
    static constexpr unsigned short M_MINUTES_PLAYED_IDX = 4;
    static constexpr unsigned short M_POINTS_IDX = 5;

    static constexpr unsigned short M_T1_S_IDX = 6;
    static constexpr unsigned short M_T2_S_IDX = 7;
    static constexpr unsigned short M_T3_S_IDX = 8;

    static constexpr unsigned short M_T1_F_IDX = 9;
    static constexpr unsigned short M_T2_F_IDX = 10;
    static constexpr unsigned short M_T3_F_IDX = 11;

    static constexpr unsigned short M_DUNKS_IDX = 12;

    static constexpr unsigned short M_RECEIVED_FAULT_IDX = 13;
    static constexpr unsigned short M_PERSONAL_FAULT_IDX = 14;

    static constexpr unsigned short M_DEFENSIVE_REBOUND_IDX = 15;
    static constexpr unsigned short M_OFFENSIVE_REBOUND_IDX = 16;

    static constexpr unsigned short M_ASSISTS_IDX = 17;
    static constexpr unsigned short M_STEALS_IDX = 18;
    static constexpr unsigned short M_LOSTS_IDX = 19;

    static constexpr unsigned short M_BLOCKED_RECEIVED_IDX = 20;
    static constexpr unsigned short M_BLOCKED_DONE_IDX = 21;

public:
    QString m_team_name;
    QString m_player_name;
    unsigned int m_shirt_number;
    unsigned int m_minutes_played;
    unsigned int m_points;

    /* shoots scored */
    unsigned int m_t1_s;
    unsigned int m_t2_s;
    unsigned int m_t3_s;

    /* shoots failed */
    unsigned int m_t1_f;
    unsigned int m_t2_f;
    unsigned int m_t3_f;

    /* dunks performed */
    unsigned int m_dunks;

    /* faults */
    unsigned int m_received_fault;
    unsigned int m_personal_fault;
    /* rebounds */
    unsigned int m_defensive_rebound;
    unsigned int m_offensive_rebound;

    /* team gaming */
    unsigned int m_steals;
    unsigned int m_losts;
    unsigned int m_assists;
    /* blocks*/
    unsigned int m_blocked_received;
    unsigned int m_blocked_done;

    /* number of matches */
    unsigned int m_n_matches;

public:
    basketball_player();
    ~basketball_player();
    void configure_player(QString &line);
    int calculate_valoration();
    basketball_player operator +(const basketball_player &other) const;
};

#endif // PLAYER_H
