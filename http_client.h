#ifndef _CRAWLER_HTTP_CLIENT_ASYNC_H_
#define _CRAWLER_HTTP_CLIENT_ASYNC_H_ 

#include <curl/curl.h>

#include <boost/function.hpp>
#include <string>

#include "hiaux/common/common.h"
#include "hiaux/structs/hashtable.h"
#include "hiaux/threads/locks.h"


#include <sys/select.h>

#include "hiaux/threads/tasklauncher.h"
#include <iostream>

namespace crw {

// not thread safe
template<class ODataT>
class HttpClientA {
public:
	
	class JobInfo {
	public:
		JobInfo(ODataT _userdata, const std::string &_postdata);
		
		ODataT userdata;
		
		std::string resp;
		bool success;
		std::string postdata;
	};
	
private:
	
	hiaux::hashtable<CURL*, JobInfo> m_e_curls;
	
	CURLM *m_curl;
	
	boost::function<void(HttpClientA::JobInfo _ji)> m_onCalled;
	
	bool m_iskicking;
	
	void performTransfers();
public:
	
	HttpClientA(boost::function<void(HttpClientA::JobInfo _ji)> _onCalled);
	~HttpClientA();
	
	int getRequestsCount();
	void call (ODataT userdata, const std::string &_url);
	void callPost (ODataT userdata, const std::string &_url, const std::string &_postdata);
	void kick();
};

//typedef boost::shared_ptr<HttpClientA> HttpClientAPtr;

size_t crawl_function_pt(void *ptr, size_t size, size_t nmemb, std::string *stream);
void _http_client_async_onFinished();

#include "http_client.impl"

}

#endif
