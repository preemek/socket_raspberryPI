#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char* argv[]) 
{

	if(argc != 4)
	{
		std::cout<<"Incorrect parameter\n"<<std::endl;	
		return -1;
	}

	auto const address = boost::asio::ip::make_address(argv[1]);
	auto const port = std::atoi(argv[2]);
	std::string msg = argv[3];
	
	msg = msg + '\n';

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);


	boost::system::error_code ec;
 	socket.connect( boost::asio::ip::tcp::endpoint( address, port ),ec);
	if(ec)
	{
	    std::cout<<ec.message()<<std::endl; 
	    return 1;
	    
	}


	boost::system::error_code error;
	boost::asio::write( socket, boost::asio::buffer(msg), error );
	
	if(error)
	{
		std::cout << "Error occures: " << error.message() << std::endl;
    }

	boost::asio::streambuf buffer_rec;
	boost::asio::read(socket, buffer_rec, boost::asio::transfer_all(), error);
	
	if( error && error != boost::asio::error::eof ) 
	{
		std::cout << "Receiving error: " << error.message() << std::endl;
	}
	else 
	{
		const char* data = boost::asio::buffer_cast<const char*>(buffer_rec.data());
		std::cout << data << std::endl;
    }
    return 0;
}