#pragma once

//defines the mod managing window

#include <wx/dialog.h>

namespace KAR
{
class ModManager : public wxDialog
{
  public:

	  //Constructor
	ModManager(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = _("Mods"),
	             const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
	             long style = wxDEFAULT_DIALOG_STYLE);
};

}