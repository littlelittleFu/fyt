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

class WebParse {
public:
	static WebParse* GetInstance();
	static bool Parse(char* buf, uint32_t len, char* sendbuf) {
		using namespace websocketpp;
		namespace wspp = websocketpp;

		size_t processed = 0;
		
        while (processed < len) {

            websocketpp::lib::error_code ec;
            auto p = m_processor->consume(reinterpret_cast<uint8_t*>(buf) + processed, len, ec);
            if (ec) {
                LOG_ERROR("consume failed with error code %d", ec.value());
                m_processor->reset_headers();
                if (p == 0) {
                    break;
                }
                else {
                    processed += p;
                    continue;
                }
            }

            processed += p;
            if (!m_processor->ready()) break;

            auto msg = m_processor->get_message();
            if (!msg) {
                LOG_ERROR("msg is nullptr");
            }
            else if (is_control(msg->get_opcode())) {
                // TODO: handle close opcode
                LOG_ERROR("Unhandled opcode: %d", msg->get_opcode());
            }
            else {      // Êý¾Ý
                const auto& payload = msg->get_payload();
                auto _MsgLen = payload.length();
                std::cout << payload.data() << std::endl;
                memcpy(sendbuf, payload.data(), _MsgLen);
            }
        }
        return true;
	}

    static void EncodeWeb(char* buf, int len) {

        if (!m_processor) {
            LOG_ERROR("m_processor is nullptr");
            return;
        }

        if (!m_msg_manager) {
            LOG_ERROR("m_ws_msg_manager is nullptr");
            return;
        }

        auto in = m_msg_manager->get_message();
        in->set_opcode(websocketpp::frame::opcode::BINARY);

        //auto totalLen = len + sizeof(uint32_t);
        auto& in_payload = in->get_raw_payload();
        //in_payload.resize(len);
        in_payload += "22";
        in_payload += buf;

        auto out = m_msg_manager->get_message();
        auto ec = m_processor->prepare_data_frame(in, out);
        if (ec) {
            LOG_ERROR("prepare_data_frame failed with error %d", ec.value());
            return;
        }

        auto data = out->get_header();
        data += out->get_payload();
        memcpy(buf, data.c_str(), data.size());
    }

private:
	static WebParse* m_Instance;
};

WebParse* WebParse::m_Instance = new WebParse();
WebParse* WebParse::GetInstance() { return m_Instance; };