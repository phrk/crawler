#ifndef _DOMAIN_STATS_H_
#define _DOMAIN_STATS_H_

#include "hiconfig.h"

#include "hiaux/common/common.h"

#include "crawler_types.h"
#include "crawler_consts.h"


namespace crw {

	class DomainLimits {
	public:
		
		Cnt max_parallel;
		Cnt max_minute;
		Cnt max_hour;
		Cnt max_all;
	};

	class DomainStats {
	
		void checkTimers();
	
	public:
		
		DomainLimits limits;
		
		Ts minute_start;
		Ts hour_start;	
			
		Cnt current_loading;
		Cnt minute_loaded;
		Cnt hour_loaded;
		Cnt all_loaded;
		
		DomainStats(const DomainLimits &_limits);
		void startedLoading();
		void linkLoaded();
		bool canDownload();
	};
}


#endif
