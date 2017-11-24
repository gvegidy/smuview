/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
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

#ifndef VIEWS_PLOTVIEW_HPP
#define VIEWS_PLOTVIEW_HPP

#include <memory>

#include "src/views/baseview.hpp"

using std::shared_ptr;

namespace sv {

class Session;

namespace data {
class Analog;
}

namespace widgets {
class Plot;
}

namespace views {

class PlotView : public BaseView
{
	Q_OBJECT

public:
	PlotView(Session& session,
		shared_ptr<data::Analog> x_signal_data,
		shared_ptr<data::Analog> y_signal_data,
		QWidget* parent);

private:
	shared_ptr<data::Analog> x_signal_data_;
	shared_ptr<data::Analog> y_signal_data_;

	widgets::Plot *plot;

	void setup_ui();
	void connect_signals();
	void init_values();

protected:

public Q_SLOTS:

private Q_SLOTS:

};

} // namespace views
} // namespace sv

#endif // VIEWS_PLOTVIEW_HPP
