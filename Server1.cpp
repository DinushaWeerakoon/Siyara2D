#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>
#include <rapidjson/document.h>
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

rapidjson::Document document;

const char json[] = " { \"latitude\" : \"6.97037\", \"Ship_name\" : \"Y101                \" , \"longitute\" : \"60.839915\" } ";

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
	
	document.Parse(json);
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	document.Accept(writer);

    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }

    try {
		s->send(hdl,sb.GetString(), msg->get_opcode());
    } catch (const websocketpp::lib::error_code& e) {
        std::cout << "Echo failed because: " << e
                  << "(" << e.message() << ")" << std::endl;
    }
}

int main() {
    // Create a server endpoint
    server server;
	

    try {
        // Set logging settings
        server.set_access_channels(websocketpp::log::alevel::all);
        server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        server.init_asio();

        // Register our message handler
        server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        server.listen(9002);

        // Start the server accept loop
        server.start_accept();

        // Start the ASIO io_service run loop
        server.run();



    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}
