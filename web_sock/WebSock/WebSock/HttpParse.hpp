#pragma once
#include "Log.h"
#include <iostream>
#include <cstdint>
#include <websocketpp/processors/hybi00.hpp>
#include <websocketpp/processors/hybi07.hpp>
#include <websocketpp/processors/hybi08.hpp>
#include <websocketpp/processors/hybi13.hpp>

#include <websocketpp/config/core.hpp>
#include <websocketpp/processors/processor.hpp>

using ws_config = websocketpp::config::core;
using ws_processor = websocketpp::processor::processor<ws_config>;
using ws_processor_ptr = websocketpp::lib::shared_ptr<ws_processor>;
using msg_manager = ws_config::con_msg_manager_type;
using msg_manager_ptr = msg_manager::ptr;
using rng_type = ws_config::rng_type;

static msg_manager_ptr m_msg_manager = nullptr;
static ws_processor_ptr m_processor = nullptr;
static rng_type m_rng;

class HttpParse {
public:
	static HttpParse* GetInstance(); 
	static bool Parse(const char* buf, uint32_t len, char* sendbuf) {
		using namespace websocketpp;
		namespace wspp = websocketpp;

		size_t processed = 0;
		wspp::http::parser::request req;
		m_msg_manager = lib::make_shared<msg_manager>();

		if (!m_msg_manager) m_msg_manager = lib::make_shared<msg_manager>();

		try {
			processed = req.consume(buf, strlen(buf));
		}
		catch (wspp::http::exception& e) {
			LOG_ERROR("parse exception: %s", e.what());
			//m_RecvPos = 0;
			return false;
		}

		if (!req.ready()) {
			//if (m_RecvPos > 1024) m_RecvPos = 0;
			return false;
		}

		if (wspp::processor::is_websocket_handshake(req)) {

			auto version = wspp::processor::get_websocket_version(req);

			switch (version) {
			case 0:
				m_processor = lib::make_shared<processor::hybi00<ws_config>>(false, true, m_msg_manager);
				break;
			case 7:
				m_processor = lib::make_shared<processor::hybi07<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
				break;
			case 8:
				m_processor = lib::make_shared<processor::hybi08<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
				break;
			case 13:
				m_processor = lib::make_shared<processor::hybi13<ws_config>>(false, true, m_msg_manager, lib::ref(m_rng));
				break;
			default:
				break;
			}

			if (m_processor) {
				auto ec = m_processor->validate_handshake(req);

				if (ec) {
					LOG_ERROR("validate_handshake failed with error %d", ec.value());
				}
				else {
					wspp::http::parser::response rsp;
					ec = m_processor->process_handshake(req, "", rsp);
					if (ec) {
						LOG_ERROR("process_handshake failed with error %d", ec.value());
					}
					else {
						rsp.set_version("HTTP/1.1");
						rsp.set_status(wspp::http::status_code::switching_protocols);
						rsp.append_header("Sec-WebSocket-Protocol", "binary");
						auto ans = rsp.raw();
						memcpy(sendbuf, ans.c_str(),ans.size());
						return true;
					}

				}
			}
		}
		return false;
	}

private:
	static HttpParse*m_Instance;
};

HttpParse* HttpParse::m_Instance = new HttpParse();
HttpParse* HttpParse::GetInstance() { return m_Instance; };