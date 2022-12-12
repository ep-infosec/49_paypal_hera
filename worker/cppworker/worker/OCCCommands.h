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
#ifndef _OCCCOMMANDS_H_
#define _OCCCOMMANDS_H_

//server commands
enum OCCReturnCode {
	OCC_SQL_ERROR = 1,
	OCC_ERROR = 2,
	OCC_VALUE = 3,
	OCC_HELLO = 4,
	OCC_OK = 5,
	OCC_NO_MORE_DATA = 6,
	OCC_STILL_EXECUTING = 7,
	OCC_MARKDOWN = 8,
};

enum OCCCommand {
	OCC_PREPARE       =1,
	OCC_BIND_NAME     =2,
	OCC_BIND_VALUE    =3,
	OCC_EXECUTE       =4,
	OCC_ROWS          =5,
	OCC_COLS          =6,
	OCC_FETCH         =7,
	OCC_COMMIT        =8,
	OCC_ROLLBACK      =9,
	OCC_BIND_TYPE     =10,
	OCC_CLIENT_INFO   =11,
	OCC_BACKTRACE     =12,
	OCC_BIND_OUT_NAME =13,
	OCC_PREPARE_SPECIAL =14,
	OCC_TRANS_START     =15,
	OCC_TRANS_TIMEOUT	=16,
	OCC_TRANS_ROLE		=17,
	OCC_TRANS_PREPARE   =18,
	OCC_SQL_STMT_CACHING=19,
	OCC_INT_CLIENT_INFO =20,
	OCC_CLIENT_CAL_CORRELATION_ID=21,
	OCC_COLS_INFO       =22,
	OCC_BIND_NUM		=23,
	OCC_BIND_VALUE_MAX_SIZE  =24,
	OCC_PREPARE_V2		=25,
	OCC_SHARD_KEY		=27,
	OCC_GET_NUM_SHARDS	=28,
	OCC_SET_SHARD_ID	=29,
};

//special queries (actual query text is defined in the OCC cdbs)
enum OCCSpecialQuery {
	OCC_QUERY_MIN_ID_FROM_WTRANSACTION                   =1,
	OCC_QUERY_PARTITIONS_FROM_WTRANSACTION_PARTITIONS    =2,
};

#endif
