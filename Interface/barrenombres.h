#ifndef BARRENOMBRES_H
#define BARRENOMBRES_H

#include <QtGui/QWidget>

class QTextEdit;

class BarreNombres : public QWidget {
    Q_OBJECT

public:
    BarreNombres(QWidget *parent);

    void setTextEdit(QTextEdit *edit);

protected:
    void paintEvent(QPaintEvent *pEvent);

private:
    QTextEdit *m_edit;
};

#endif // BARRENOMBRES_H
