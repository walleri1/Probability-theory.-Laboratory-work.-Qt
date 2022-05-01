#ifndef DIALOGABOUTAUTOR_H
#define DIALOGABOUTAUTOR_H

#include <QDialog>

namespace Ui {
class DialogAboutAutor;
}

class DialogAboutAutor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAboutAutor(QWidget *parent = 0);
    ~DialogAboutAutor();

private:
    Ui::DialogAboutAutor *ui;
};

#endif // DIALOGABOUTAUTOR_H
