#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    string *str = (string *)userdata;
    str->append(ptr, realsize);
    return realsize;
}

int main() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        string url = "https://www.google.com/search?q=banana&tbm=isch";
        string buffer;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            ofstream outfile("banana_urls.txt");
            size_t pos = buffer.find("imgurl=");
            while (pos != string::npos) {
                size_t endpos = buffer.find("&amp;", pos + 1);
                string imgurl = buffer.substr(pos + 7, endpos - pos - 7);
                outfile << imgurl << endl;
                pos = buffer.find("imgurl=", endpos);
            }
            outfile.close();
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
