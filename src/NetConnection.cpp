#include "NetConnection.h"

#include <curl/curl.h>
#include <iostream>

/*[==========================================================================]*/
namespace
{

/*[==========================================================================]*/
static int writer(char* data, size_t size, size_t nmemb, std::string* buffer)
{
    int result = 0;
    if (0 != buffer)
    {
        //добавляем к буферу строки из data, в количестве nmemb
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}


/*[==========================================================================]*/
std::string performSystem(const std::string command)
{
    std::string out;
    FILE *in;
    char buff[512];

    if(!(in = popen(command.c_str(), "r")))
    {      }
    else
    {
        while(fgets(buff, sizeof(buff), in)!=NULL)
        {   out += buff;   }
        pclose(in);
    }
    return out;
}


}
/*[==========================================================================]*/




/*[==========================================================================]*/
namespace TelegramBotApi
{

/*[==========================================================================]*/
int NetConnection::init(const std::string& token)
{
    m_token = token;
    return m_token.size();
}

/*[==========================================================================]*/
std::string NetConnection::getUpdates(const std::string& updateId) const
{

    std::string method = "/getUpdates";
    std::string url = m_mainUrl + m_token + method;

    // /*DEBUG*/ std::cout << "[DD] " << url << "\n";

    if (0 != updateId.size())
    {   url += "?offset=" + updateId;   }

    // /*DEBUG*/ std::cout << "[DD] " << url << "\n";
    return performRequest(url);
}


/*[==========================================================================]*/
std::string NetConnection::sendMessage(const std::string& chatId,
                                       const std::string& msg,
                                       const std::string& replyId) const
{

    std::string method = "/sendMessage";
    std::string url = m_mainUrl + m_token + method;

    if (0 != chatId.size())
    {
        url += "?chat_id=" + chatId;
        if (0 != msg.size())
        {   url += "&text=" + msg;   }
        if (0 != replyId.size())
        {   url += "&reply_to_message_id=" + replyId;   }
    }

    // /*DEBUG*/ std::cout << "[DD] " << url << "\n";

    return performRequest(url);
}

/*[==========================================================================]*/
std::string NetConnection::sendPhoto(const std::string& chatId,
                                       const std::string& msg,
                                       const std::string& filePath,
                                       const std::string& replyId) const
{
    if (0 != chatId.size())
    {
        return performSystem("./sendphoto.sh "+m_token+" "+chatId+" "+filePath);
    }
    return "";
}

/*[==========================================================================]*/
std::string NetConnection::sendSticker(const std::string& chatId,
                                       const std::string& sticker,
                                       const std::string& replyId) const
{

    std::string method = "/sendSticker";
    std::string url = m_mainUrl + m_token + method;

    if (0 != chatId.size())
    {
        url += "?chat_id=" + chatId;
        if (0 != sticker.size())
            url += "&sticker=" + sticker;
        if (0 != replyId.size())
            url += "&reply_to_message_id=" + replyId;
    }
    return performRequest(url);
}

/*[==========================================================================]*/
std::string NetConnection::answerInlineQuery(const std::string& inlineQueryId,
                                             const std::string& results) const
{
    std::string method = "/answerInlineQuery";
    std::string url = m_mainUrl + m_token + method;

    url += "?inline_query_id=" + inlineQueryId;
    url += "&results=" + results;
    return performRequest(url);
}

/*[==========================================================================]*/
std::string NetConnection::performRequest(const std::string& url, const std::string& post) const
{
    std::string result;
    CURL* _c = curl_easy_init();
    static char errorBuffer[CURL_ERROR_SIZE];
    if (0 != _c)
    {
        CURLcode res;
        curl_easy_setopt(_c, CURLOPT_URL, url.c_str());
        if (0 != post.size())
        {
          // curl_formadd
            // curl_easy_setopt(_c, CURLOPT_POST, 1);
            // curl_easy_setopt(_c, CURLOPT_POSTFIELDS, post.c_str());
        }
        curl_easy_setopt(_c, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(_c, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(_c, CURLOPT_ERRORBUFFER, errorBuffer);

        res = curl_easy_perform(_c);
        if (CURLE_OK == res)
        {   std::cout << "[II] " << result.size() << " bytes get\n";   }
        else
        {   std::cout << "[EE] " << errorBuffer << "\n";   }

      std::cout << "[II] " << result.c_str() << " \n";

        curl_easy_cleanup(_c);
    }

    return result;
}


}
/*[==========================================================================]*/
