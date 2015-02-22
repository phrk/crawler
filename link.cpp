#include "link.h"

namespace crw {
	
	Link::Link(const Url &_url) {
		
		url = _url;
		
		ParsedUrl parsed(_url);
		
		if (!parsed.ok)
			throw IncorrectUrlEx();
		
		domain = parsed.host;
		url_without_params = parsed.withoutParams();
	}
	
}
