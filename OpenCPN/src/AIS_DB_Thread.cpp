#include "AIS_DB_Thread.h"
#include "MySqlVar.h"

//connectedToDB = false;
//bool have_updated_data = false;
//wxString AIS_Query = _("select * from decoded_ais_data where last_received_date = curdate() and last_received_time > (curtime() - 003000)");
//wxString Previous_AIS_Query = _("select * from decoded_ais_data where last_received_date = curdate() and last_received_time > (curtime() - 003000)");
//wxString connected_db_ip;
//bool checkHistory = false;
//bool checkHistoryDone = false;
AIS_DB_Thread::AIS_DB_Thread(AIS_Decoder *parent, wxString ais_database_ip)
{
	db_threads_parent = parent;
	m_n_targets = 0;

	if (mysql_real_connect(connection,
		ais_database_ip.mb_str(),//ip
		"ais_data_viewer",//user
		"password",//password
		"cop_db",//db
		3306,//port
		NULL, 0) == 0)
	{
		connectedToDB = false;

		/*wxString msg(ais_database_ip);
		msg.Prepend(_("Failed to establish connection to AIS database hosted on : "));
		OCPNMessageDialog md(NULL, msg, _("OpenCPN Message"), wxICON_ERROR );
		md.ShowModal();*/
	}
	else
	{
		connectedToDB = true;

		connected_db_ip = ais_database_ip;

		/*wxString msg(ais_database_ip);
		msg.Prepend(_("Connection established to AIS database hosted on : "));
		OCPNMessageDialog md(NULL, msg,_("OpenCPN Info"), wxOK );
		md.ShowModal();*/

		Create();
	}
}

AIS_DB_Thread::~AIS_DB_Thread(void){}

void *AIS_DB_Thread::Entry()
{
	while (1)
	{
		//-showpilotstationdata------------------
		db_threads_parent->VTMCoordinator_Data();
		//-showpilotstationdata------------------

		db_threads_parent->MySQL_DB_User();
	}

	return 0;
}

void AIS_DB_Thread::OnExit(void)
{
	mysql_close(connection);
}