
#ifndef _CRAWLER_PAGE_H_
#define _CRAWLER_PAGE_H_

#include "hiconfig.h"

#include "crawler_types.h"
#include "crawler_consts.h"
#include "link.h"

#include <boost/shared_ptr.hpp>

namespace crw {

	class Content {
		std::string html;
		std::string text;
	public:
		
		std::string get();
		std::string textOnly();
	};

	class Page {
	public:
	
		Link link;
		Content content;
		bool success;
	
		std::vector<Link> outbound_links_in;
		std::vector<Link> outbound_links_out;
	
		Page(const Url &_url);
	};

	typedef boost::shared_ptr<Page> PagePtr;

}

#endif
