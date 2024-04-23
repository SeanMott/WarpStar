// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <wx/bitmap.h>
#include <wx/dialog.h>
#include <wx/generic/statbmpg.h>
#include <wx/hyperlink.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include "Common/Common.h"
#include "DolphinWX/AboutDolphin.h"
#include "DolphinWX/WxUtils.h"

AboutDolphin::AboutDolphin(wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& position, const wxSize& size, long style)
	: wxDialog(parent, id, title, position, size, style)
{
	wxGenericStaticBitmap* const sbDolphinLogo = new wxGenericStaticBitmap(
		this, wxID_ANY, WxUtils::LoadScaledResourceBitmap("dolphin_logo", this));

	const wxString DolphinText = _("Warp Star - Ishiiruka");
	const wxString RevisionText = scm_desc_str;
	const wxString CopyrightText =
		_("(c) 04/23/2024+ Sean (Jas) Mott. \"GameCube\", \"Wii\", and \"Kirby Air Ride\" are trademarks of Nintendo. Warp Star "
			"is not affiliated with Nintendo in any way.");
	const wxString BranchText = wxString::Format(_("Branch: %s"), scm_branch_str.c_str());
	const wxString BranchRevText = wxString::Format(_("Revision: %s"), scm_rev_git_str.c_str());
	const wxString CheckUpdateText = _("Download Updates via KAR Workshop: ");
	const wxString Text =
		_("\n"
			"Warp Star is a free and open-source KAR emulator.\n"
			"\n"
			"This software should be used to play KAR Netplay.\n\n"
			"Created by Sean (Jas) Mott based on the work by Slippie and Dolphin Team\n\n"
	        "Special thanks to Jinxy for assisting with finding some of the quirks with Dolphin and being a second pair of eyes to this insane idea\n\n"
			"Special thanks to Taco, Support PVP, and Hey Now for being my test subjects\n\n"
	        "And of course our resident Netplay Admin Kinix, where would I be without his WTFs and adament support\n");
	const wxString LicenseText = _("License");
	//const wxString AuthorsText = _("Sean (Jas) Mott, based on the work by the Slippie crew");
	const wxString SupportText = _("Support can be found at the Netplay Server");

	wxStaticText* const Dolphin = new wxStaticText(this, wxID_ANY, DolphinText);
	wxStaticText* const Revision = new wxStaticText(this, wxID_ANY, RevisionText);

	wxStaticText* const Copyright = new wxStaticText(this, wxID_ANY, CopyrightText);
	wxStaticText* const Branch =
		new wxStaticText(this, wxID_ANY, BranchText + "\n" + BranchRevText + "\n");
	wxStaticText* const Message = new wxStaticText(this, wxID_ANY, Text);
	wxStaticText* const UpdateText = new wxStaticText(this, wxID_ANY, CheckUpdateText);
	wxStaticText* const FirstSpacer = new wxStaticText(this, wxID_ANY, "  |  ");
	wxHyperlinkCtrl* const Download = new wxHyperlinkCtrl(this, wxID_ANY, "KAR Workshop",
		"");
	wxHyperlinkCtrl* const License =
		new wxHyperlinkCtrl(this, wxID_ANY, LicenseText,
			"https://github.com/SeanMott/WarpStar/blob/main/license.txt");
	//wxHyperlinkCtrl* const Authors = new wxHyperlinkCtrl(
	//	this, wxID_ANY, AuthorsText, "");
	//wxStaticText *const authors =
	//    new wxStaticText(this, wxID_ANY, "Sean (Jas) Mott, based on the work by the Slippie crew");
	wxHyperlinkCtrl* const Support =
		new wxHyperlinkCtrl(this, wxID_ANY, SupportText, "http://discord.gg/p3rGrcr");

	wxFont DolphinFont = Dolphin->GetFont();
	wxFont RevisionFont = Revision->GetFont();
	wxFont CopyrightFont = Copyright->GetFont();
	wxFont BranchFont = Branch->GetFont();

	DolphinFont.SetPointSize(36);
	Dolphin->SetFont(DolphinFont);

	RevisionFont.SetWeight(wxFONTWEIGHT_BOLD);
	Revision->SetFont(RevisionFont);

	BranchFont.SetPointSize(7);
	Branch->SetFont(BranchFont);

	CopyrightFont.SetPointSize(7);
	Copyright->SetFont(CopyrightFont);
	Copyright->SetFocus();

	wxSizerFlags center_flag;
	center_flag.Center();
	const int space5 = FromDIP(5);
	const int space10 = FromDIP(10);
	const int space15 = FromDIP(15);
	const int space30 = FromDIP(30);
	const int space40 = FromDIP(40);
	const int space75 = FromDIP(75);

	wxBoxSizer* const sCheckUpdates = new wxBoxSizer(wxHORIZONTAL);
	sCheckUpdates->Add(UpdateText, center_flag);
	sCheckUpdates->Add(Download, center_flag);

	wxBoxSizer* const sLinks = new wxBoxSizer(wxHORIZONTAL);
	sLinks->Add(License, center_flag);
	sLinks->Add(FirstSpacer, center_flag);
	//sLinks->Add(SecondSpacer, center_flag);
	sLinks->Add(Support, center_flag);

	wxBoxSizer* const sInfo = new wxBoxSizer(wxVERTICAL);
	sInfo->Add(Dolphin);
	sInfo->AddSpacer(space5);
	sInfo->Add(Revision);
	sInfo->AddSpacer(space10);
	sInfo->Add(Branch);
	sInfo->Add(sCheckUpdates);
	sInfo->Add(Message);
	sInfo->Add(sLinks);

	wxBoxSizer* const sLogo = new wxBoxSizer(wxVERTICAL);
	sLogo->AddSpacer(space75);
	sLogo->Add(sbDolphinLogo);
	sLogo->AddSpacer(space40);

	wxBoxSizer* const sMainHor = new wxBoxSizer(wxHORIZONTAL);
	sMainHor->AddSpacer(space30);
	sMainHor->Add(sLogo);
	sMainHor->AddSpacer(space30);
	sMainHor->Add(sInfo);
	sMainHor->AddSpacer(space30);

	wxBoxSizer* const sFooter = new wxBoxSizer(wxVERTICAL);
	sFooter->AddSpacer(space15);
	sFooter->Add(Copyright, 0, wxALIGN_CENTER_HORIZONTAL);
	sFooter->AddSpacer(space5);

	wxBoxSizer* const sMain = new wxBoxSizer(wxVERTICAL);
	sMain->Add(sMainHor, 1, wxEXPAND);
	sMain->Add(sFooter, 0, wxEXPAND);

	SetSizerAndFit(sMain);
	Center();
	SetFocus();
}
