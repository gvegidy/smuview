/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 * Copyright (C) 2016 Soeren Apel <soeren@apelpie.net>
 * Copyright (C) 2017-2018 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>

#include <QDebug>

#include <libsigrokcxx/libsigrokcxx.hpp>

#include "basechannel.hpp"
#include "src/util.hpp"
#include "src/channels/basechannel.hpp"
#include "src/data/analogsignal.hpp"
#include "src/data/basesignal.hpp"
#include "src/devices/basedevice.hpp"

using std::make_pair;
using std::make_shared;

namespace sv {
namespace channels {

BaseChannel::BaseChannel(
		shared_ptr<devices::BaseDevice> parent_device,
		const QString channel_group_name,
		double channel_start_timestamp) :
	channel_start_timestamp_(channel_start_timestamp),
	has_fixed_signal_(false),
	actual_signal_(nullptr),
	parent_device_(parent_device),
	channel_group_name_(channel_group_name),
	name_("")
{
	qWarning() << "Init channel " << name_
		<< ", channel_start_timestamp = "
		<< util::format_time_date(channel_start_timestamp);
}

BaseChannel::~BaseChannel()
{
}

bool BaseChannel::has_fixed_signal()
{
	return has_fixed_signal_;
}

void BaseChannel::set_fixed_signal(bool has_fixed_signal)
{
	has_fixed_signal_ = has_fixed_signal;
}

shared_ptr<data::BaseSignal> BaseChannel::actual_signal()
{
	return actual_signal_;
}

map<BaseChannel::quantity_t, shared_ptr<data::BaseSignal>> BaseChannel::signal_map()
{
	return signal_map_;
}

shared_ptr<devices::BaseDevice> BaseChannel::parent_device()
{
	return parent_device_;
}

QString BaseChannel::channel_group_name() const
{
	return channel_group_name_;
}

QString BaseChannel::name() const
{
	return name_;
}

void BaseChannel::set_name(QString name)
{
	name_ = name;
	name_changed(name);
}

QString BaseChannel::display_name() const
{
	return name_;
}

bool BaseChannel::enabled() const
{
	return true;
}

void BaseChannel::set_enabled(bool value)
{
	(void)value;
}

ChannelType BaseChannel::type() const
{
	return channel_type_;
}

QColor BaseChannel::colour() const
{
	return colour_;
}

void BaseChannel::set_colour(QColor colour)
{
	colour_ = colour;
	colour_changed(colour);
}

void BaseChannel::save_settings(QSettings &settings) const
{
	settings.setValue("name", name());
	settings.setValue("enabled", enabled());
	settings.setValue("colour", colour());
}

void BaseChannel::restore_settings(QSettings &settings)
{
	set_name(settings.value("name").toString());
	set_enabled(settings.value("enabled").toBool());
	set_colour(settings.value("colour").value<QColor>());
}

void BaseChannel::on_aquisition_start_timestamp_changed(double timestamp)
{
	qWarning()
		<< "BaseChannel::on_aquisition_start_timestamp_changed() timestamp = "
		<< util::format_time_date(timestamp);
	channel_start_timestamp_ = timestamp;
	Q_EMIT channel_start_timestamp_changed(timestamp);
}

} // namespace channels
} // namespace sv
