#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#include "hiconfig.h"
#include "hiaux/strings/string_utils.h"
#include "hiaux/network/HttpClientAsync.h"

#include <queue>

#include "crawler_types.h"
#include "crawler_consts.h"
#include "domain_stats.h"
#include "page.h"

#include "http_client.h"

#include <boost/function.hpp>

namespace crw {
	
	class Crawler {
	
		DomainLimits m_def_domain_limits;
		std::map<Domain, DomainStats> m_domains_stats;
	
		boost::function<void(PagePtr page)> m_onPage;
		
		std::queue<Link> m_download_queue;
		
		typedef HttpClientA<Link> CrawlerHttpClient;
		typedef boost::shared_ptr< CrawlerHttpClient > CrawlerHttpClientPtr;
		CrawlerHttpClientPtr m_client;
		
		void onCalledServer(CrawlerHttpClient::JobInfo _ji);
		DomainStats& getDomainStats(const Link &_link);
		
	public:
		
		Crawler(const DomainLimits &_def_domain_limits,
			boost::function<void(PagePtr page)> _onPage);
		
		void enqueueLink(const Link &_link);
		void proceedEvents();
		
		virtual ~Crawler();
	};

	typedef boost::shared_ptr<Crawler> CrawlerPtr;

};

#endif
