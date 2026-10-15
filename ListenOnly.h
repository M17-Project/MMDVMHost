/*
 *   Copyright (C) 2026 by Chip Cuccio W0CHP
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

#if !defined(LISTENONLY_H)
#define LISTENONLY_H

// Set by the "listen on|off" remote command (CMMDVMHost::setListenOnly).
// While set, nothing is transmitted and nothing heard on RF is written to
// any network; RF is still decoded and published.
extern bool g_listenOnly;

#endif
