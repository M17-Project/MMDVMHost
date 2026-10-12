/*
 *   Copyright (C) 2020,2021 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(M17Control_H)
#define	M17Control_H

#include "RSSIInterpolator.h"
#include "M17Network.h"
#include "M17Defines.h"
#include "RingBuffer.h"
#include "StopWatch.h"
#include "Display.h"
#include "Defines.h"
#include "M17LSF.h"
#include "Timer.h"
#include "Modem.h"

#include <string>

class CM17Control {
public:
	CM17Control(const std::string& callsign, unsigned int can, bool selfOnly, bool allowEncryption, CM17Network* network, CDisplay* display, unsigned int timeout, bool duplex, CRSSIInterpolator* rssiMapper);
	~CM17Control();

	bool writeModem(unsigned char* data, unsigned int len);

	unsigned int readModem(unsigned char* data);

	void clock(unsigned int ms);

	bool isBusy() const;

	void enable(bool enabled);

private:
	std::string                m_callsign;
	unsigned int               m_can;
	bool                       m_selfOnly;
	bool                       m_allowEncryption;
	CM17Network*               m_network;
	CDisplay*                  m_display;
	bool                       m_duplex;
	CRingBuffer<unsigned char> m_queue;
	std::string                m_source;
	std::string                m_dest;
	RPT_RF_STATE               m_rfState;
	RPT_NET_STATE              m_netState;
	CTimer                     m_rfTimeoutTimer;
	CTimer                     m_netTimeoutTimer;
	CTimer                     m_networkWatchdog;
	CStopWatch                 m_elapsed;
	unsigned int               m_rfFrames;
	unsigned int               m_netFrames;
	unsigned int               m_rfErrs;
	unsigned int               m_rfBits;
	unsigned int               m_rfLSFCount;
	CM17LSF                    m_rfCurrentRFLSF;
	CM17LSF                    m_rfCurrentNetLSF;
	CM17LSF                    m_rfCollectingLSF;
	CM17LSF                    m_rfCollectedLSF;
	unsigned int               m_rfLSFn;
	CM17LSF                    m_netLSF;
	unsigned int               m_netLSFn;
	unsigned char              m_rfTextBits;
	unsigned char              m_netTextBits;
	char*                      m_rfText;
	char*                      m_netText;
	CRSSIInterpolator*         m_rssiMapper;
	unsigned char              m_rssi;
	unsigned char              m_maxRSSI;
	unsigned char              m_minRSSI;
	unsigned int               m_aveRSSI;
	unsigned int               m_rssiCount;
	bool                       m_enabled;
	unsigned char*             m_rfPacket;
	unsigned int               m_rfPacketLength;
	bool                       m_rfPacketValid;
	bool                       m_rfPacketComplete;
	FILE*                      m_fp;

	bool processRFHeader(bool lateEntry);

	void processRFPacket();
	void logEndRFPacket();
	void processNetPacket(const unsigned char* data, unsigned int length);

	bool checkPacket(const unsigned char* data, unsigned int length) const;
	void logPacket(const char* from, const std::string& source, const std::string& dest, const unsigned char* data, unsigned int length) const;

	void encodeLinkSetupFrame(const CM17LSF& lsf, unsigned char* data) const;
	void encodePacketFrame(const unsigned char* frame, unsigned char* data) const;
	void encodeEOTFrame(unsigned char* data) const;

	void writeQueueRF(const unsigned char* data);

	void writeQueueNet(const unsigned char* data);

	void writeNetwork();

	void interleaver(const unsigned char* in, unsigned char* out) const;
	void decorrelator(const unsigned char* in, unsigned char* out) const;

	bool checkCallsign(const std::string& source) const;

	void createRFLSF(bool addCallsign);

	void writeEndRF();
	void writeEndNet();

	bool openFile();
	bool writeFile(const unsigned char* data);
	void closeFile();
};

#endif
