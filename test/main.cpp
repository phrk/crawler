#include "hiconfig.h"
#include "crawler.h"


void onCalledServer(crw::HttpClientA<int>::JobInfo _ji) {
	
	std::cout << "onCalledServer \n";
	if (!_ji.success)
		std::cout << "not success\n";
	
	std::cout << "resp: " << _ji.resp << std::endl;
}

int main (int argv, char **argc) {
	
	crw::HttpClientA<int> cl(boost::bind(&onCalledServer, _1));
	
	cl.call(0, "http://ya.ru");
	cl.call(0, "http://google.ru");
	
	
	cl.kick();
	
	return 0;
}

