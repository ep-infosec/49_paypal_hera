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

/* HBSender is used by OCC child worker to send heartbeat to client at regular interval
 * while a blocking SQL in pending on Oracle. Most SQLs do not take very long (heartbeat interval
 * is typically 90 seconds), so no heartbeat will go out. 
 */

#ifndef _HBSender_H
#define _HBSender_H

#include "MutexLock.h"
#include <atomic>

class OCCChild;
class LogWriterBase;
class NetstringReader;

class HBSender : public Synchronizable {
		
	private:
		int  m_timeout;        // heartbeat timeout
		bool m_is_enabled;     // heartbeat is enabled while a SQL is pending on Oracle
		std::atomic<std::uint32_t> m_rq_id; // "unique" identifier (basically a counter) of the SQL currently running
		OCCChild* m_occ_child; // handle to OCCChild

		LogWriterBase* logfile;

		// the version thread library we are using has bug wherein getpid() call within thread
		// does not give right pid. Passing pid for correlation purposes when a message is logged
		// call within heartbeat thread
		pid_t m_ppid; 
		int m_next_hb_time;
		int m_ctrl_fd; //the control pipe
		NetstringReader* m_reader;

		static HBSender* the_hbsender;


		// private copy ctor and assignment operator
		HBSender(const HBSender& _rhs);
		const HBSender& operator=(const HBSender& _rhs);

		int get_snooze_time();

		void send_heartbeat_ping();

		// returns true if data on ctrl channel, false if timeout
		bool wait_for_ctrl(int wait_time);
		// returns true if it handled the ctrl message, else if not (in case hbs is inactive)
		bool handle_ctrl();

	public:

		HBSender(OCCChild* _occ_child, int _tineout, pid_t _ppid, int _ctrl_fd);

		~HBSender();

		// start is called to start the thread
		void start();

		// main loop for thread
		void run();

		void set_rqid(uint32_t rq_id) { m_rq_id.store(rq_id); }

		// enable heartbeat, invoked right before submitting blocking SQL
		void enable();

		// disable/cancel heartbeat, invoked right after submitting blocking SQL
		void disable();
};

#endif

