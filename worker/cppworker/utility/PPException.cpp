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
#include "PPException.h"
#include <sstream>
#include <cstdarg>

PPException::PPException(const std::string& _message)
	: m_message(_message)
{
}

PPException::PPException(const std::string& _message, const PPException& _root_cause)
	: m_message(_message)
{
	set_root_cause(_root_cause);
}

PPException::~PPException() PPEX_NOTHROW
{
	// WARNING!!!
	// ** DO NOT ** inline this function in the header file!
	// gcc will make several thousand copies of this function if you do and it
	// will increase object code size by 25% and compile time by 35%!
}

std::string PPException::get_string(void) const
{
	std::ostringstream os;
	os << get_name() << ": " << get_details_string();
	boost::shared_ptr<PPExceptionSummary> root_cause = m_root_cause;
	while (root_cause.get())
	{
		os << " / Root cause: " << root_cause->message;
		root_cause = root_cause->root_cause_next;
	}

	return os.str();
}

const std::string &PPException::get_message(void) const
{
	return m_message;
}

std::string PPException::get_details_string(void) const
{
	return m_message;
}

const char* PPException::what() const PPEX_NOTHROW
{
	m_what = get_string();
	return m_what.c_str();
}

void PPException::set_root_cause(const PPException& _root_cause)
{
	m_root_cause.reset(new PPExceptionSummary);
	m_root_cause->message = _root_cause.m_message;
	m_root_cause->root_cause_next = _root_cause.m_root_cause; 
}
