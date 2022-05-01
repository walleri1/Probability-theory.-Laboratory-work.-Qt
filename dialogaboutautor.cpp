#include "dialogaboutautor.h"
#include "ui_dialogaboutautor.h"

DialogAboutAutor::DialogAboutAutor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutAutor)
{
    ui->setupUi(this);
}

DialogAboutAutor::~DialogAboutAutor()
{
    delete ui;
}
