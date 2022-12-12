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
#ifndef _OPSCONFIG_H_
#define _OPSCONFIG_H_

#include <config/CDBConfig.h>
#include <string>

/**
 * OPSConfig class is used to access and fetch values for Operational
 * Configuration Keys. Support types include: bool, short, int, uint
 * llong, ullong, std::string
 *
 * For the client side configuration lookups, opscfg.<app>.default
 * is preprended to every key. <app> used by this class is
 * CalClient::get_poolname() which is also the package name of the application
 * and in most cases topo APPNAME (barring few exceptions)
 *
 * In general, Ops configured values are to be stored transiently. Everytime a
 * the configuration value is needed it should be accessed using this API
 * instead of storing it in a more persistent local or member variable.
 * This class reloads the value on change and hence accessing this API
 * guarantees that the value
 * is up to date.
 */

class OPSConfig {
public:
	static OPSConfig& create_instance(const std::string& filename);
	static OPSConfig& get_instance() {return *m_instance;};
	bool get_value(const std::string& name, std::string& value) const;
	bool load_if_changed();

private:
	OPSConfig(const std::string& filename);
	~OPSConfig(){};

	CDBConfig m_cfg;
	std::string m_keyPrefix;
	static OPSConfig* m_instance;
};

#endif
