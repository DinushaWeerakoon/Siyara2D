#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/datetime.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/aui/aui.h>

#include <vector>
#include "AIS_Decoder.h"
#include <mysql.h>

//-wrc----------------------

//    A simple thread to use database without blocking the main thread
class AIS_DB_Thread : public wxThread
{
public:
	AIS_DB_Thread(AIS_Decoder *parent, wxString ais_database_ip);
	~AIS_DB_Thread(void);
	void *Entry();
	void OnExit(void);

private:
	AIS_Decoder *db_threads_parent;
	int m_n_targets;
};

//-wrc-----------------------