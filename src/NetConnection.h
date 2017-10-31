#ifndef TELEGRAMBOTAPI_NET_CONNECTION_H
#define TELEGRAMBOTAPI_NET_CONNECTION_H

#include <string>

#include <curl/curl.h>

namespace TelegramBotApi
{

class NetConnection
{

/*[=================*/public:/*=================]*/
    int init(const std::string& token);

    std::string getUpdates(const std::string& updateId = "") const;

    std::string sendMessage(const std::string& chat_id,
                            const std::string& msg,
                            const std::string& replyId = "") const;


    std::string sendSticker(const std::string& chat_id,
                            const std::string& sticker,
                            const std::string& replyId = "") const;

    std::string answerInlineQuery(const std::string& inlineQueryId,
                                  const std::string& results) const;

/*[=================*/private:/*=================]*/
    std::string performRequest(const std::string& url) const;

/*[=================*/private:/*=================]*/
    std::string m_mainUrl   = "https://api.telegram.org/bot";

    std::string m_method    = "/getUpdates";

    std::string m_token;

    // std::string  m_updateId ; // update_id

    CURL* m_c;

};

}

#endif  //TELEGRAMBOTAPI_NET_CONNECTION_H
