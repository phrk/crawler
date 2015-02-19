#include "domain_stats.h"

namespace crw {

	DomainStats::DomainStats(const DomainLimits &_limits):
		limits(_limits),
		minute_start(getMinuteBeginning()),
		hour_start(getHourBeginning()),
		current_loading(0),
		minute_loaded(0),
		hour_loaded(0),
		all_loaded(0){
		
	}

	void DomainStats::checkTimers() {
	
		Ts current_min_beg = getMinuteBeginning();
		Ts current_hour_beg = getHourBeginning();
			
		if (minute_start < current_min_beg) {
			
			minute_loaded = 0;
			minute_start = current_min_beg;
		}
			
		if (hour_start < current_hour_beg) {
			
			hour_loaded = 0;
			hour_start = current_hour_beg;
		}
	}

	void DomainStats::startedLoading() {
		
		current_loading++;
	}

	void DomainStats::linkLoaded() {
		
		current_loading--;
		minute_loaded++;
		hour_loaded++;
		all_loaded++;
		
		checkTimers();
	}
	
	bool DomainStats::canDownload() {
		
		if (current_loading >= limits.max_parallel)
			return false;
		if (minute_loaded >= limits.max_minute)
			return false;
		if (hour_loaded >= limits.max_hour)
			return false;
		if (all_loaded >= limits.max_all)
			return false;
		
		return true;
	}

}
