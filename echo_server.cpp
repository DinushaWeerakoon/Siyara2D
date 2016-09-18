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
FILE * pFile = fopen("test.json", "r");
char buffer[65536];
rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));


const char json[] = " { \"latitude\" : \"6.97037\", \"Ship_name\" : \"Y101                \" , \"longitute\" : \"60.839915\" } ";

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {

	document.Parse(json);

	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
	document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
	//puts(sb.GetString());

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
    server echo_server;
	

    try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(9002);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();



    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}
