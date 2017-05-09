#include "youdao.h"
#include "def.h"

#include <easylogging++.h>
#include <tinyxml2/tinyxml2.h>
#include <Document.h>
#include <Selection.h>
#include <Node.h>
#include <string_utility.hpp>

std::string string_clear(std::string str) {
    std::string s;
    char last = '0';
    for (auto c : str) {
        if(c == '\n' || c == '\r' || c == ' ') {
            if (last != c && c == ' ') {
                s.append(1, c);
            }
        } else {
            s.append(1, c);
        }
        last = c;
    }
    return s;
}


// http://dict.youdao.com/search?keyfrom=dict.python&q=quit&xmlDetail=true&doctype=xml
// http://dict.youdao.com/search?keyword=dict&q=hello
YoudaoDict::YoudaoDict(const char* url) {
    m_url = std::string(url);
    /*
    m_params["keyfrom"] = std::string("dict");
    m_headers["User-Agent"] =
            "Mac OS X/ Safari: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_2) AppleWebKit/601.3.9 "
            "(KHTML, like Gecko) Version/9.0.2 Safari/601.3.9";
            */
}

YoudaoDict::YoudaoDict(std::string& url) : m_url(url) {
}

YoudaoDict::YoudaoDict() : m_url("http://dict.youdao.com/search"){
}

dict::ResultVectorPtr YoudaoDict::query(const char* word, int type) {
    // m_params["q"] = word;
    // auto res = this->m_bbq->get(m_url, m_params); //, m_headers);
    // LOGD("RES: %s", res.c_str());

    if (type) {
    auto r = cpr::Get(
            m_url, cpr::Parameters{{"keyfrom", "dict.python"}, {"q", std::string(word)}, {"doctype","xml"}}
            /*    ,
            cpr::Header{{"User-Agent",
                         "Mac OS X/ Safari: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_2) "
                         "AppleWebKit/601.3.9 (KHTML, like Gecko) Version/9.0.2 Safari/601.3.9"}}
            */
                );
    if (r.text.length() && r.status_code == 200) {
            dict::ResultVectorPtr values = std::make_shared<dict::ResultVector>();
        //LOGD("RES: %s", r.text.c_str());
            tinyxml2::XMLDocument doc;
            doc.Parse(r.text.c_str());
            auto node = doc.RootElement()->FirstChild();
            LOGD("node: %s", node->ToElement()->GetText());
            while (node) {
                LOGD("custom-translation: %s %s",node->Value(), node->ToElement()->GetText());
                if (memcmp(node->Value(), "return-phrase", 13) == 0) {
                    values->insert("keyword", std::string(node->ToElement()->GetText()));
                } else if (memcmp(node->Value(), "custom-translation", 18) == 0) {
                    auto sub = node->FirstChildElement("translation");
                    while (sub) {
                    LOGD("ELEM: %s", sub->FirstChildElement("content")->GetText());
                    values->insert("translation", std::string(sub->FirstChildElement("content")->GetText()));
                    sub = sub->NextSiblingElement("translation");
                    }
                } else if (memcmp(node->Value(), "yodao-web-dict", 14) == 0) {
                    auto sub = node->FirstChildElement("web-translation");
                    while (sub) {
                    LOGD("ELEM: %s", sub->FirstChildElement("key")->GetText());
                    std::string key = std::string(sub->FirstChildElement("key")->GetText());
                    std::string val;
                    auto trans = sub->FirstChildElement("trans");
                    while(trans) {
                        LOGD("val: %s", trans->FirstChildElement("value")->GetText());
                        val = val + std::string(trans->FirstChildElement("value")->GetText()) + std::string("; ");
                        trans = sub->NextSiblingElement("trans");
                    }
                    values->insert("youdao-translation", key + " : " + val);
                    sub = sub->NextSiblingElement("web-translation");
                    }

                } else if (memcmp(node->Value(), "example-sentences", 17) == 0) {
                    auto sub = node->FirstChildElement("sentence-pair");
                    while (sub) {
                    LOGD("ELEM: %s", sub->FirstChildElement("sentence")->GetText());
                    std::string key = std::string(sub->FirstChildElement("sentence")->GetText());
                    std::string val = std::string(sub->FirstChildElement("sentence-translation")->GetText());
                    values->insert("example", key + "\n" + val);
                    sub = sub->NextSiblingElement("sentence-pair");
                    }
                }
                node = node->NextSibling();
            }
            return values;
    }
    } else {
    auto r = cpr::Get(
            m_url, cpr::Parameters{{"keyfrom", "dict"}, {"q", std::string(word)}},
            cpr::Header{{"User-Agent",
                         "Mac OS X/ Safari: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_2) "
                         "AppleWebKit/601.3.9 (KHTML, like Gecko) Version/9.0.2 Safari/601.3.9"}});

    if (r.text.length() && r.status_code == 200) {
        dict::ResultVectorPtr values = std::make_shared<dict::ResultVector>();
        CDocument doc;
        doc.parse(r.text.c_str());
        CSelection c = doc.find("div #phrsListTab span.keyword");
        for (size_t i = c.nodeNum(); i != 0; i--) {
            values->insert("keyword", string_utility<std::string>::trim(string_clear(c.nodeAt(c.nodeNum() - i).text())));
        }

        c = doc.find("div #phrsListTab ul li");
        for (size_t i = c.nodeNum(); i != 0; i--) {
             LOGD("%s", c.nodeAt(c.nodeNum() - i).text().c_str());
             values->insert("translation", string_utility<std::string>::trim(string_clear(c.nodeAt(c.nodeNum() - i).text())));
        }

        c = doc.find("div #phrsListTab p.additional");
        for (size_t i = c.nodeNum(); i != 0; i--) {
            values->insert("additional", string_utility<std::string>::trim(string_clear(c.nodeAt(c.nodeNum() - i).text())));
        }

        c = doc.find("p.wordGroup");
        for (size_t i = c.nodeNum(); i != 0; i--) {
            values->insert("wordgroup", string_utility<std::string>::trim(string_clear(c.nodeAt(c.nodeNum() - i).text())));
        }

        c = doc.find("div#bk div.content p");
        for (size_t i = c.nodeNum(); i != 0; i--) {
            values->insert("bk", string_utility<std::string>::trim(string_clear(c.nodeAt(c.nodeNum() - i).text())));
        }
        return values;
    }
    }
    return std::make_shared<dict::ResultVector>();
}

dict::ResultVectorPtr YoudaoDict::query(std::string word, int type) {
    return this->query(word.c_str(), type);
}
