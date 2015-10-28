/**********************************************************************
* Copyright (c) 2015 Mark Charlebois
* 
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the
* disclaimer below) provided that the following conditions are met:
* 
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
* 
*  * Neither the name of Dronecode Project nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
* 
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
* GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
* HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************/
#include <stdio.h>
#include <list>
#include "DriverFramework.hpp"
#include "DriverMgr.hpp"

using namespace DriverFramework;

// TODO add missing locking

static std::list<DriverFramework::DriverObj *> *g_driver_list = nullptr;

int DriverMgr::initialize(void)
{
	g_driver_list = new std::list<DriverFramework::DriverObj *>;
	if (g_driver_list == nullptr) {
		return -1;
	}
	return 0;
}

void DriverMgr::finalize(void)
{
	std::list<DriverFramework::DriverObj *>::iterator it = g_driver_list->begin(); 
	while (it != g_driver_list->end()) {
		g_driver_list->erase(it);
	}
}

void DriverMgr::registerDriver(DriverObj *obj)
{
	g_driver_list->push_back(obj);
}

void DriverMgr::unRegisterDriver(DriverObj *obj)
{
	std::list<DriverFramework::DriverObj *>::iterator it = g_driver_list->begin(); 
	while (it != g_driver_list->end()) {
		if (*it == obj) {
			g_driver_list->erase(it);
			break;
		}
	}
}

DriverObj *DriverMgr::getDriverObjByName(const std::string &name, unsigned int instance)
{
	std::list<DriverFramework::DriverObj *>::iterator it = g_driver_list->begin(); 
	while (it != g_driver_list->end()) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}
	return nullptr;
}

DriverObj *DriverMgr::getDriverObjByID(unsigned long id)
{
	std::list<DriverFramework::DriverObj *>::iterator it = g_driver_list->begin(); 
	while (it != g_driver_list->end()) {
		if ((*it)->getId() == id) {
			return *it;
		}
	}
	return nullptr;
}

