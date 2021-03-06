/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017-2019 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>

#include <QDebug>

#include "session.hpp"
#include "src/util.hpp"
#include "src/devices/basedevice.hpp"

using std::function;
using std::shared_ptr;
using std::string;
using std::unordered_set;

namespace sigrok {
class Context;
}

namespace sv {

shared_ptr<sigrok::Context> Session::sr_context;
double Session::session_start_timestamp = .0;

Session::Session(DeviceManager &device_manager) :
	device_manager_(device_manager)
{
}

Session::~Session()
{
	for (auto device : devices_)
		device->close();
}

DeviceManager& Session::device_manager()
{
	return device_manager_;
}

const DeviceManager& Session::device_manager() const
{
	return device_manager_;
}

void Session::save_settings(QSettings &settings) const
{
	(QSettings)&settings;

	// TODO: Remove all signal data from settings?
}

void Session::restore_settings(QSettings &settings)
{
	(QSettings)&settings;

	// TODO: Restore all signal data from settings?
}

unordered_set<shared_ptr<devices::BaseDevice>> Session::devices() const
{
	return devices_;
}

void Session::add_device(shared_ptr<devices::BaseDevice> device,
	function<void (const QString)> error_handler)
{
	assert(device);

	try {
		device->open(error_handler);
	}
	catch (const QString &e) {
		qWarning() << e;
		device.reset();
	}

	devices_.insert(device);

	Q_EMIT device_added(device);
}

void Session::remove_device(shared_ptr<devices::BaseDevice> device)
{
	if (device)
		device->close();

	devices_.erase(device);
}

} // namespace sv
