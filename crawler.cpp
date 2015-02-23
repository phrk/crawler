
#include "crawler.h"

namespace crw {

	Crawler::Crawler(const DomainLimits &_def_domain_limits,
					boost::function<void(PagePtr page)> _onPage):
	m_def_domain_limits(_def_domain_limits),
	m_onPage(_onPage),
	m_client( CrawlerHttpClientPtr(new HttpClientA<Link>( boost::bind(&Crawler::onCalledServer, this, _1) ))) { 
		
	}

	void Crawler::enqueueLink(const Link &_link) {
		
		m_download_queue.push(_link);
	}
	
	DomainStats& Crawler::getDomainStats(const Link &_link) {
		
		
		std::map<Domain, DomainStats>::iterator it = m_domains_stats.find(_link.domain);
		
		if (it == m_domains_stats.end()) {
			m_domains_stats.insert( std::make_pair(_link.domain, DomainStats( m_def_domain_limits )) );
			it = m_domains_stats.find(_link.domain);
		}
		
		return  (it->second);
	}
	
	void Crawler::proceedEvents() {
		
		for (int i = 0; i<20; i++) {
			
			if (m_download_queue.empty())
				break;
		
			Link link = m_download_queue.front();
			m_download_queue.pop();
			
			DomainStats& stats = getDomainStats(link);
			
			if (stats.canDownload()) {
				
				m_client->call(link, link.url);
				stats.startedLoading();
			
			} else {
				//std::cout << "Crawler::proceedEvents cannot download beacause of limits\n";
				m_download_queue.push(link);
			}
			if ( m_client->getRequestsCount() >= 10 )	
				break;
		}
		
		m_client->kick();
	}

	void Crawler::onCalledServer(CrawlerHttpClient::JobInfo _ji) {
		
		DomainStats& stats = getDomainStats(_ji.userdata);
		stats.linkLoaded();
		
		PagePtr page(new Page( _ji.userdata, _ji.resp ) );
		
		if (!_ji.success)
			page->success = false;
		else
			page->success = true;
		
		m_onPage( page );
	}

	Crawler::~Crawler() {
		
	}

}
