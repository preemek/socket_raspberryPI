#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{

	if(argc != 3)
	{
		std::cout<<"Incorrect parameter\n"<<std::endl;
		return -1;
	}

	auto const ip_address = boost::asio::ip::make_address(argv[1]);
	auto const port = std::atoi(argv[2]);

	boost::asio::io_service service_io;

	boost::system::error_code ec;
	boost::asio::ip::tcp::acceptor acceptor_(service_io, boost::asio::ip::tcp::endpoint(address, port ));
	boost::asio::ip::tcp::socket socket_(service_io);
	acceptor_.accept(socket_);

	boost::asio::streambuff buff;
	boost::asio::read_until( socket_, buff, "\n",ec);
	if(ec){
	    std::cout<<ec.message()<<std::endl; 
	    return 1;
	    
	}
	std::string client_data = boost::asio::buffer_cast<const char*>(buff.data());
	std::cout << client_data << std::endl;

	boost::asio::write( socket_, boost::asio::buffer(client_data) ,ec);
	if(ec){
	    std::cout<<ec.message()<<std::endl; 
	    return 1;
	    
	}
	return 0;
}