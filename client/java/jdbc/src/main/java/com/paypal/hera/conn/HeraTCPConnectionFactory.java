package com.paypal.hera.conn;

import java.util.Properties;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.paypal.hera.conf.HeraConnectionConfig;
import com.paypal.hera.ex.HeraConfigException;
import com.paypal.hera.ex.HeraIOException;

public class HeraTCPConnectionFactory implements HeraClientConnectionFactory {
	
	final static Logger LOGGER = LoggerFactory.getLogger(HeraTCPConnectionFactory.class);
	
	public HeraClientConnection createClientConnection(Properties props, String host, String port) throws HeraIOException, HeraConfigException {
		HeraConnectionConfig config = new HeraConnectionConfig(props, host, port);
		try {
			return new HeraTCPConnection(config);
		} catch (Exception e) {
			throw new HeraIOException(e);
		}
	}
}
