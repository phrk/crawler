#ifndef _CRAWLER_LINK_H_
#define _CRAWLER_LINK_H_

#include "hiconfig.h"

#include "crawler_types.h"
#include "crawler_consts.h"

#include <boost/shared_ptr.hpp>

namespace crw {

	class Link {
	public:
	
		Url url;
		Domain domain;
		Path path;
		
		Link(const Url &_url);
	};

}

#endif
