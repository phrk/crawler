#ifndef _CRAWLER_LINK_H_
#define _CRAWLER_LINK_H_

#include "hiconfig.h"

#include "hiaux/thirdparty/url-parser/url_parser.h"

#include "crawler_types.h"
#include "crawler_consts.h"

#include <boost/shared_ptr.hpp>

#include <iostream>

namespace crw {

	class IncorrectUrlEx {
	};

	class Link {
	public:
	
		Url url;
		Url inverted_url;
		Url url_without_params;
		Domain domain;
		
		// if domain is inverted
		Link(const Url &_url, bool _inverted = false);
	};

}

#endif
