/* $Id$ */

/*
 * This file is part of FreeRCT.
 * FreeRCT is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * FreeRCT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with FreeRCT. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file setting_gui.cpp Main setting window code. */

#include "stdafx.h"
#include "window.h"

#include "map.h"
#include "table/gui_sprites.h"

/**
 * Setting window.
 * @ingroup gui_group
 */
class SettingWindow : public GuiWindow {
public:
	SettingWindow();

	void SetWidgetStringParameters(WidgetNumber wid_num) const override;
	void OnClick(WidgetNumber number) override;
};

/**
 * Widget numbers of the setting window.
 * @ingroup gui_group
 */
enum SettingGuiWidgets {
	SW_TITLEBAR, ///< Titlebar widget.
	SW_LANGUAGE, ///< Change language widget.
};

/**
 * Widget parts of the setting window.
 * @ingroup gui_group
 */
static const WidgetPart _setting_widgets[] = {
	Intermediate(0, 1),
		Intermediate(1, 0),
			Widget(WT_TITLEBAR, SW_TITLEBAR, COL_RANGE_BLUE), SetData(GUI_SETTING_TITLE, GUI_TITLEBAR_TIP),
			Widget(WT_CLOSEBOX, INVALID_WIDGET_INDEX, COL_RANGE_BLUE),
		EndContainer(),
		Widget(WT_PANEL, INVALID_WIDGET_INDEX, COL_RANGE_BLUE),
			Intermediate(0, 2),
				Widget(WT_LEFT_TEXT, INVALID_WIDGET_INDEX, COL_RANGE_BLUE),
						SetData(GUI_SETTING_LANGUAGE, GUI_SETTING_LANGUAGE_TOOLTIP), SetPadding(3, 3, 3, 3),
				Widget(WT_TEXT_PUSHBUTTON, SW_LANGUAGE, COL_RANGE_BLUE),
						SetData(STR_ARG1, STR_NULL), SetMinimalSize(100, 10), SetPadding(3, 3, 3, 3),
			EndContainer(),
	EndContainer(),
};


SettingWindow::SettingWindow() : GuiWindow(WC_SETTING, ALL_WINDOWS_OF_TYPE)
{
	this->SetupWidgetTree(_setting_widgets, lengthof(_setting_widgets));
}

void SettingWindow::SetWidgetStringParameters(WidgetNumber wid_num) const
{
	switch (wid_num) {
		case SW_LANGUAGE:
			_str_params.SetStrID(1, GUI_LANGUAGE_NAME); /// \todo Language name should be part of the language's properties, rather than a string.
			break;
	}
}

void SettingWindow::OnClick(WidgetNumber number)
{
	switch (number) {
		case SW_LANGUAGE:
			_current_language = (_current_language == 2) ? 0 : 2; /// \todo Needs to use a dropdown list to change language.
			for (Window *w = _manager.top; w != NULL; w = w->lower) w->ResetSize();
			break;
	}
}

/**
 * Open the settings window.
 * @ingroup gui_group
 */
void ShowSettingGui()
{
	if (HighlightWindowByType(WC_SETTING, ALL_WINDOWS_OF_TYPE)) return;
	new SettingWindow();
}