#pragma once
#include<boost/asio.hpp>

extern boost::asio::io_context MainService;
template<typename FType> inline void RunInMainThread(FType&& Func )
{
	MainService.post(std::forward<FType>(Func));
}