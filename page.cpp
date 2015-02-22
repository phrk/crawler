#include "page.h"

namespace crw {

	Page::Page(const Link &_link):
		link(_link)
		//success(false)
		 {
	
	}
	
	Page::Page(const Link &_link, const std::string &_html):
	link(_link) {
		
		content.html = _html;
	}

}
