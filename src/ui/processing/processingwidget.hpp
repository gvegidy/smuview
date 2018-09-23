/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2018 Frank Stettner <frank-stettner@gmx.net>
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

#ifndef UI_PROCESSING_PROCESSINGWIDGET_HPP
#define UI_PROCESSING_PROCESSINGWIDGET_HPP

#include <memory>

#include <QAction>
#include <QMainWindow>
#include <QTabWidget>
#include <QToolBar>
#include <QToolBox>

using std::shared_ptr;

namespace sv {

class Session;

namespace processing {
class Processor;
}

namespace ui {
namespace processing {

class ProcessThreadWidget;

class ProcessingWidget : public QMainWindow
{
	Q_OBJECT

public:
	ProcessingWidget(const Session &session, QWidget *parent = nullptr);

private:
	const Session &session_;
	shared_ptr<sv::processing::Processor> processor_;
	uint thread_count_;

	QAction *const action_start_process_;
	QAction *const action_pause_process_;
	QAction *const action_stop_process_;
	QAction *const action_add_thread_;
	QAction *const action_save_process_;
	QToolBar *toolbar_;
	//QTabWidget *process_tab_widget_;
	QToolBox *thread_toolbox_;

	void setup_ui();
	void setup_toolbar();
	void processing_error(const QString, const QString);

private Q_SLOTS:
	void on_action_start_process_triggered();
	void on_action_pause_process_triggered();
	void on_action_stop_process_triggered();
	void on_action_add_thread_triggered();
	void on_action_save_process_triggered();
	void on_processor_started();
	void on_processor_finished();
	void show_processing_error(const QString, const QString);

};

} // namespace processing
} // namespace ui
} // namespace sv

#endif // UI_PROCESSING_PROCESSINGWIDGET_HPP

