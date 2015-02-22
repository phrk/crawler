#include "link.h"

namespace crw {
	
	Link::Link(const Url &_url, bool _inverted) {
		
		//url = _url;
		
		ParsedUrl parsed(_url, _inverted);
		url = parsed.withoutParams();
		
		if (!parsed.ok) {

			//std::cout << "Link::Link !parsed.ok " << url << std::endl;
			throw IncorrectUrlEx();
		}
		domain = parsed.host;
		url_without_params = parsed.withoutParams();
		inverted_url = parsed.getInverted();
	}
	
}
