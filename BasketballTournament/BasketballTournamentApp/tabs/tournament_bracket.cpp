#include "tournament_bracket.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QHBoxLayout>

#include <QtWidgets>

tournament_bracket::tournament_bracket(QWidget *widget, const QStringList &team_names)
{
    m_widget = widget;
    m_team_names = team_names;
}

tournament_bracket::~tournament_bracket()
{
    for (unsigned int i = 0; i < m_pos_chart.size(); ++i) {
        if(m_pos_chart[i] != NULL) {
            delete m_pos_chart[i];
        }
    }
}

void
tournament_bracket::create_ui()
{
    /* Calculate the number of columns (rounds of the tournament) */
    unsigned int number_of_columns = log2(m_team_names.size()) + 1;
    /* Calculate the number of rows */
    unsigned int number_of_rows = m_team_names.size() * 2 - 1;

    /* Reorder randomly the teams */
    std::random_shuffle(m_team_names.begin(), m_team_names.end());

    /* Create a new grid layout */
    QGridLayout *layout = new QGridLayout(m_widget);
    QString styleSheet = "border: 1px solid black";

    /* Control variables */
    unsigned int n_space_start_end = 0;
    unsigned int n_space_mid = 0;
    unsigned int n_columns = number_of_columns;

    /* Set the size of the vector and initialize its elements to null */
    m_pos_chart.resize(number_of_columns * number_of_rows);
    for (auto& ptr : m_pos_chart) {
      ptr = nullptr;
    }

    unsigned int pos_grid = 0;
    for(unsigned int col = 0; col < number_of_columns - 1; ++col) {
        unsigned int row = 0;
        n_space_mid = col * 2 + 1;

        unsigned int row_start = n_space_start_end;
        unsigned int row_end = number_of_rows - (n_space_start_end + 1);

        /* First Team */
        row = row + row_start;

        pos_grid = col * number_of_rows + row;
        m_pos_chart[pos_grid] = new QLineEdit();
        m_pos_chart[pos_grid]->setAlignment(Qt::AlignCenter);
        m_pos_chart[pos_grid]->setStyleSheet(styleSheet);
        if (col == 0) {
            unsigned int team_n = row / 2;
            m_pos_chart[pos_grid]->setText(m_team_names[team_n].arg(team_n).arg(col));
        }
        layout->addWidget(m_pos_chart[pos_grid], row, col);

        /* Middle team */
        if (n_columns > 2) {
            row += n_space_mid + 1;
            for (; row < row_end; row += n_space_mid + 1) {
                pos_grid = col * number_of_rows + row;
                m_pos_chart[pos_grid] = new QLineEdit();
                m_pos_chart[pos_grid]->setAlignment(Qt::AlignCenter);
                m_pos_chart[pos_grid]->setStyleSheet(styleSheet);
                if (col == 0) {
                    unsigned int team_n = row / 2;
                    m_pos_chart[pos_grid]->setText(m_team_names[team_n].arg(team_n).arg(col));
                }
                layout->addWidget(m_pos_chart[pos_grid], row, col);
            }
        }

        /* Last team */
        pos_grid = col * number_of_rows + row_end;
        m_pos_chart[pos_grid] = new QLineEdit();
        m_pos_chart[pos_grid]->setAlignment(Qt::AlignCenter);
        m_pos_chart[pos_grid]->setStyleSheet(styleSheet);
        if(col == 0) {
            unsigned int team_n = row / 2;
            m_pos_chart[pos_grid]->setText(m_team_names[team_n].arg(team_n).arg(col));
        }
        layout->addWidget(m_pos_chart[pos_grid], row_end, col);

        --n_columns;
        n_space_start_end = n_space_mid;
    }

    /* Winner */
    pos_grid = (number_of_columns * number_of_rows) - number_of_rows/2;
    m_pos_chart[pos_grid] = new QLineEdit();
    m_pos_chart[pos_grid]->setAlignment(Qt::AlignCenter);
    m_pos_chart[pos_grid]->setStyleSheet(styleSheet);
    layout->addWidget(m_pos_chart[pos_grid], number_of_rows/2, number_of_columns);

    /* Update Button */
    m_update_btn = new QPushButton("Update");
    /* Set the size policy of the button */
    m_update_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_update_btn->setFixedSize(100, 25);
    m_update_btn->setStyleSheet("background-color: grey; color: white; font-weight: bold;");
    /* Create a QPixmap object with an image file */
    QPixmap pixmap_update_btn("../images/icons8-available-updates-52.png");
    /* Set the QPixmap object as the icon for the button */
    m_update_btn->setIcon(QIcon(pixmap_update_btn));
    m_update_btn->setIconSize(m_update_btn->size());
    layout->addWidget(m_update_btn, number_of_rows + 2, number_of_columns, Qt::AlignHCenter);

    /* Save Button */
    m_save_btn = new QPushButton("Save");
    /* Set the size policy of the button */
    m_save_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_save_btn->setFixedSize(100, 25);
    m_save_btn->setStyleSheet("background-color: grey; color: white; font-weight: bold;");
    /* Create a QPixmap object with an image file */
    QPixmap pixmap_save_btn("../images/icons8-save-100.png");
    /* Set the QPixmap object as the icon for the button */
    m_save_btn->setIcon(QIcon(pixmap_save_btn));
    m_save_btn->setIconSize(m_save_btn->size());
    layout->addWidget(m_save_btn, number_of_rows + 2, number_of_columns, Qt::AlignRight);
}

void
tournament_bracket::update_ui()
{

}

void
tournament_bracket::save_structure() {

}
