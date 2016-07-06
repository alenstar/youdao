#include "querydialog.h"
#include "ui_querydialog.h"
#include <QString>

QueryDialog::QueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    _query = new QueryThread(this);
    connect(_query, &QueryThread::queryResult, this, &QueryDialog::queryResult);
}

QueryDialog::~QueryDialog()
{
    delete ui;
}

void QueryDialog::on_lineEdit_returnPressed()
{
    std::string word = this->ui->lineEdit->text().toStdString();
    if (word.size() > 0) {
        _query->query(word);
    }
}

void QueryDialog::queryResult(dict::ResultVectorPtr ptr)
{
    for(int i = 0; i < ptr->size(); i++) {
        this->ui->textBrowser->append(QString(ptr->at(i - 1).value.c_str()));
    }
}
