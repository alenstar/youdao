#include "querydialog.h"
#include "ui_querydialog.h"

#include "dict/youdao.h"
#include "thpool/thpoolcpp.h"

class Queryer : public ThreadJob
{
private:
    QueryDialog *dialog;
    std::string word;
public:
    Queryer(QueryDialog *dialog, const char *word)
    {
        this->word = std::string(word);
        this->dialog = dialog;
    }
    void run()
    {
        YoudaoDict *yd = new YoudaoDict("http://dict.youdao.com/search");
        assert(this->word.c_str());
        auto res = yd->query(this->word);
        dialog->showExplain(res);
        delete yd;
        delete this;
    }
};

QueryDialog::QueryDialog(QWidget *parent) :
    MDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    this->setup(this, this->ui->mainLayout);
    this->setOnClose([]() {
        qApp->quit();
    });
    QString title = "有道翻译";
    this->setTitle(title);
    connect(this, &QueryDialog::doShowExplain, this, &QueryDialog::onShowExplain);
    new ThreadPool(2);
}

QueryDialog::~QueryDialog()
{
    delete ui;
    delete ThreadPool::getSingletonPtr();
}

void QueryDialog::on_lineEdit_returnPressed()
{
    std::string word = this->ui->lineEdit->text().toStdString();
    if (word.size() > 0) {
        Queryer *q = new Queryer(this, word.c_str());
        ThreadPool::getSingletonPtr()->add(q);
    }
}

void QueryDialog::onShowExplain(dict::ResultVectorPtr ptr)
{
    this->ui->textBrowser->clear();
    this->ui->lineEdit->clear();
    QString phonetic = "";
    for (int i = 0; i < ptr->size(); i++) {
        if(ptr->at(i - 0).session == std::string("phonetic")) {
            phonetic += " " + QString(ptr->at(i - 0).value.c_str());
            this->ui->ukPhonetic->setText(phonetic);
        }
        else if(ptr->at(i - 0).session == std::string("keyword")) {
            this->ui->wordLab->setText(" " + QString(ptr->at(i - 0).value.c_str()));
        } else {
            this->ui->textBrowser->append(QString(ptr->at(i - 0).value.c_str()));
            //this->ui->textBrowser->setText(QString(ptr->at(i - 0).value.c_str()));
        }
    }
    delete ptr;
}

void QueryDialog::showExplain(dict::ResultVectorPtr ptr)
{
    emit this->doShowExplain(ptr);
}
