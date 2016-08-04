#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/datetime.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/aui/aui.h>
#include <wx/wxhtml.h>

#include <mysql.h>
#include <ostream>

#include <vector>
#include <Select.h>
#include "AIS_Decoder.h"

//-anchorwatch---------
extern wxString        g_default_wp_icon;
extern Select          *pSelect;
extern RoutePoint       *pAnchorWatchPoint1;   // pjotrc 2010.02.15
extern RoutePoint       *pAnchorWatchPoint2;   // pjotrc 2010.02.15

extern wxString         g_AW1GUID;
extern wxString         g_AW2GUID;
extern int              g_nAWDefault;

extern int AWmmsi1, AWmmsi2;
extern double AWship1Lat, AWship1Lon, AWship2Lat, AWship2Lon;
extern int AW_counter;//AW_counter = 0;
//-anchorwatch---------

//-showpilotstationdata------------------
extern wxString VTMCoordinators;// _T("New Pilot Station");
//-showpilotstationdata------------------


//-wrc--------------------------------------------------

extern MYSQL *connection;
extern bool connectedToDB;
extern bool have_updated_data;
extern wxString AIS_Query;
extern wxString Previous_AIS_Query;
extern wxString connected_db_ip;
extern bool checkHistory;
extern bool checkHistoryDone;
extern AIS_Decoder* g_pAIS;

//-wrc--------------------------------------------------
