#ifndef TOURNAMENT_BRACKET_H
#define TOURNAMENT_BRACKET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class tournament_bracket
{
public:
    tournament_bracket(QWidget *widget, const QStringList &team_names);
    ~tournament_bracket();

    void create_ui();
    void update_ui();
    void save_structure();
private:
    QWidget *m_widget;
    QStringList m_team_names;
    QPushButton *m_update_btn;
    QPushButton *m_save_btn;

    /* Vector with all the team positions in the bracket */
    std::vector<QLineEdit *> m_pos_chart;
};

#endif // TOURNAMENT_BRACKET_H
