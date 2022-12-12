// Copyright 2020 PayPal Inc.
//
// Licensed to the Apache Software Foundation (ASF) under one or more
// contributor license agreements.  See the NOTICE file distributed with
// this work for additional information regarding copyright ownership.
// The ASF licenses this file to You under the Apache License, Version 2.0
// (the "License"); you may not use this file except in compliance with
// the License.  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <string>
#include <arpa/inet.h>

#include "worker/ControlMessage.h"
#include "log/LogFactory.h"

#define MAGIC ((uint32_t)(-1))

ControlMessage::ControlMessage(uint32_t _req_byte_cnt, 
	uint32_t _resp_byte_cnt, CtrlCmd _cmd, bool _in_transaction)
: 	m_command(_cmd),
	m_req_byte_cnt(_req_byte_cnt),
  	m_resp_byte_cnt(_resp_byte_cnt),
	m_in_transaction(_in_transaction ? 1 : 0),
  	m_magic(MAGIC)
{
}

ControlMessage::ControlMessage()
: 	m_command(0),
	m_req_byte_cnt(0),
  	m_resp_byte_cnt(0),
	m_in_transaction(0),
  	m_magic(0)
{
}

void ControlMessage::compose(std::string& _buffer) const
{
	int len = get_serialized_size();
	_buffer.resize(len);
	ControlMessage *r = (ControlMessage *) _buffer.c_str();

	r->m_command = m_command;
	r->m_req_byte_cnt = m_req_byte_cnt;
	r->m_resp_byte_cnt = m_resp_byte_cnt;
	r->m_in_transaction = m_in_transaction;
	r->m_magic = MAGIC;
}

bool ControlMessage::parse(std::string& _buffer)
{
	int len = get_serialized_size();
	if (_buffer.length() < len)
	{
		return false;
	}

	ControlMessage *r = (ControlMessage *) _buffer.c_str();

	m_command = r->m_command;
	m_req_byte_cnt = r->m_req_byte_cnt;
	m_resp_byte_cnt = r->m_resp_byte_cnt;
	m_in_transaction = r->m_in_transaction;
	m_magic = r->m_magic;

	return (m_magic == MAGIC);
}

void ControlMessage::dump(std::ostream& out) const
{
	out << "m_command: " << m_command << std::endl;
	out << "m_req_byte_cnt: " << m_req_byte_cnt << std::endl;
	out << "m_resp_byte_cnt: " << m_resp_byte_cnt << std::endl;
	out << "m_in_transaction: " << m_in_transaction << std::endl;
	out << "m_magic: " << m_magic << std::endl;
}
