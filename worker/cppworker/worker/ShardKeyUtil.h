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
#ifndef SHARDKEY_UTIL_H
#define SHARDKEY_UTIL_H

/*
 * ShardKeyUtil.h
 */

#include <string>
#include <vector>

class ShardKeyUtil
{
public:
	static void gen_shard_key(const std::string& _key_name, std::vector<std::string>& _values,
		std::string& _shard_info);

	static int parse_shard_key(const std::string& _shard_info, std::string& _key_name,
		std::vector<std::string>& _key_values);

	static void process_bind_name(const std::string& _name, std::string& _res_name);
	static void process_bind_name2(const std::string& _name, std::string& _res_name);


private:
	static void append_escape(std::string& _dest, const std::string& _src);
	static int tokenize(const std::string& _str, char _escape, char _sep,
						std::vector<std::string>& _values);
};

#endif //SHARDKEY_UTIL_H
