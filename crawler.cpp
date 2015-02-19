
#include "crawler.h"

namespace crw {

	Crawler::Crawler(const DomainLimits &_def_domain_limits,
					boost::function<void(PagePtr page)> _onPage):
	m_def_domain_limits(_def_domain_limits),
	m_onPage(_onPage) {
		
	}

	void Crawler::addLink(const Url &_url) {
		
		m_download_queue.push(Link(_url));
	}
	
	void Crawler::proceedEvents() {
		
	}

	Crawler::~Crawler() {
		
	}

}
