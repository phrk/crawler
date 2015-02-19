#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#include "hiconfig.h"
#include "hiaux/strings/string_utils.h"

#include <queue>

#include "crawler_types.h"
#include "crawler_consts.h"
#include "domain_stats.h"
#include "page.h"

#include <boost/function.hpp>

namespace crw {
	
	class Crawler {
	
		DomainLimits m_def_domain_limits;
		std::map<Domain, DomainStats> m_domains_stats;
	
		boost::function<void(PagePtr page)> m_onPage;
		
		std::queue<Link> m_download_queue;
		
	public:
		
		Crawler(const DomainLimits &_def_domain_limits,
			boost::function<void(PagePtr page)> _onPage);
		
		void addLink(const Url &_url);
		void proceedEvents();
		
		virtual ~Crawler();
	};

};

#endif
