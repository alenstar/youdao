#include <QApplication>
#include "ui/querydialog.h"
#include "ui/helper.h"
#include "dict/youdao.h"
#include "dict/def.h"

#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

Q_DECLARE_METATYPE(dict::ResultVectorPtr)
int main(int argc, const char **argv)
{
    START_EASYLOGGINGPP(argc, argv);
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
                                       "%datetime %func[%fbase] %level: %msg");
    std::string word;
    if (argc < 2) {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif

        QApplication a(argc, (char **)argv);
        qRegisterMetaType<dict::ResultVectorPtr>();
        Helper::SetStyle("gray");
        QueryDialog w;
        w.show();
        return a.exec();
    } else {
        for (int i = 1; i < argc ; i++) {
            if (word.size()) {
                word = word + " " + std::string(argv[i]);
            } else {
                word = std::string(argv[i]);
            }

        }
    }
    //el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %func[%fbase] %level: %msg");

    YoudaoDict dict("http://dict.youdao.com/search");
    auto res = dict.query(word, 1);
    for (int i = res->size(); i > 0; i--) {
        LOGD("%s: %s", res->at(i - 1).session.c_str(), res->at(i - 1).value.c_str());
    }
    return 0;
}
