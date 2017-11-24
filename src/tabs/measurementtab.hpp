/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
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

#ifndef TABS_MEASUREMENTTAB_HPP
#define TABS_MEASUREMENTTAB_HPP

#include <memory>

#include <QMainWindow>

#include "src/devices/hardwaredevice.hpp"
#include "src/tabs/devicetab.hpp"

using std::shared_ptr;

namespace sv {

namespace tabs {

class MeasurementTab : public DeviceTab
{
    Q_OBJECT

public:
	MeasurementTab(Session &session,
 		shared_ptr<devices::HardwareDevice> device, QMainWindow *parent);

private:
	uint digits_;
	QString unit_;

	void setup_ui();

};

} // namespace tabs
} // namespace sv

#endif // TABS_MEASUREMENTTAB_HPP
