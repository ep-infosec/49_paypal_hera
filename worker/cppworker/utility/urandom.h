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
#ifndef URANDOM_H
#define URANDOM_H

#include <climits>
#include <stdio.h>
#include "utility/PPException.h"


//-----------------------------------------------------------------------------
//
// urandom is a static helper class for pulling data from /dev/urandom.
// It's the standard pseudorandom number source within PayPal code.
//
// The only other allowed/approved random data source is srand/rand, and it
// shouldn't be used except in one of the following situations:
// 1) you need a repeatable pseudorandom sequence (srand with a static seed)
// 2) the quality of the random data is not at all important.  i.e. it would be
//    just fine if a malicious user could predict the random numbers
//
// An example of 2) would be generating the random /* 7 */ comments in wuser
// queries.
// 
// On each call, urandom will open /dev/urandom, read the necessary amount of
// data, and then close it.
//
//-----------------------------------------------------------------------------

class urandom {
public:
	// any of these methods can throw a urandomException if they fail to open
	// or	read from /dev/urandom.

	// returns a random uint on [0, UINT_MAX]
	static uint rand();
	// returns a random uint on [0, _range - 1].  _range == 0 returns 0.
	static uint rand(uint _range);
	// fills _buffer with _length bytes of random data
	static void fill_buffer(std::string& _buffer, uint _length);
	static void fill_buffer(void* _buffer, uint _length);

private:
	// private constructor, never called
	urandom() {}

	// internal method that does the actual open/read/close
	static void read_bytes(void* _buffer, uint _count);
};

//-----------------------------------------------------------------------------

class urandomException : public PPException {
public:
	urandomException(const std::string& _message) : PPException(_message) {}
	virtual std::string get_name() const { return "urandomException"; }
};

#endif
