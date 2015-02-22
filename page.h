
#ifndef _CRAWLER_PAGE_H_
#define _CRAWLER_PAGE_H_

#include "hiconfig.h"

#include "crawler_types.h"
#include "crawler_consts.h"
#include "link.h"

#include <boost/shared_ptr.hpp>

#include "gumbo.h"

namespace crw {

	class Content {
	public:
	
		std::string html;
		std::string text;
		
		//std::string get();
		//std::string textOnly();
	};

	class Page {
		
		void findLinks(GumboNode* node);
		
	public:
	
		Link link;
		Content content;
		bool success;
	
		std::vector<Link> outbound_links_in;
		std::vector<Link> outbound_links_out;
	
	//	Page(const Link &_link);
		Page(const Link &_link, const std::string &_html);
	};

	typedef boost::shared_ptr<Page> PagePtr;

}

#endif
